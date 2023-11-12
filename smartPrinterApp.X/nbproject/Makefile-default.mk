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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/gd32f30x_it.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/gd32f30x_it.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/gd32f30x_it.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/gd32f30x_it.o

# Source Files
SOURCEFILES=src/main.c src/gd32f30x_it.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${DFP_DIR}/include"  -I "${CMSIS_DIR}/CMSIS/Core/Include"



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
_/_=\\
ShExtension=.bat
Device=ATSAME53J18A
ProjectDir="E:\New Version Theraml\smartPrinterApp.X"
ProjectName=smartPrinterApp
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [   arm-none-eabi-objdump -D dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.elf -Mforce-thumb > dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.S         && arm-none-eabi-objcopy dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.elf  dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.bin -O binary]"
	@   arm-none-eabi-objdump -D dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.elf -Mforce-thumb > dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.S         && arm-none-eabi-objcopy dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.elf  dist\default\${IMAGE_TYPE}\smartPrinterApp.x.${IMAGE_TYPE}.bin -O binary
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=SAME53J18A
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/c599b8164e565de55903aae25dfd8ae427381ef5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "libs/GD32f30x/inc/CMSIS" -I "libs/GD32f30x/inc/CMSIS/GD/GD32F30x/Include" -I "libs/GD32f30x/inc/Peripherals" -I "libs/USBD/inc/device/class/printer/Include" -I "libs/USBD/inc/device/core/Include" -I "libs/USBD/inc/driver/Include" -I "libs/USBD/inc/ustd/class/cdc" -I "libs/USBD/inc/ustd/class/hid" -I "libs/USBD/inc/ustd/class/msc" -I "libs/USBD/inc/ustd/common" -I "inc" -I "libs/smartPrinter/inc" -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/gd32f30x_it.o: src/gd32f30x_it.c  .generated_files/flags/default/9d6973f729f763f8b233d48aa7dcbb263ce2385c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gd32f30x_it.o.d 
	@${RM} ${OBJECTDIR}/src/gd32f30x_it.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "libs/GD32f30x/inc/CMSIS" -I "libs/GD32f30x/inc/CMSIS/GD/GD32F30x/Include" -I "libs/GD32f30x/inc/Peripherals" -I "libs/USBD/inc/device/class/printer/Include" -I "libs/USBD/inc/device/core/Include" -I "libs/USBD/inc/driver/Include" -I "libs/USBD/inc/ustd/class/cdc" -I "libs/USBD/inc/ustd/class/hid" -I "libs/USBD/inc/ustd/class/msc" -I "libs/USBD/inc/ustd/common" -I "inc" -I "libs/smartPrinter/inc" -Wall -MP -MMD -MF "${OBJECTDIR}/src/gd32f30x_it.o.d" -o ${OBJECTDIR}/src/gd32f30x_it.o src/gd32f30x_it.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/cbbdeebff434582957f604c432033f485022dbf9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "libs/GD32f30x/inc/CMSIS" -I "libs/GD32f30x/inc/CMSIS/GD/GD32F30x/Include" -I "libs/GD32f30x/inc/Peripherals" -I "libs/USBD/inc/device/class/printer/Include" -I "libs/USBD/inc/device/core/Include" -I "libs/USBD/inc/driver/Include" -I "libs/USBD/inc/ustd/class/cdc" -I "libs/USBD/inc/ustd/class/hid" -I "libs/USBD/inc/ustd/class/msc" -I "libs/USBD/inc/ustd/common" -I "inc" -I "libs/smartPrinter/inc" -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/gd32f30x_it.o: src/gd32f30x_it.c  .generated_files/flags/default/a35732bc50e6ccbd78488668ce549231c8c9146 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gd32f30x_it.o.d 
	@${RM} ${OBJECTDIR}/src/gd32f30x_it.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "libs/GD32f30x/inc/CMSIS" -I "libs/GD32f30x/inc/CMSIS/GD/GD32F30x/Include" -I "libs/GD32f30x/inc/Peripherals" -I "libs/USBD/inc/device/class/printer/Include" -I "libs/USBD/inc/device/core/Include" -I "libs/USBD/inc/driver/Include" -I "libs/USBD/inc/ustd/class/cdc" -I "libs/USBD/inc/ustd/class/hid" -I "libs/USBD/inc/ustd/class/msc" -I "libs/USBD/inc/ustd/common" -I "inc" -I "libs/smartPrinter/inc" -Wall -MP -MMD -MF "${OBJECTDIR}/src/gd32f30x_it.o.d" -o ${OBJECTDIR}/src/gd32f30x_it.o src/gd32f30x_it.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  libs/GD32f30x/src/GD32f30x.X.a libs/USBD/src/USBFS.X.a libs/smartPrinter/src/smartPrinter.X.a  gd32f30x_flash.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m4  -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -D__$(MP_PROCESSOR_OPTION)__   -T"gd32f30x_flash.ld"  -mthumb --specs=nosys.specs -Wl,-Map="${DISTDIR}\smartPrinterApp.X.${IMAGE_TYPE}.map"  -o ${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    libs\GD32f30x\src\GD32f30x.X.a libs\USBD\src\USBFS.X.a libs\smartPrinter\src\smartPrinter.X.a  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -Wl,--gc-sections  
	
	
	
	
	
	
else
${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  libs/GD32f30x/src/GD32f30x.X.a libs/USBD/src/USBFS.X.a libs/smartPrinter/src/smartPrinter.X.a gd32f30x_flash.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m4  -D__$(MP_PROCESSOR_OPTION)__   -T"gd32f30x_flash.ld"  -mthumb --specs=nosys.specs -Wl,-Map="${DISTDIR}\smartPrinterApp.X.${IMAGE_TYPE}.map"  -o ${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    libs\GD32f30x\src\GD32f30x.X.a libs\USBD\src\USBFS.X.a libs\smartPrinter\src\smartPrinter.X.a  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections  
	
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature "${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/smartPrinterApp.X.${IMAGE_TYPE}.hex"
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
