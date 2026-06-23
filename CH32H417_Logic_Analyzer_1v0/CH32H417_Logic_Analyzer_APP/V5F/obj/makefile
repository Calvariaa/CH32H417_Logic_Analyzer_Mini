################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Core/subdir.mk
-include Common/Debug/subdir.mk
-include Common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
CH32H417_Logic_Analyzer_V5F.bin \
CH32H417_Logic_Analyzer_V5F.hex \

SECONDARY_LIST += \
CH32H417_Logic_Analyzer_V5F.lst \

SECONDARY_SIZE += \
CH32H417_Logic_Analyzer_V5F.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: CH32H417_Logic_Analyzer_V5F.elf secondary-outputs

# Tool invocations
CH32H417_Logic_Analyzer_V5F.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-wch-elf-gcc -march=rv32imac_zba_zbb_zbc_zbs_xw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "e:\程序代码\分析仪\USB分析仪\V2.0\程序\260519\CH32H417_Logic_Analyzer_SourceCode_20260518B\CH32H417_Logic_Analyzer_APP\Common\Ld\V5F\Link_v5f.ld" -nostartfiles -Xlinker --gc-sections -L"e:\程序代码\分析仪\USB分析仪\V2.0\程序\260519\CH32H417_Logic_Analyzer_SourceCode_20260518B\CH32H417_Logic_Analyzer_APP\Common" -Wl,-Map,"CH32H417_Logic_Analyzer_V5F.map" --specs=nano.specs --specs=nosys.specs -o "CH32H417_Logic_Analyzer_V5F.elf" $(OBJS) $(USER_OBJS) $(LIBS)
CH32H417_Logic_Analyzer_V5F.bin: CH32H417_Logic_Analyzer_V5F.elf
	@	riscv-wch-elf-objcopy -O binary "CH32H417_Logic_Analyzer_V5F.elf" "CH32H417_Logic_Analyzer_V5F.bin"
CH32H417_Logic_Analyzer_V5F.hex: CH32H417_Logic_Analyzer_V5F.elf
	@	riscv-wch-elf-objcopy -O ihex "CH32H417_Logic_Analyzer_V5F.elf" "CH32H417_Logic_Analyzer_V5F.hex"
CH32H417_Logic_Analyzer_V5F.lst: CH32H417_Logic_Analyzer_V5F.elf
	@	riscv-wch-elf-objdump --all-headers --demangle --disassemble -M xw "CH32H417_Logic_Analyzer_V5F.elf" > "CH32H417_Logic_Analyzer_V5F.lst"
CH32H417_Logic_Analyzer_V5F.siz: CH32H417_Logic_Analyzer_V5F.elf
	riscv-wch-elf-size --format=berkeley "CH32H417_Logic_Analyzer_V5F.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) CH32H417_Logic_Analyzer_V5F.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets