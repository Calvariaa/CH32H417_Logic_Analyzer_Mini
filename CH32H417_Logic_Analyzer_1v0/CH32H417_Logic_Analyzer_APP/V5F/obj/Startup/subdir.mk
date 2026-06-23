################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Startup/startup_ch32h417_v5f.S 

S_UPPER_DEPS += \
./Startup/startup_ch32h417_v5f.d 

OBJS += \
./Startup/startup_ch32h417_v5f.o 

DIR_OBJS += \
./Startup/*.o \

DIR_DEPS += \
./Startup/*.d \

DIR_EXPANDS += \
./Startup/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32h417_v5f.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Startup/startup_ch32h417_v5f.S
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -x assembler-with-cpp -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

