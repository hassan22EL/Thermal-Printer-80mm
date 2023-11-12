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
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/fonts/Fonts.c src/fonts/font_iso_8859_7_12x24.c src/fonts/font_iso_8859_7_8x16.c src/fonts/font_iso_8859_7_9x17.c src/escpos.c src/escpos_commands.c src/fifo.c src/PrintHead.c src/font.c src/userDefineChar_BitImageDownload.c src/usart.c src/xm25qh16b.c src/UserStatus.c src/cutOperation.c src/utility.c src/FeedButton.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/fonts/Fonts.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o ${OBJECTDIR}/src/escpos.o ${OBJECTDIR}/src/escpos_commands.o ${OBJECTDIR}/src/fifo.o ${OBJECTDIR}/src/PrintHead.o ${OBJECTDIR}/src/font.o ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o ${OBJECTDIR}/src/usart.o ${OBJECTDIR}/src/xm25qh16b.o ${OBJECTDIR}/src/UserStatus.o ${OBJECTDIR}/src/cutOperation.o ${OBJECTDIR}/src/utility.o ${OBJECTDIR}/src/FeedButton.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/fonts/Fonts.o.d ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o.d ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o.d ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o.d ${OBJECTDIR}/src/escpos.o.d ${OBJECTDIR}/src/escpos_commands.o.d ${OBJECTDIR}/src/fifo.o.d ${OBJECTDIR}/src/PrintHead.o.d ${OBJECTDIR}/src/font.o.d ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o.d ${OBJECTDIR}/src/usart.o.d ${OBJECTDIR}/src/xm25qh16b.o.d ${OBJECTDIR}/src/UserStatus.o.d ${OBJECTDIR}/src/cutOperation.o.d ${OBJECTDIR}/src/utility.o.d ${OBJECTDIR}/src/FeedButton.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/fonts/Fonts.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o ${OBJECTDIR}/src/escpos.o ${OBJECTDIR}/src/escpos_commands.o ${OBJECTDIR}/src/fifo.o ${OBJECTDIR}/src/PrintHead.o ${OBJECTDIR}/src/font.o ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o ${OBJECTDIR}/src/usart.o ${OBJECTDIR}/src/xm25qh16b.o ${OBJECTDIR}/src/UserStatus.o ${OBJECTDIR}/src/cutOperation.o ${OBJECTDIR}/src/utility.o ${OBJECTDIR}/src/FeedButton.o

