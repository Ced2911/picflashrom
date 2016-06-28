/* 
 * File:   spi.h
 * Author: cc
 *
 * Created on 20 avril 2016, 09:47
 */

#ifndef SPI_H
#define	SPI_H

void SPI1_Initialize(void);
inline void SPI1_Write8bit(uint8_t data);
uint8_t SPI1_Exchange8bit(uint8_t data);
uint8_t SPI1_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
bool SPI1_IsBufferFull(void);
bool SPI1_HasWriteCollisionOccured(void);
void SPI1_ClearWriteCollisionStatus(void);

#endif	/* SPI_H */

