/* 
 * File:   command.h
 * Author: cc
 *
 * Created on 15 avril 2016, 17:09
 */

#ifndef COMMAND_H
#define	COMMAND_H


/** command **/
void cmd_get_firmware_version();
void cmd_send_hello();
void cmd_spi_init();
void cmd_reset();
void cmd_bootloader();
void cmd_read_rom(uint8_t *out, uint32_t addr, uint8_t len);


void cmd_led_on();
void cmd_led_off();

#endif	/* COMMAND_H */

