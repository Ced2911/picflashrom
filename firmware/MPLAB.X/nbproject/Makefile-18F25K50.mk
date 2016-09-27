#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-18F25K50.mk)" "nbproject/Makefile-local-18F25K50.mk"
include nbproject/Makefile-local-18F25K50.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=18F25K50
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic18f25K50/system.c ../src/main.c ../src/mcp23s17.c ../src/command.c ../src/spi.c ../src/app_usb.c ../src/rom.c ../framework/usb/src/usb_device_generic.c ../framework/usb/src/usb_device.c ../src/vendor/usb_descriptors.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/407776489/system.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1 ${OBJECTDIR}/_ext/1360937237/command.p1 ${OBJECTDIR}/_ext/1360937237/spi.p1 ${OBJECTDIR}/_ext/1360937237/app_usb.p1 ${OBJECTDIR}/_ext/1360937237/rom.p1 ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1 ${OBJECTDIR}/_ext/2142726457/usb_device.p1 ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/407776489/system.p1.d ${OBJECTDIR}/_ext/1360937237/main.p1.d ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d ${OBJECTDIR}/_ext/1360937237/command.p1.d ${OBJECTDIR}/_ext/1360937237/spi.p1.d ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d ${OBJECTDIR}/_ext/1360937237/rom.p1.d ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/407776489/system.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1 ${OBJECTDIR}/_ext/1360937237/command.p1 ${OBJECTDIR}/_ext/1360937237/spi.p1 ${OBJECTDIR}/_ext/1360937237/app_usb.p1 ${OBJECTDIR}/_ext/1360937237/rom.p1 ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1 ${OBJECTDIR}/_ext/2142726457/usb_device.p1 ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1

# Source Files
SOURCEFILES=../src/system_config/pic18f25K50/system.c ../src/main.c ../src/mcp23s17.c ../src/command.c ../src/spi.c ../src/app_usb.c ../src/rom.c ../framework/usb/src/usb_device_generic.c ../framework/usb/src/usb_device.c ../src/vendor/usb_descriptors.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC18F25K50
ProjectDir="I:\console\github\firmware\MPLAB.X"
ConfName=18F25K50
ImagePath="dist\18F25K50\${IMAGE_TYPE}\MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\18F25K50\${IMAGE_TYPE}"
ImageName="MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-18F25K50.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} "../../firm.c.hex"]"
	@copy ${ImagePath} "../../firm.c.hex"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=18F25K50
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/407776489/system.p1: ../src/system_config/pic18f25K50/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/407776489" 
	@${RM} ${OBJECTDIR}/_ext/407776489/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/407776489/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/407776489/system.p1  ../src/system_config/pic18f25K50/system.c 
	@-${MV} ${OBJECTDIR}/_ext/407776489/system.d ${OBJECTDIR}/_ext/407776489/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/407776489/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/mcp23s17.p1: ../src/mcp23s17.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/mcp23s17.p1  ../src/mcp23s17.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/mcp23s17.d ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/command.p1: ../src/command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/command.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/command.p1  ../src/command.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/command.d ${OBJECTDIR}/_ext/1360937237/command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/spi.p1: ../src/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/spi.p1  ../src/spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/spi.d ${OBJECTDIR}/_ext/1360937237/spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_usb.p1: ../src/app_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_usb.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_usb.p1  ../src/app_usb.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_usb.d ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/rom.p1: ../src/rom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/rom.p1  ../src/rom.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/rom.d ${OBJECTDIR}/_ext/1360937237/rom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/rom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1: ../framework/usb/src/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1  ../framework/usb/src/usb_device_generic.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.d ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device.p1: ../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2142726457/usb_device.p1  ../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device.d ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/140694402/usb_descriptors.p1: ../src/vendor/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/140694402" 
	@${RM} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/140694402/usb_descriptors.p1  ../src/vendor/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/140694402/usb_descriptors.d ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/407776489/system.p1: ../src/system_config/pic18f25K50/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/407776489" 
	@${RM} ${OBJECTDIR}/_ext/407776489/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/407776489/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/407776489/system.p1  ../src/system_config/pic18f25K50/system.c 
	@-${MV} ${OBJECTDIR}/_ext/407776489/system.d ${OBJECTDIR}/_ext/407776489/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/407776489/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/mcp23s17.p1: ../src/mcp23s17.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/mcp23s17.p1  ../src/mcp23s17.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/mcp23s17.d ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/mcp23s17.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/command.p1: ../src/command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/command.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/command.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/command.p1  ../src/command.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/command.d ${OBJECTDIR}/_ext/1360937237/command.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/command.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/spi.p1: ../src/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/spi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/spi.p1  ../src/spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/spi.d ${OBJECTDIR}/_ext/1360937237/spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_usb.p1: ../src/app_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_usb.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_usb.p1  ../src/app_usb.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_usb.d ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_usb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/rom.p1: ../src/rom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rom.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/rom.p1  ../src/rom.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/rom.d ${OBJECTDIR}/_ext/1360937237/rom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/rom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1: ../framework/usb/src/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1  ../framework/usb/src/usb_device_generic.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.d ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device_generic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device.p1: ../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2142726457/usb_device.p1  ../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device.d ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/140694402/usb_descriptors.p1: ../src/vendor/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/140694402" 
	@${RM} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/140694402/usb_descriptors.p1  ../src/vendor/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/140694402/usb_descriptors.d ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/140694402/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --rom=default,-0-FFF,-1006-1007,-1016-1017 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../bsp/pic18F25K50" -I"../src/system_config/pic18F25K50" -I"C:/Program Files (x86)/Microchip/xc8/v1.37/include/plib" -I"../framework/usb/inc" -I"../src/vendor" --warn=0 --asmlist -DXPRJ_18F25K50=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --codeoffset=0x1000 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/18F25K50
	${RM} -r dist/18F25K50

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