# Source Files
SOURCEFILES=src/fonts/Fonts.c src/fonts/font_iso_8859_7_12x24.c src/fonts/font_iso_8859_7_8x16.c src/fonts/font_iso_8859_7_9x17.c src/escpos.c src/escpos_commands.c src/fifo.c src/PrintHead.c src/font.c src/userDefineChar_BitImageDownload.c src/usart.c src/xm25qh16b.c src/UserStatus.c src/cutOperation.c src/utility.c src/FeedButton.c

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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/fonts/Fonts.o: src/fonts/Fonts.c  .generated_files/flags/default/604f3d3b6e9ffbafd5aeee987558b482916ede8e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/Fonts.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/Fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/Fonts.o.d" -o ${OBJECTDIR}/src/fonts/Fonts.o src/fonts/Fonts.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o: src/fonts/font_iso_8859_7_12x24.c  .generated_files/flags/default/131a9095485e0a9db5b14c1206ea657e4e1bcbf8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o src/fonts/font_iso_8859_7_12x24.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o: src/fonts/font_iso_8859_7_8x16.c  .generated_files/flags/default/35518f5f67a4c8990706cc2baaabe227ab739148 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o src/fonts/font_iso_8859_7_8x16.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o: src/fonts/font_iso_8859_7_9x17.c  .generated_files/flags/default/ccd9c6903ecc9364e2c4725864a02080689f8222 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o src/fonts/font_iso_8859_7_9x17.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/escpos.o: src/escpos.c  .generated_files/flags/default/63b1cb7c3a1988694fb30c41ffde3a05a1976fec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/escpos.o.d 
	@${RM} ${OBJECTDIR}/src/escpos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/escpos.o.d" -o ${OBJECTDIR}/src/escpos.o src/escpos.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/escpos_commands.o: src/escpos_commands.c  .generated_files/flags/default/1a799f7ffe1f17c17ec800b264ab91416c1d129c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/escpos_commands.o.d 
	@${RM} ${OBJECTDIR}/src/escpos_commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/escpos_commands.o.d" -o ${OBJECTDIR}/src/escpos_commands.o src/escpos_commands.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fifo.o: src/fifo.c  .generated_files/flags/default/57e108c1c7ded44e60f3847387b8b11bc25e06b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fifo.o.d" -o ${OBJECTDIR}/src/fifo.o src/fifo.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintHead.o: src/PrintHead.c  .generated_files/flags/default/9eb0a1186ad7d053b6fea34751efab60acde3b16 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintHead.o.d 
	@${RM} ${OBJECTDIR}/src/PrintHead.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/PrintHead.o.d" -o ${OBJECTDIR}/src/PrintHead.o src/PrintHead.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/font.o: src/font.c  .generated_files/flags/default/7156505985e894b17f0d0e37469b3cbb198e443 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/font.o.d 
	@${RM} ${OBJECTDIR}/src/font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/font.o.d" -o ${OBJECTDIR}/src/font.o src/font.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/userDefineChar_BitImageDownload.o: src/userDefineChar_BitImageDownload.c  .generated_files/flags/default/5c9a822d8e9b98999aa9e70d510001df44712894 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o.d 
	@${RM} ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/userDefineChar_BitImageDownload.o.d" -o ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o src/userDefineChar_BitImageDownload.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/usart.o: src/usart.c  .generated_files/flags/default/a2d7eaa0cea8ba2d9b5b1265467cb16a8c543b8c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usart.o.d 
	@${RM} ${OBJECTDIR}/src/usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/usart.o.d" -o ${OBJECTDIR}/src/usart.o src/usart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/xm25qh16b.o: src/xm25qh16b.c  .generated_files/flags/default/f3ea3f7cba47cacb0d3778274209646a8ade04c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/xm25qh16b.o.d 
	@${RM} ${OBJECTDIR}/src/xm25qh16b.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/xm25qh16b.o.d" -o ${OBJECTDIR}/src/xm25qh16b.o src/xm25qh16b.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/UserStatus.o: src/UserStatus.c  .generated_files/flags/default/b6d0f43e18b8593a147ce5c74300aa6c485c8a58 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/UserStatus.o.d 
	@${RM} ${OBJECTDIR}/src/UserStatus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/UserStatus.o.d" -o ${OBJECTDIR}/src/UserStatus.o src/UserStatus.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/cutOperation.o: src/cutOperation.c  .generated_files/flags/default/6895a8fbea0ad29b7fac18fcac3a1a25cba2b3c0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/cutOperation.o.d 
	@${RM} ${OBJECTDIR}/src/cutOperation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/cutOperation.o.d" -o ${OBJECTDIR}/src/cutOperation.o src/cutOperation.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/utility.o: src/utility.c  .generated_files/flags/default/99400d79935d4b3187c6c05bfa4dc53e9ad1304e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/utility.o.d 
	@${RM} ${OBJECTDIR}/src/utility.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/utility.o.d" -o ${OBJECTDIR}/src/utility.o src/utility.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/FeedButton.o: src/FeedButton.c  .generated_files/flags/default/688ce01202996daee78360c63420a338d4c96dc9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FeedButton.o.d 
	@${RM} ${OBJECTDIR}/src/FeedButton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/FeedButton.o.d" -o ${OBJECTDIR}/src/FeedButton.o src/FeedButton.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/fonts/Fonts.o: src/fonts/Fonts.c  .generated_files/flags/default/4c779d614ee0772d4b5a806a88ddb552008518dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/Fonts.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/Fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/Fonts.o.d" -o ${OBJECTDIR}/src/fonts/Fonts.o src/fonts/Fonts.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o: src/fonts/font_iso_8859_7_12x24.c  .generated_files/flags/default/14561f6ea84e69c23ae198eae7c4d87ec5b3e496 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_12x24.o src/fonts/font_iso_8859_7_12x24.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o: src/fonts/font_iso_8859_7_8x16.c  .generated_files/flags/default/c4eeb6949d5220628c67bf7e0815e3320c9e0ed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_8x16.o src/fonts/font_iso_8859_7_8x16.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o: src/fonts/font_iso_8859_7_9x17.c  .generated_files/flags/default/c7517159377825631edf27081602474d3686836b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/fonts" 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o.d 
	@${RM} ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o.d" -o ${OBJECTDIR}/src/fonts/font_iso_8859_7_9x17.o src/fonts/font_iso_8859_7_9x17.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/escpos.o: src/escpos.c  .generated_files/flags/default/499736751d2c0737702e67a39d9ad87cd5ef91f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/escpos.o.d 
	@${RM} ${OBJECTDIR}/src/escpos.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/escpos.o.d" -o ${OBJECTDIR}/src/escpos.o src/escpos.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/escpos_commands.o: src/escpos_commands.c  .generated_files/flags/default/3c5639b5f7c2ae9c5101f692fc082a2cb707190b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/escpos_commands.o.d 
	@${RM} ${OBJECTDIR}/src/escpos_commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/escpos_commands.o.d" -o ${OBJECTDIR}/src/escpos_commands.o src/escpos_commands.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fifo.o: src/fifo.c  .generated_files/flags/default/a50e040168592217bd35bf75985906138e7b74cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/fifo.o.d" -o ${OBJECTDIR}/src/fifo.o src/fifo.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintHead.o: src/PrintHead.c  .generated_files/flags/default/829546073610f857840132db720e8c80c7e10471 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintHead.o.d 
	@${RM} ${OBJECTDIR}/src/PrintHead.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/PrintHead.o.d" -o ${OBJECTDIR}/src/PrintHead.o src/PrintHead.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/font.o: src/font.c  .generated_files/flags/default/729d6902881a728b49edee54ee67f73a43ef236a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/font.o.d 
	@${RM} ${OBJECTDIR}/src/font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/font.o.d" -o ${OBJECTDIR}/src/font.o src/font.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/userDefineChar_BitImageDownload.o: src/userDefineChar_BitImageDownload.c  .generated_files/flags/default/8f44721a259de64976360d228f75fb2dbfbec3a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o.d 
	@${RM} ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/userDefineChar_BitImageDownload.o.d" -o ${OBJECTDIR}/src/userDefineChar_BitImageDownload.o src/userDefineChar_BitImageDownload.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/usart.o: src/usart.c  .generated_files/flags/default/c58ed254e4f39da8f292dbea74e4630bfd90f078 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usart.o.d 
	@${RM} ${OBJECTDIR}/src/usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/usart.o.d" -o ${OBJECTDIR}/src/usart.o src/usart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/xm25qh16b.o: src/xm25qh16b.c  .generated_files/flags/default/1c2855c25b21dca43be458aa0ed166f82f78dda9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/xm25qh16b.o.d 
	@${RM} ${OBJECTDIR}/src/xm25qh16b.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/xm25qh16b.o.d" -o ${OBJECTDIR}/src/xm25qh16b.o src/xm25qh16b.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/UserStatus.o: src/UserStatus.c  .generated_files/flags/default/385b8a8cc145243f51a829b31f5194f0f34a5bad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/UserStatus.o.d 
	@${RM} ${OBJECTDIR}/src/UserStatus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/UserStatus.o.d" -o ${OBJECTDIR}/src/UserStatus.o src/UserStatus.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/cutOperation.o: src/cutOperation.c  .generated_files/flags/default/fd83c3b5d3f9d4cb80987eb19a440e9dee04de4c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/cutOperation.o.d 
	@${RM} ${OBJECTDIR}/src/cutOperation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/cutOperation.o.d" -o ${OBJECTDIR}/src/cutOperation.o src/cutOperation.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/utility.o: src/utility.c  .generated_files/flags/default/ce928b687495d50c266b4e304e3e3834be470313 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/utility.o.d 
	@${RM} ${OBJECTDIR}/src/utility.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/utility.o.d" -o ${OBJECTDIR}/src/utility.o src/utility.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/FeedButton.o: src/FeedButton.c  .generated_files/flags/default/672602516291e7fa50ff379301c0c146a1aa1bd0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FeedButton.o.d 
	@${RM} ${OBJECTDIR}/src/FeedButton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -O3 -ffunction-sections -ffast-math -mlong-calls -I "Core/GD32F307RC/inc/CMSIS/GD/GD32F30x/Include" -I "Core/GD32F307RC/inc/CMSIS" -I "Core/GD32F307RC/inc/Peripherals" -I "inc" -I "src/fonts" -I "src" -Wall -MP -MMD -MF "${OBJECTDIR}/src/FeedButton.o.d" -o ${OBJECTDIR}/src/FeedButton.o src/FeedButton.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -r ${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
else
${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -r ${DISTDIR}/smartPrinter.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
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
