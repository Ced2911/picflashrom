#include "vendor/usb_config.h"

#define _XTAL_FREQ 16000000
#define BOOTLOADER_ABSOLUTE_ENTRY_ADDRESS       0x001C  //Execute a "goto 0x001C" inline assembly instruction, if you want to enter the bootloader mode from the application via software
#define FIRMWARE_VERSION    1
