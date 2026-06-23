################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/ch32h417_usbfs_device.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/ch32h417_usbhs_device.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/usb_desc.c \
e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/usb_inf.c 

C_DEPS += \
./Common/USB/ch32h417_usbfs_device.d \
./Common/USB/ch32h417_usbhs_device.d \
./Common/USB/usb_desc.d \
./Common/USB/usb_inf.d 

OBJS += \
./Common/USB/ch32h417_usbfs_device.o \
./Common/USB/ch32h417_usbhs_device.o \
./Common/USB/usb_desc.o \
./Common/USB/usb_inf.o 

DIR_OBJS += \
./Common/USB/*.o \

DIR_DEPS += \
./Common/USB/*.d \

DIR_EXPANDS += \
./Common/USB/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Common/USB/ch32h417_usbfs_device.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/ch32h417_usbfs_device.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/V3F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/USB/ch32h417_usbhs_device.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/ch32h417_usbhs_device.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/V3F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/USB/usb_desc.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/usb_desc.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/V3F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Common/USB/usb_inf.o: e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB/usb_inf.c
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DCore_V3F -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/Debug" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Core" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/V3F/User" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/SRC/Peripheral/inc" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common" -I"e:/程序代码/分析仪/USB分析仪/V2.0/程序/260519/CH32H417_Logic_Analyzer_SourceCode_20260518B/CH32H417_Logic_Analyzer_IAP/Common/USB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

