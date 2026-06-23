################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_logic.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_uhsif.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbhs_device.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbss_device.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbss_it.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/hardware.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/usb_desc.c 

C_DEPS += \
./Common/ch32h417_logic.d \
./Common/ch32h417_uhsif.d \
./Common/ch32h417_usbhs_device.d \
./Common/ch32h417_usbss_device.d \
./Common/ch32h417_usbss_it.d \
./Common/hardware.d \
./Common/usb_desc.d 

OBJS += \
./Common/ch32h417_logic.o \
./Common/ch32h417_uhsif.o \
./Common/ch32h417_usbhs_device.o \
./Common/ch32h417_usbss_device.o \
./Common/ch32h417_usbss_it.o \
./Common/hardware.o \
./Common/usb_desc.o 

DIR_OBJS += \
./Common/*.o \

DIR_DEPS += \
./Common/*.d \

DIR_EXPANDS += \
./Common/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Common/ch32h417_logic.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_logic.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/ch32h417_uhsif.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_uhsif.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/ch32h417_usbhs_device.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbhs_device.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/ch32h417_usbss_device.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbss_device.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/ch32h417_usbss_it.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/ch32h417_usbss_it.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/hardware.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/hardware.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/usb_desc.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/usb_desc.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V5F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/V5F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_APP/Common" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

