/********************************** (C) COPYRIGHT  *******************************
* File Name          : hardware.c
* Author             : Q2H2
* Version            : V1.0.0
* Date               : 2026/04/29
* Description        : This file main functions.
********************************************************************************/
#include "hardware.h"
#include "ch32h417_usbss_device.h"
#include "ch32h417_usbhs_device.h"
#include "ch32h417_logic.h"

uint16_t DAC_Value[7] = {700, 600, 500, 0, 750, 750, 750};    // Voltage must be less than 0.6V before it can be increased. When it is 0, it is 3.3V

/*********************************************************************
 * @fn      VDDI8_IO_Change
 *
 * @brief   Turn off the internal 1.8v power supply .
 *
 * @param   none
 *
 * @return  none
 */
void VDDI8_IO_Change(void)
{
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR, ENABLE);
    PWR->CTLR |= PWR_CTLR_VIO_SWCR;
    PWR->CTLR &= ~PWR_CTLR_VSEL_VIO18;
    PWR->CTLR = PWR->CTLR | PWR_CTLR_VSEL_VIO18_MODE5;
    Dac_Init(); /* Default output 3.3V power supply */
}

/*********************************************************************
 * @fn      Hardware
 *
 * @brief   Logic&Adc main process
 *
 * @param   none
 *
 * @return  none
 */
void Hardware(void)
{
    /* Disable SWD */
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    /* Enable the IO function of PC6 pins */
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_SWPMI, ENABLE);
    SWPMI->OR |= SWPMI_SWP_TBYP;
    /* Parameter initialization */
    LOGIC_Para_Init(); 
    Led_Time_Init();
    Delay_Ms(100);
    VDDI8_IO_Change();                                                          /* Turn off VDDIO-1.8V power supply */
    Get_Flash_Size();                                                           /* Get FLASH size for IAP upgrade */
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOF | RCC_HB2Periph_HSADC, ENABLE);   /* Enable ADC clock */
    RCC_HSADCCLKConfig(RCC_HSADCSource_PLLCLK);                                 /* Enable ADC PLL */
    /* USB initialization */
    USB_Timer_Init();
    USBSS_Device_Init(ENABLE);
    while(1)
    {
        LOGIC_ADC_CMD_Process();                                                /* Logic analyzer and ADC acquisition parameter setting main function */
        LOGIC_UHSIF_Main_Process();                                             /* Logic analyzer data transfer main function */
        LOGIC_ADC_Main_Process();                                               /* ADC data acquisition main function */
        LOGIC_ADC_RAMOVER_Process();                                            /* Report buffer overflow main function */
        IAP_JUMP_Process();                                                     /* IAP processing main function */
    }
}
