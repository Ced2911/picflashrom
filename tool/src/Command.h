#pragma once

#include "hidapi.h"
#include "ccrwrom.h"

//Bootloader Command From Host - Switch() State Variable Choices
#define QUERY_DEVICE                0x02    //Command that the host uses to learn about the device (what regions can be programmed, and what type of memory is the region)
#define UNLOCK_CONFIG               0x03    //Note, this command is used for both locking and unlocking the config bits (see the "//Unlock Configs Command Definitions" below)
#define ERASE_DEVICE                0x04    //Host sends this command to start an erase operation.  Firmware controls which pages should be erased.
#define PROGRAM_DEVICE              0x05    //If host is going to send a full RequestDataBlockSize to be programmed, it uses this command.
#define PROGRAM_COMPLETE            0x06    //If host send less than a RequestDataBlockSize to be programmed, or if it wished to program whatever was left in the buffer, it uses this command.
#define GET_DATA                    0x07    //The host sends this command in order to read out memory from the device.  Used during verify (and read/export hex operations)
#define RESET_DEVICE                0x08    //Resets the microcontroller, so it can update the config bits (if they were programmed, and so as to leave the bootloader (and potentially go back into the main application)
#define SIGN_FLASH                  0x09    //The host PC application should send this command after the verify operation has completed successfully.  If checksums are used instead of a true verify (due to ALLOW_GET_DATA_COMMAND being commented), then the host PC application should send SIGN_FLASH command after is has verified the checksums are as exected. The firmware will then program the SIGNATURE_WORD into flash at the SIGNATURE_ADDRESS.
#define QUERY_EXTENDED_INFO         0x0C    //Used by host PC app to get additional info about the device, beyond the basic NVM layout provided by the query device command
#define TO_BOOLOADER                0x28    // go to bootloader
#define PROM_READ                   0x40    // read prom
#define PROM_BULK_READ              0x42    // read prom
#define PROM_BULK_WRITE             0x44    // write prom
#define PROM_WRITE_FINISHED         0x45    // write erom
#define PROM_ID                     0x50    // read id
#define JEDEC_ERASE                 0x60    // erase erom
#define JEDEC_WRITE                 0x62    // write erom
#define CMD_AA                      0xAA
#define CMD_AB                      0xAB
#define CMD_AC                      0xAC

hid_device * usb_connect();

uint32_t usb_write(uint8_t * in, uint32_t size);
uint32_t usb_read(uint8_t * out, uint32_t size);

void cmd_bootloader();

uint32_t cmd_read_rom(uint8_t * out, uint32_t size);
uint32_t cmd_write_rom(uint8_t * in, uint32_t size);
void cmd_erase();
void cmd_read_id(uint8_t * out);

void cmd_query(uint8_t * in);