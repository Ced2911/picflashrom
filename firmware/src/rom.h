/* 
 * File:   rom.h
 * Author: cc
 *
 * Created on 28 avril 2016, 09:04
 */

#ifndef ROM_H
#define	ROM_H

#define ROM_ERROR   1
#define ROM_OK      0

void rom_init();
void rom_start_read();
void rom_start_write();

/* generic read */
uint8_t rom_read(uint8_t * out, uint32_t addr, uint8_t len);
uint8_t rom_read_16(uint8_t * out, uint32_t addr, uint8_t len);

/* generic write */
uint8_t rom_erase(uint8_t * out);
uint8_t rom_write(uint8_t * out, uint32_t addr, uint8_t len);
uint8_t rom_write_8_16(uint8_t * out, uint32_t addr, uint8_t len) ;
uint8_t rom_write_16(uint8_t * out, uint32_t addr, uint8_t len) ;

/* generic ID */
uint8_t rom_identify(uint8_t * in);

/** work in 8bit but need 16bit command*/
uint8_t rom_erase_8_16(uint8_t * out);
uint8_t rom_write_8_16(uint8_t * out, uint32_t addr, uint8_t len) ;
uint8_t rom_identify_8_16(uint8_t * in);

uint8_t rom_custom(uint8_t data, uint32_t addr);
uint8_t rom_reset();
/* vendor specific */
void amd_unlock_write_start();
void amd_unlock_write_end();
uint8_t amd_unlock_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len);
uint8_t rom_page_write_8_16(uint8_t * in, uint32_t _addr, uint8_t _len);

#endif	/* ROM_H */

