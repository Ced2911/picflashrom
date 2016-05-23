
/*************************************************************
I2C.C

This program contains I2C routines for the MCP23X08 and MCP23X17

Written for C18 compiler vX.XX
**************************************************************/

#include	<xc.h>
#include 	"i2c.h"

/********************************************************************
*   Function Name:  OpenI2C1                                        *
*   Return Value:   void                                            *
*   Parameters:     SSP1 peripheral setup bytes                     *
*   Description:    This function sets up the SSP1 module on a      * 
*                   PIC18CXXX device for use with a Microchip I2C   *
*                   EEPROM device or I2C bus device.                *
********************************************************************/
void OpenI2C(unsigned char sync_mode, unsigned char slew)
{
  SSPSTAT &= 0x3F;                // power on state 
  SSPCON1 = 0x00;                 // power on state
  SSPCON2 = 0x00;                 // power on state
  SSPCON1 |= sync_mode;           // select serial mode 
  SSPSTAT |= slew;                // slew rate on/off 

  SSPCON1bits.SSPEN = 1;          // enable synchronous serial port 
}

/********************************************************************
*     Function Name:    I2CStart   	                              	*
*     Return Value:     void           													    *
*     Parameters:       void                                        *
*     Description:      																            *
********************************************************************/
void I2CStart()
{
  PIR1bits.SSPIF = 0;
  SSPCON2bits.SEN=1;
  while(!PIR1bits.SSPIF);
  PIR1bits.SSPIF = 0;
}
  
/********************************************************************
*     Function Name:    I2CReStart   	                              *
*     Return Value:     void           													    *
*     Parameters:       void                                        *
*     Description:      																            *
********************************************************************/
void I2CReStart()
{
  PIR1bits.SSPIF = 0;
  SSPCON2bits.RSEN = 1;
  while(!PIR1bits.SSPIF);
  PIR1bits.SSPIF = 0;
}

/********************************************************************
*     Function Name:    WaitForACK   	                              *
*     Return Value:     void           													    *
*     Parameters:       void                                        *
*     Description:      																            *
********************************************************************/
void WaitForACK()
{
  PIR1bits.SSPIF = 0;    
  while(!PIR1bits.SSPIF);
  PIR1bits.SSPIF = 0;
}

/********************************************************************
*     Function Name:    I2CStop      	                              *
*     Return Value:     void           													    *
*     Parameters:       void                                        *
*     Description:      Stop bit												            *
********************************************************************/
void I2CStop()
{
  PIR1bits.SSPIF = 0;
  if (!SSPSTATbits.P)
  {
    SSPCON2bits.PEN = 1;  //Stop condition
    while(SSPCON2bits.PEN); //wait for STOP
    if (PIR2bits.BCLIF)
    PIR2bits.BCLIF = 0;
    while(!PIR1bits.SSPIF);  //Wait for flag to set
    PIR1bits.SSPIF = 0;
  }
}

/********************************************************************
*     Function Name:    WriteI2C2                                   *
*     Return Value:     Status byte for WCOL detection.             *
*     Parameters:       Single data byte for I2C2 bus.              *
*     Description:      This routine writes a single byte to the    * 
*                       I2C2 bus.                                   *
********************************************************************/
unsigned char WriteI2C( unsigned char data_out )
{
  SSPBUF = data_out;           // write single byte to SSP2BUF
  if ( SSPCON1bits.WCOL )      // test if write collision occurred
    return ( -1 );              // if WCOL bit is set return negative #
  else
  {
    while( SSPSTATbits.BF );   // wait until write cycle is complete         
    return ( 0 );               // if WCOL bit is not set return non-negative #
  }
}

/********************************************************************
*     Function Name:    ReadI2C2                                    *
*     Return Value:     contents of SSP2BUF register                *
*     Parameters:       void                                        *
*     Description:      Read single byte from I2C2 bus.             *
********************************************************************/
unsigned char ReadI2C(void)
{
	while (SSPSTATbits.BF);
  SSPCON2bits.RCEN = 1;         // enable master for 1 byte reception
  while (!SSPSTATbits.BF);      // wait until byte received  
  return (SSPBUF);              // return with read byte 
}

/********************************************************************
*     Function Name:    AckI2C                                      *
*     Return Value:     void                                        *
*     Parameters:       void                                        *
*     Description:      Initiate ACK bus condition.                 *
********************************************************************/
void ACKI2C(void)
{
  PIR1bits.SSPIF = 0;
  SSPCON2bits.ACKDT = 0;           // set acknowledge bit state for ACK
  SSPCON2bits.ACKEN = 1;           // initiate bus acknowledge sequence
  while(!PIR1bits.SSPIF);
  PIR1bits.SSPIF = 0;
}

/********************************************************************
*     Function Name:    nACKI2C                                     *
*     Return Value:     void                                        *
*     Parameters:       void                                        *
*     Description:      Initiate no-ACK bus condition.              *
********************************************************************/
void nACK()
{
  PIR1bits.SSPIF = 0;
  SSPCON2bits.ACKDT = NACK;  //Disable ACK
  SSPCON2bits.ACKEN = 1;    //Start ACK sequence
  while(!PIR1bits.SSPIF);  //Wait for flag to set
  PIR1bits.SSPIF = 0;
}

/********************************************************************
*     Function Name:    I2CDataReady                                *
*     Return Value:     Buffer Full (BF) flag                       *
*     Parameters:       void                                        *
*     Description:      Checks if data is in the SSPBUF             *
********************************************************************/
unsigned char I2CDataReady()
{
  if (SSPSTATbits.BF)          // test if buffer full bit is set     
    return ( +1 );                // data in SSP2BUF register
  else
    return ( 0 );                 // no data in SSP2BUF register
}

/*************************************************************
**************************************************************/
void I2CReset()
{
  WriteI2C(0);
//  I2CStop();
}
