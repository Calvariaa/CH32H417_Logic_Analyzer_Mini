/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2025/05/07
 * Description        : Main program body for V3F.
 *********************************************************************************
 * Copyright (c) 2025 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "ch32h417_usbhs_device.h"
#include "ch32h417_usbss_device.h"
#include "debug.h"
#include "hardware.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 *
 */
int main(void)
{
    SystemInit();
    SystemAndCoreClockUpdate();

    /*  The current in the VDD12 power domain of the chip is relatively high. 
     If the VDD12 power supply is externally provided and the internal LDO is turned off, 
     the following function can be executed to reduce the chip's power consumption and 
     alleviate overheating. Note that this operation should only be performed when the 
     external 1.2V power supply has stabilized.*/
    //    PWR_VDD12ExternPower();
    Delay_Init();
    USART_Printf_Init(921600);

    DBG_PRINT("SystemClk:%d\r\n", SystemClock);
    DBG_PRINT("V3F SystemCoreClk:%d\r\n", SystemCoreClock);
#if (Run_Core == Run_Core_V3FandV5F)
    NVIC_WakeUp_V5F(Core_V5F_StartAddr);    //wake up V5
    HSEM_ITConfig(HSEM_ID0, ENABLE);
    NVIC->SCTLR |= 1 << 4;
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR, ENABLE);
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
    HSEM_ClearFlag(HSEM_ID0);
    DBG_PRINT("V3F wake up\r\n");

    Hardware();

#elif (Run_Core == Run_Core_V3F)
    Hardware();

#elif (Run_Core == Run_Core_V5F)

    NVIC_WakeUp_V5F(Core_V5F_StartAddr);    //wake up V5
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
    DBG_PRINT("V3F wake up\r\n");
#endif

    while(1)
    {
    }
}
