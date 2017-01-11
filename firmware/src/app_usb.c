/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_generic.h"
#include "app_usb.h"
#include <string.h>
#include "system.h"
#include "rom.h"


void cmd_bootloader();

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
        case ROM_READ_8:
        case ROM_READ_16:
        case ROM_ERASE:
        case ROM_WRITE:
        case ROM_ERASE_8_16:
        case ROM_WRITE_8_16:
        case ROM_WRITE_UNLOCKED_AMD:
        case ROM_WRITE_PAGE_8_16:
        case PROM_ID:
        case SNES_SRAM_READ:
        case SNES_ROM_READ:
        case SNES_SRAM_WRITE:
        case GENESIS_SRAM_WRITE:
        case GENESIS_SRAM_READ:
        case GENESIS_ROM_READ:
        case GENESIS_ROM_WRITE:
        case GENESIS_ROM_ERASE:
            if (USBHandleBusy(USBGenericInHandle)) {
                USBCancelIO(USBGEN_EP_NUM);
            }
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
                        rom_reset_8();
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
                        rom_reset_8_16();
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
                    uint8_t status = rom_write_8((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
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
                
                
            case GENESIS_ROM_WRITE:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    uint8_t status = genesis_rom_write((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
                    PacketToPC.Command = status;
                    
                    // not busy anymore
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
            
                    cmd_op_addr += USB_PACKET_SIZE>>1;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
                
            case ROM_READ_8:
                
                if (!USBHandleBusy(USBGenericInHandle)) {
                    rom_read_8((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
              
            case GENESIS_ROM_READ:
            case ROM_READ_16:
            //case GENESIS_SRAM_READ:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    rom_read_16((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    cmd_op_addr += USB_PACKET_SIZE>>1;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
            
            case (GENESIS_SRAM_READ):
                if (!USBHandleBusy(USBGenericInHandle)) {                    
                    genesis_sram_read((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    cmd_op_addr += USB_PACKET_SIZE>>1;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
            case GENESIS_SRAM_WRITE:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    uint8_t status = genesis_sram_write((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
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
                
            case SNES_SRAM_WRITE:
                if (!USBHandleBusy(USBGenericOutHandle) && !USBHandleBusy(USBGenericInHandle)) {
                    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (uint8_t*) & OUTPacket, USBGEN_EP_SIZE);
                    uint8_t status = snes_sram_write((uint8_t *) &OUTPacket, cmd_op_addr, USB_PACKET_SIZE);
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
            case SNES_SRAM_READ:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    snes_sram_read((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    cmd_op_addr += USB_PACKET_SIZE;
                    if (cmd_op_addr >= cmd_op_size) {
                        AppState = IDLE; 
                        rqCmd = 0;   
                    }
                }
                
                break;
                
            case SNES_ROM_READ:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    snes_rom_read((uint8_t *) & PacketToPC, cmd_op_addr, USB_PACKET_SIZE);
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
                    rom_erase_8(in);

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
                
            case GENESIS_ROM_ERASE:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    genesis_rom_erase(in);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case PROM_ID:
                if (!USBHandleBusy(USBGenericInHandle)) {
                    uint8_t * in = (uint8_t*) & PacketToPC;
                    
                    rom_reset_8();                    
                    rom_identify_8(in);
                    
                    rom_reset_8();
                    rom_identify_8_16(&in[0x10]);
                    
                    genesis_rom_reset_16();
                    genesis_rom_identify(&in[0x20]);

                    USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (uint8_t*) & PacketToPC, USBGEN_EP_SIZE);
                    rqCmd = 0;
                    AppState = IDLE;
                }
                break;
                
            case ROM_WRITE:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                rom_reset_8();
                
                AppState = PENDING_OPERATION;
                
                break;
                
            case ROM_WRITE_8_16:
            case ROM_WRITE_PAGE_8_16:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                rom_reset_8_16();
                
                AppState = PENDING_OPERATION;
                
                break;                
                
            case ROM_WRITE_UNLOCKED_AMD:                
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                rom_reset_8_16();
                
                AppState = PENDING_OPERATION;
                
                // send unlock cmd
                amd_unlock_write_start();
                break;
                
            case ROM_READ_16:
            case ROM_READ_8:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                        
                rom_reset_8();
                
                AppState = PENDING_OPERATION;    
                
                break;
                
            case GENESIS_ROM_WRITE:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
                genesis_rom_reset_16();
                
                AppState = PENDING_OPERATION;    
                break;
                
                // genesis
            case GENESIS_SRAM_WRITE:
            case GENESIS_SRAM_READ:
            case GENESIS_ROM_READ:
                // snes
            case SNES_SRAM_WRITE:
            case SNES_ROM_READ:    
            case SNES_SRAM_READ:
                cmd_op_addr = rqArg0;
                cmd_op_size = rqArg1;
                
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
                
            default:
                break;
        }
    }
}
