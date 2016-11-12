/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_generic.h"
#include "app_usb.h"
#include <string.h>
#include "system.h"
#include "rom.h"

extern volatile CTRL_TRF_SETUP SetupPkt;

#if defined(FIXED_ADDRESS_MEMORY)
PacketToFromPC INPacket VENDOR_BASIC_DEMO_IN_DATA_BUFFER_ADDRESS;
PacketToFromPC OUTPacket VENDOR_BASIC_DEMO_OUT_DATA_BUFFER_ADDRESS;
#else
PacketToFromPC INPacket;
PacketToFromPC OUTPacket;
#endif

/** V A R I A B L E S ********************************************************/
#define PacketFromPC OUTPacket
#define PacketToPC INPacket

PacketToFromPC WorkingPacket;


unsigned char AppState;

static uint32_t cmd_op_addr = 0;
static uint32_t cmd_op_size = 0;

static USB_HANDLE USBGenericOutHandle;
static USB_HANDLE USBGenericInHandle;

static uint8_t rqCmd = 0;
static uint8_t rqPendingCmd = 0;
static uint32_t rqArg0 = 0;
static uint32_t rqArg1 = 0;

volatile uint8_t AppVendorRequest[USB_EP0_BUFF_SIZE];

// Page buffer data
uint8_t pgData[0x160];
uint8_t *currentPgData = &pgData;

/** FUNCTIONS ******************************************************/

void APP_USBInitialize() {
    AppState = IDLE;
    rom_init();

    //initialize the variable holding the handle for the last
    // transmission
    USBGenericOutHandle = 0;
    USBGenericInHandle = 0;

    //Enable the application endpoints
    USBEnableEndpoint(USBGEN_EP_NUM, USB_OUT_ENABLED | USB_IN_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);

    //Arm the application OUT endpoint, so it can receive a packet from the host
    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
}

static void App_VendorReportComplete(void) {
    // transfert complete ...
    rqCmd = rqPendingCmd;

    //
    ((uint8_t *) & rqArg0)[3] = AppVendorRequest[3];
    ((uint8_t *) & rqArg0)[2] = AppVendorRequest[2];
    ((uint8_t *) & rqArg0)[1] = AppVendorRequest[1];
    ((uint8_t *) & rqArg0)[0] = AppVendorRequest[0];

    ((uint8_t *) & rqArg1)[3] = AppVendorRequest[7];
    ((uint8_t *) & rqArg1)[2] = AppVendorRequest[6];
    ((uint8_t *) & rqArg1)[1] = AppVendorRequest[5];
    ((uint8_t *) & rqArg1)[0] = AppVendorRequest[4];

    rqPendingCmd = 0;
    
    // Cancel pending operation
    if (AppState == PENDING_OPERATION) {
        //cmd_op_addr = 0;
        //rom_init(); 
    }
    AppState = IDLE;
}

void APP_USBCheckVendorRequest() {
    switch (SetupPkt.bRequest) {
        case TO_BOOLOADER:
        case QUERY_DEVICE:
        case PROM_BULK_READ:
        case ROM_ERASE:
        case ROM_WRITE:
        case ROM_ERASE_8_16:
        case ROM_WRITE_8_16:
        case ROM_WRITE_UNLOCKED_AMD:
        case ROM_WRITE_PAGE_8_16:
        case PROM_ID:
            rqPendingCmd = SetupPkt.bRequest;
            USBEP0Receive((uint8_t*) & AppVendorRequest, SetupPkt.wLength, &App_VendorReportComplete);
            break;
        default:
            break;
    }
}

void ProcessIO(void) {
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) return;

    if (AppState == PENDING_OPERATION) {
        switch (rqCmd) {
            case ROM_WRITE_UNLOCKED_AMD:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    uint8_t status = amd_unlock_rom_write_8_16((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
                    PacketToPC.Command = status;
                    
                    // not busy anymore
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
            
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        amd_unlock_write_end();
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
            case ROM_WRITE_8_16:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);                    
                    uint8_t status = rom_write_8_16((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
                    PacketToPC.Command = status;
                    
                    // not busy anymore
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
            
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        rom_reset();
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
            case ROM_WRITE_PAGE_8_16:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    const uint32_t pgSize = 0x100;                    
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    for(int i = 0; i < 0x40; i++) {
                        *currentPgData++ = OUTPacket.Contents[i];
                    }
                    
                    if (currentPgData >= (pgData+pgSize)) {                    
                        uint8_t status = rom_page_write_8_16((uint8_t *) &pgData, cmd_op_addr, pgSize);
                        OUTPacket.Command = status;
                        // reset page data ptr
                        currentPgData = pgData;   
                        cmd_op_addr += pgSize;
                    } else {
                        OUTPacket.Command = ROM_OK;     
                    }
                    
                    // not busy anymore
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
            
                   // cmd_op_addr += USB_PACKET_SIZE;
                   // 
                    if (cmd_op_addr >= cmd_op_size) {
                        rom_reset();
                        AppState = IDLE; 
                        rqCmd = 0; 
                        // reset page data ptr
                        currentPgData = pgData;
                    }
                }
                
                break;
            case ROM_WRITE:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    uint8_t status = rom_write((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
                    PacketToPC.Command = status;
                    
                    // not busy anymore
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
            
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
                
            case PROM_BULK_READ:
                
                if (!USBHandleBusy(USBGenericInHandle)) {
                    rom_read((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
        }
    } else if (rqCmd != 0) {
        switch (rqCmd) {
            case TO_BOOLOADER:
                cmd_bootloader();
                rqCmd = 0;
                AppState = IDLE;
                break;
                
            case QUERY_DEVICE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    memset(&PacketToPC, 0, USB_PACKET_SIZE);
                    PacketToPC.Command = QUERY_DEVICE;
                    PacketToPC.BytesPerAddress = 0x29;
                    PacketToPC.PacketDataFieldSize = REQUEST_DATA_BLOCK_SIZE;                 
                    
                    rqCmd = 0;
                    AppState = IDLE;
                    
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);

                    // time for init
                    rom_init();  
                }
                break;
                                
            case ROM_ERASE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    rom_erase(in);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case ROM_ERASE_8_16:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    rom_erase_8_16(in);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case PROM_ID:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    
                    rom_reset();                    
                    rom_identify(in);
                    
                    rom_reset();
                    rom_identify_8_16(&in[0x10]);
                    
                    rom_reset();

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case ROM_WRITE:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                AppState = PENDING_OPERATION;
                
                break;
                
            case ROM_WRITE_8_16:
            case ROM_WRITE_PAGE_8_16:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                rom_reset();
                
                AppState = PENDING_OPERATION;
                
                break;                
                
            case ROM_WRITE_UNLOCKED_AMD:                
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                AppState = PENDING_OPERATION;
                
                // send unlock cmd
                amd_unlock_write_start();
                break;
                
            case PROM_BULK_READ:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                        
                rom_reset();
                
                AppState = PENDING_OPERATION;    
                
                break;
                
                
            case CMD_DBG:    
                if (!USBHandleBusy(USBGenericInHandle)) {  
                    uint8_t * in = (uint8_t*) & PacketToPC;    
                    rom_write_8_16(in, 0, 0x40);
                    rom_custom(rqArg0, rqArg1);

                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
        }
    }
}
