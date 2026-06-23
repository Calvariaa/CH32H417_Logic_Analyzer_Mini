################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32h417_it.c \
../User/main.c \
../User/system_ch32h417.c 

C_DEPS += \
./User/ch32h417_it.d \
./User/main.d \
./User/system_ch32h417.d 

OBJS += \
./User/ch32h417_it.o \
./User/main.o \
./User/system_ch32h417.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/V3F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

