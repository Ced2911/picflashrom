#include "usb.h"
#include "usb_device_hid.h"
#include "usb_device.h"
#include <string.h>
#include "system_config.h"
#include "command.h"
#include "rom.h"

void cmd_reset() {
    UCONbits.SUSPND = 0;    
    UCON = 0x00;
    __delay_ms(10);
    // reset mcu
    Reset();
    Nop();
    Nop();
}

void cmd_bootloader() {
    //USBDisableWithLongDelay();
    UCONbits.SUSPND = 0;    
    UCON = 0x00;
    __delay_ms(10);
#asm
    goto BOOTLOADER_ABSOLUTE_ENTRY_ADDRESS
#endasm
    Nop();
    Nop();
}

void cmd_get_firmware_version() {
    char _data[] = {0};
}

void cmd_send_hello() {
}

void cmd_init() {    
    led_init();
    cmd_led_on();
}

void cmd_led_on() {
    led_on();
}

void cmd_led_off() {
    led_off();
}

