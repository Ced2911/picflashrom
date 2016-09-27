#include <xc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "spi.h"


/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0
#define DUMMY_DATA 0x0

#ifndef NULL
#define NULL    0
#endif // NULL

/**
  Section: Module APIs
*/

void SPI1_Initialize(void)
{
    // Set the SPI1 module to the options selected in the User Interface
    
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP Middle; UA dontupdate; CKE Idle to Active; D_nA lastbyte_address; 
    SSP1STAT = 0x40;
    
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4; SSPOV no_overflow; 
    SSP1CON1 = 0x22;
    
    // SSP1ADD 0; 
    SSP1ADD = 0x00;
}

inline void SPI1_Write8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSP1BUF = data;

    while(SSP1STATbits.BF == SPI_RX_IN_PROGRESS);
}

uint8_t SPI1_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSP1BUF = data;

    while(SSP1STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSP1BUF);
}

uint8_t SPI1_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    SPI1_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI1_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI1_Exchange8bit(DUMMY_DATA);

                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

bool SPI1_IsBufferFull(void)
{
    return (SSP1STATbits.BF);
}

bool SPI1_HasWriteCollisionOccured(void)
{
    return (SSP1CON1bits.WCOL);
}

void SPI1_ClearWriteCollisionStatus(void)
{
    SSP1CON1bits.WCOL = 0;
}
