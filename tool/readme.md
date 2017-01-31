ccrwrom
===================
Homemade flash programmer,
Read/Write 16bit/8bit eeprom
Transform card into flashcard !

Compatibility
-------------
**Nor/Flash based eeprom**

Name| Size
-------- | ---
SST39SF040 | 4MB
MX29LV160 | 16MB
MX29LV320 | 32MB
MX29LV640 | 64MB
MX29L3211 | 32MB
AM29LV160D | 16MB

**SNES Cartdrige support**

Type | Sram saving/reading | Write support
-------- | --- | ---
LoROM| Yes | Todo
HiROM| Yes | Yes
ExLoROM| Todo | Todo
ExHiROM| Todo | Todo


**SEGA Megadrive/Genesis cartdrige support**

Type | save type | save saving/reading | Write support
-------- | --- | --- | ---
Up to 32MB cart | none | none | Yes
Up to 16MB cart | SRAM/FRAM | Yes | Yes
16MB to 32MB cart | SRAM/FRAM | Todo | Yes
Up to 32MB cart | I2C| Todo | Yes
Up to 32MB cart | SPI| Todo | Yes

Usage
---------
###SNES
####Read rom
	ccrwrom -r filename -c snes
####Read sram
	ccrwrom -r filename -c snes -a sram
####Write rom
	ccrwrom -w filename -c snes

>**Note:** You need to add a wire between **!WE** on programmator and **!WE** on eeprom

####Write sram
	ccrwrom -w filename -c snes -a sram
	
###SEGA Genesis/MegaDrive
####Read rom
	ccrwrom -r filename -c genesis
####Read sram
	ccrwrom -r filename -c genesis -a sram
####Write rom
	ccrwrom -w filename -c genesis

>**Note:** You need to add a wire between **!WE** on programmator and **!WE** on eeprom

####Write sram
	ccrwrom -w filename -c genesis -a sram

###Raw command
####Read rom
	ccrwrom -r filename -m sizeInMB
> **Note:** Can be used for write

	ccrwrom -r filename -s sizeInBytes
> **Note:** Can be used for write

####Write rom
	ccrwrom -w filename

> **Note:** Use the size from the specified file

	ccrwrom -w filename -m sizeInMB

> **Note:** Use the size from the command line

####Erase rom
	ccrwrom -e
####Identify rom
	ccrwrom -i
