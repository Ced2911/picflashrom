/* 
 * File:   i2c.h
 * Author: cc
 *
 * Created on 18 avril 2016, 13:18
 */

#ifndef I2C_H
#define	I2C_H

/*************************************************************
I2C.h

This header file is for I2C routines.

Written for C18 compiler vX.XX
**************************************************************/
#define ACK  0
#define NACK 1

#define WrtCmd  0
#define RdCmd   1

extern void OpenI2C(unsigned char sync_mode, unsigned char slew);
extern void I2CReset(void);
extern void I2CStart(void);
extern void I2CReStart(void);
extern void I2CStop(void);
extern void WaitForACK(void);
extern void ACKI2C(void);
extern unsigned char WriteI2C(unsigned char data_out);
extern unsigned char ReadI2C(void);
extern void nACK(void);
extern unsigned char I2CDataReady(void);


#endif	/* I2C_H */

