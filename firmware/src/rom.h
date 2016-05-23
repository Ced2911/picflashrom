/* 
 * File:   rom.h
 * Author: cc
 *
 * Created on 28 avril 2016, 09:04
 */

#ifndef ROM_H
#define	ROM_H

void rom_init();
void rom_start_read();
void rom_start_write();

/* generic read */
void rom_read(uint8_t * out, uint32_t addr, uint8_t len);
void rom_read_16(uint8_t * out, uint32_t addr, uint8_t len);

/* generic write */
void rom_write(uint8_t * out, uint32_t addr, uint8_t len);
void rom_write_16(uint8_t * out, uint32_t addr, uint8_t len) ;

/* generic ID */
void rom_identify(uint8_t * in);

/* sst write */
void SST39xx_rom_erase(uint8_t * in);
void SST39xx_rom_write(uint8_t * in, uint32_t addr, uint8_t len);

#endif	/* ROM_H */

