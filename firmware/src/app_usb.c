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
}

void APP_USBCheckVendorRequest() {
    switch (SetupPkt.bRequest) {
        case TO_BOOLOADER:
        case QUERY_DEVICE:
        case PROM_BULK_READ:
        case SST39_ERASE:
        case SST39_WRITE:
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
            case SST39_WRITE:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    SST39xx_rom_write((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
                    
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
                
            case SST39_ERASE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    SST39xx_rom_erase(in);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case PROM_ID:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    rom_identify(in);
                    rom_identify(&in[0x10]);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case SST39_WRITE:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                AppState = PENDING_OPERATION;
                
                break;
                
            case PROM_BULK_READ:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                AppState = PENDING_OPERATION;    
                
                break;
        }
    }
}

void old_ProcessIO(void) {

    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) return;

    if (AppState == IDLE) {

        if (!USBHandleBusy(USBGenericOutHandle)) {
            USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
            AppState = NOT_IDLE;
            memset(&PacketToPC, 0, USB_PACKET_SIZE);
        }
    }
    else if (AppState == CMD_READ_IN_PROGRESS) {
        if (!USBHandleBusy(USBGenericInHandle)) {
            rom_read((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
            USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
            cmd_op_addr += USB_PACKET_SIZE;
            if (cmd_op_addr >= cmd_op_size) {
                AppState = IDLE;
                cmd_op_addr = 0;
                cmd_op_size = 0;
            }
        }
    }
#if 0 // crash ...
    else if (AppState == CMD_WRITE_IN_PROGRESS) {
        if (!USBHandleBusy(USBGenericOutHandle)) {
            USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
            SST39xx_rom_write((uint8_t *) OUTPacket, cmd_op_addr, USB_PACKET_SIZE);

            cmd_op_addr += USB_PACKET_SIZE;
            if (cmd_op_addr >= cmd_op_size) {
                AppState = IDLE;
                cmd_op_addr = 0;
                cmd_op_size = 0;
            }
        }
    }
#endif
    else {
        switch (PacketFromPC.Command) //Data arrived, check what kind of command might be in the packet of data.
        {
            case TO_BOOLOADER:
                cmd_bootloader();
                break;

            case QUERY_DEVICE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    memset(&PacketToPC, 0, USB_PACKET_SIZE);
                    PacketToPC.Command = QUERY_DEVICE;
                    PacketToPC.BytesPerAddress = 0x29;
                    PacketToPC.PacketDataFieldSize = REQUEST_DATA_BLOCK_SIZE;

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    AppState = IDLE;

                    // time for init
                    rom_init();
                }
                break;

            case PROM_BULK_READ:
                //PacketFromPC.RomSize = 0x100000;
                //PacketFromPC.RomAddress = 0;
                cmd_op_addr = PacketFromPC.RomAddress;
                cmd_op_size = PacketFromPC.RomSize;
                rom_start_read();
                AppState = CMD_READ_IN_PROGRESS;
                break;

            case SST39_ERASE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    SST39xx_rom_erase(in);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    AppState = IDLE;
                }
                break;
#if 0 // crash
            case SST39_WRITE:
                cmd_op_addr = PacketFromPC.address;
                cmd_op_size = PacketFromPC.size;
                AppState = CMD_WRITE_IN_PROGRESS;
                break;
#else
            case SST39_WRITE:
                //if (!USBHandleBusy(USBGenericInHandle)) 
            {

                cmd_op_addr = PacketFromPC.address;
                cmd_op_size = PacketFromPC.size;
                SST39xx_rom_write((uint8_t *) PacketFromPC.byte, cmd_op_addr, cmd_op_size);
                //USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketFromPC, USBGEN_EP_SIZE);
                AppState = IDLE;
            }
                break;
#endif

            case PROM_ID:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    rom_identify(in);
                    rom_identify(&in[0x10]);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    AppState = IDLE;
                }
                break;
        }
    }
}
