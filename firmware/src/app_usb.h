#ifndef APP_USB_H
#define	APP_USB_H

//BootState Variable States
#define IDLE                        0x00
#define NOT_IDLE                    0x01
#define PENDING_OPERATION           0x02

#define CMD_READ_IN_PROGRESS        0x10
#define CMD_READ_WAIT_TRANSFER      0x11
#define CMD_READ_FINISHED           0x12

#define CMD_WRITE_IN_PROGRESS       0x20
#define CMD_WRITE_WAIT_TRANSFER     0x21
#define CMD_WRITE_FINISHED          0x22

#define USB_PACKET_SIZE             0x40
#define REQUEST_DATA_BLOCK_SIZE     0x3A    //Number of data bytes in a standard request to the PC.  Must be an even number from 2-58 (0x02-0x3A).  Larger numbers make better use of USB bandwidth and 
                                            //yeild shorter program/verify times, but require more micrcontroller RAM for buffer space.


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
#define PROM_ID_8_16                0x51    // read id
#define ROM_ERASE                   0x60    // erase erom
#define ROM_ERASE_8_16              0x61    // erase erom
#define ROM_WRITE                   0x70    // write erom
#define ROM_WRITE_8_16              0x71    // write erom
#define ROM_WRITE_UNLOCKED_AMD      0x72    // write erom
#define ROM_WRITE_PAGE_8_16         0x73    // write page
#define CMD_DBG                     0xDB    // DBG COMMAND
#define CMD_AA                      0xAA
#define CMD_AB                      0xAB
#define CMD_AC                      0xAC


/** USB Packet Request/Response Formatting Structure **********************************************************/
typedef union 
{
        unsigned char Contents[USB_PACKET_SIZE];

        //General command (with data in it) packet structure used by PROGRAM_DEVICE and GET_DATA commands       
        struct{
            unsigned char command;
            unsigned long address;
            unsigned char size;
            //unsigned char PadBytes[58-REQUEST_DATA_BLOCK_SIZE]; //Uncomment this if using a smaller than 0x3A RequestDataBlockSize.  Compiler doesn't like 0 byte array when using 58 byte data block size.
            unsigned char byte[REQUEST_DATA_BLOCK_SIZE];
        };
        
        //General command (with data in it) packet structure used by PROGRAM_DEVICE and GET_DATA commands       
        struct{
            unsigned char RomCommand;
            uint32_t RomAddress;
            uint32_t RomSize;
        };
        
        //This struct used for responding to QUERY_DEVICE command (on a device with four programmable sections)
        struct{
            unsigned char Command;
            unsigned char PacketDataFieldSize;
            unsigned char BytesPerAddress;
            unsigned char Type1;
            unsigned long Address1;
            unsigned long Length1;
            unsigned char Type2;
            unsigned long Address2;
            unsigned long Length2;
            unsigned char Type3;
            unsigned long Address3;
            unsigned long Length3;
            unsigned char Type4;
            unsigned long Address4;
            unsigned long Length4;                      
            unsigned char Type5;
            unsigned long Address5;
            unsigned long Length5;
            unsigned char Type6;
            unsigned long Address6;
            unsigned long Length6;  
            unsigned char VersionFlag;      //Used by host software to identify if device is new enough to support QUERY_EXTENDED_INFO command  
            unsigned char ExtraPadBytes[7];
        };  
        
        struct{                     //For UNLOCK_CONFIG command
            unsigned char Command;
            unsigned char LockValue;
        };
        
        //Structure for the QUERY_EXTENDED_INFO command (and response)
        struct{
            unsigned char Command;
            unsigned int BootloaderVersion;
            unsigned int ApplicationVersion;
            unsigned long SignatureAddress;
            unsigned int SignatureValue;
            unsigned long ErasePageSize;
            unsigned char Config1LMask;
            unsigned char Config1HMask;
            unsigned char Config2LMask;
            unsigned char Config2HMask;
            unsigned char Config3LMask;
            unsigned char Config3HMask;
            unsigned char Config4LMask;
            unsigned char Config4HMask;
            unsigned char Config5LMask;
            unsigned char Config5HMask;
            unsigned char Config6LMask;
            unsigned char Config6HMask;
            unsigned char Config7LMask;
            unsigned char Config7HMask;
        };          
} PacketToFromPC;


extern void APP_USBInitialize();
extern void APP_USBStart();
extern void APP_USBTasks();
extern void APP_USBCheckVendorRequest();

#endif