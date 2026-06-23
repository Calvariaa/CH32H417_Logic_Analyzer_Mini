/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32h417_logic.c
 * Author             : Q2H2
 * Version            : V1.0.0
 * Date               : 2026/05/18
 * Description        : Core logic analyzer firmware functions for CH32H417, 
 *                      including clock configuration and HSADC handling.
 ********************************************************************************/
#include <string.h>
#include "ch32h417_logic.h"
#include "ch32h417_it.h"
#include "ch32h417_uhsif.h"
#include "ch32h417_usb.h"
#include "ch32h417_usbss_device.h"
#include "usb_desc.h"

uint8_t adc_flag = 0;
volatile uint16_t test_flag = 0;
volatile uint32_t Flash_Erase_Page_Size = Size_8KB;
LOGIC_ADC_PARA logic_adc_info;
__attribute__((aligned(32))) uint16_t ADC_BufA[ADC_BUF_LEN + 1024];    // HADC double buffer 1
__attribute__((aligned(32))) uint16_t ADC_BufB[ADC_BUF_LEN + 1024];    // HADC double buffer 2

void HSADC_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      UHSIF_Clock_Set
 *
 * @brief   Initializes Logic sys PLL & sys CLK.
 * @param   rcc_pll  See Bit definition for RCC_PLLCFGR register
 * @return  none
 */
void UHSIF_Clock_Set(uint32_t rcc_pll)
{
    RCC->CFGR0 = (RCC->CFGR0 & ~RCC_SW) | RCC_SW_HSI;
    while((RCC->CFGR0 & RCC_SWS) != RCC_SWS_HSI);    // Wait for clock to stabilize

    RCC->PLLCFGR &= ~0x80000000;
    RCC->CTLR &= ~RCC_PLLON;

    RCC->PLLCFGR &= (uint32_t)((uint32_t)~(RCC_PLLMUL));
    RCC->PLLCFGR |= (uint32_t)rcc_pll;
    RCC->PLLCFGR &= (uint32_t)((uint32_t)~(RCC_PLL_SRC_DIV));
    RCC->PLLCFGR |= (uint32_t)RCC_PLL_SRC_DIV1;
    RCC->PLLCFGR &= (uint32_t)((uint32_t)~(RCC_PLLSRC));
    RCC->PLLCFGR |= (uint32_t)RCC_PLLSRC_HSE;

    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0);
    RCC->PLLCFGR |= 0x80000000;

    RCC->CFGR0 = (RCC->CFGR0 & ~RCC_SW) | RCC_SW_PLL;    // Switch to PLL clock, wait for clock to stabilize
    while((RCC->CFGR0 & RCC_SWS) != RCC_SWS_PLL);
    SystemAndCoreClockUpdate();
    USART_Printf_Init(921600);    // Reinit baud rate
    Delay_Ms(100);                // Need delay time
}

/*********************************************************************
 * @fn      Set_Logic_Para_Fun
 *
 * @brief   Initializes Logic sys collection.
 *
 * @return  none
 */
void Set_Logic_Para_Fun(uint8_t logic_bit, uint8_t logic_sys)
{
    uint8_t uhsif_div;
    uint32_t rcc_pll;
    switch(logic_sys)
    {
    case 0x00:    // 200M  400/2
        rcc_pll = RCC_PLLMUL16;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x01:    // 187M 25*15/2 =187.5
        rcc_pll = RCC_PLLMUL15;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x02:    // 175  25*14/2 = 175
        rcc_pll = RCC_PLLMUL14;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x03:    // 162M 25*13/2 = 162.5
        rcc_pll = RCC_PLLMUL13;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x04:    // 156M  25*12.5/2 = 156.25
        rcc_pll = RCC_PLLMUL12_5;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x05:    // 25*12/2 = 150
        rcc_pll = RCC_PLLMUL12;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x06:    // 25*11/2 = 137.5
        rcc_pll = RCC_PLLMUL11;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x07:    // 25*10/2 = 125
        rcc_pll = RCC_PLLMUL10;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x08:    // 25*9/2 = 112.5
        rcc_pll = RCC_PLLMUL9;
        uhsif_div = RCC_UHSIFDIV_DIV2;
        break;
    case 0x09:    // 100
        rcc_pll = RCC_PLLMUL16;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0a:    // 187.5 /2 =
        rcc_pll = RCC_PLLMUL15;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0b:    // 25*14/2 = 175/2 = 87.5
        rcc_pll = RCC_PLLMUL14;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0c:    // 162.5/2 = 81.5
        rcc_pll = RCC_PLLMUL13;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0d:    // 156.25/2 = 78.125
        rcc_pll = RCC_PLLMUL12_5;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0e:    // 150/2 = 75
        rcc_pll = RCC_PLLMUL12;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    case 0x0f:    // 137.5/2 = 68.75
        rcc_pll = RCC_PLLMUL11;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    default:    // Default 100M
        rcc_pll = RCC_PLLMUL16;
        uhsif_div = RCC_UHSIFDIV_DIV4;
        break;
    }
    logic_adc_info.uhsif_div = uhsif_div;
    if(logic_adc_info.usb_status == USB_U2_CONNECT)
    {    // USB2.0 high speed, reconfigure buffer descriptor
        if(logic_bit == 8)
        {
            rcc_pll = RCC_PLLMUL16;                 // Default 400M
            uhsif_div = RCC_UHSIFDIV_DIV10;         // 10x divider, speed 40MB
        }
        else if(logic_bit == 16)
        {
            rcc_pll = RCC_PLLMUL16;                 // Default 400M
            uhsif_div = RCC_UHSIFDIV_DIV20;         // 20x divider, speed 20MB
        }
        logic_adc_info.uhsif_div = uhsif_div;
        UHSIF_Clock_Set(rcc_pll);                   // Configure system PLL clock
        UHSIF_Set_Para(logic_bit, uhsif_div);       // Configure parallel acquisition parameters
    }
    else
    {                                               // USB3.0 super speed
        UHSIF_Clock_Set(rcc_pll);                   // Configure system PLL clock
        UHSIF_Set_Para(logic_bit, uhsif_div);       // Configure parallel acquisition parameters
    }
}

/*********************************************************************
 * @fn      Dac_Init
 *
 * @brief   Initializes dac collection.
 *
 * @return  none
 */
void Dac_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    DAC_InitTypeDef DAC_InitType = { 0 };

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOA, ENABLE);
    RCC_HB1PeriphClockCmd(RCC_HB1Periph_DAC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    DAC_InitType.DAC_Trigger = DAC_Trigger_None;
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_2, &DAC_InitType);
    DAC_Cmd(DAC_Channel_2, ENABLE);
    DAC_SetChannel1Data(DAC_Align_12b_R, 34);    // Default output 0, voltage 3.3V
}

/*********************************************************************
 * @fn      DAC_OUT
 *
 * @brief    dac out data.
 *
 * @return  none
 */
void DAC_OUT(uint16_t dac_value)
{
    DAC_SetChannel1Data(DAC_Align_12b_R, dac_value);
}

/*********************************************************************
 * @fn      HSADC_Function_Init
 *
 * @brief   Initializes HSADC collection.
 * @return  none
 */
void HSADC_Function_Init(void)
{
    HSADC_InitTypeDef HSADC_InitStructure = { 0 };
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    if(logic_adc_info.adc_channel == ADC_CHANNEL0)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if(logic_adc_info.adc_channel == ADC_CHANNEL1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    HSADC_InitStructure.HSADC_BurstMode = ENABLE;
    HSADC_InitStructure.HSADC_DMA_TransferLen = ADC_BUF_LEN - 1;                // 1024*16-1; // 16K per acquisition
    HSADC_InitStructure.HSADC_BurstMode_TransferLen = 3;
    HSADC_InitStructure.HSADC_BurstMode_DMA_LastTransferLen = 16;

    HSADC_InitStructure.HSADC_ClockDivision = logic_adc_info.adc_div;           // ADC divider: 400/(adc_div+1)/5 = adc sys
    HSADC_InitStructure.HSADC_DMA = ENABLE;
    HSADC_InitStructure.HSADC_RxAddress0 = (uint32_t)ADC_BufA;
    HSADC_InitStructure.HSADC_RxAddress1 = (uint32_t)ADC_BufB;

    HSADC_InitStructure.HSADC_DualBuffer = ENABLE;
    HSADC_InitStructure.HSADC_FirstConversionCycle = HSADC_First_Conversion_Cycle_8;
    if(logic_adc_info.adc_bit == ADC_GET_WIDTH8)
    {
        HSADC_InitStructure.HSADC_DataSize = HSADC_DataSize_8b;
    }
    else if(logic_adc_info.adc_bit == ADC_GET_WIDTH10)
    {
        HSADC_InitStructure.HSADC_DataSize = HSADC_DataSize_16b;
    }
    HSADC_Init(&HSADC_InitStructure);
    if(logic_adc_info.adc_channel == ADC_CHANNEL0)
    {
        HSADC_ChannelConfig(HSADC_Channel_2);
    }
    else if(logic_adc_info.adc_channel == ADC_CHANNEL1)
    {
        HSADC_ChannelConfig(HSADC_Channel_3);
    }
    NVIC_EnableIRQ(HSADC_IRQn);
    NVIC_SetPriority(HSADC_IRQn, 2);
    HSADC_ITConfig(HSADC_IT_DMAEnd, ENABLE);
    logic_adc_info.usb30_endp3_up = USB_SUCESEE_FLAG;
    logic_adc_info.usb20_endp3_up = USB_SUCESEE_FLAG;
    logic_adc_info.adc_rec_total = 0;
    logic_adc_info.adc_flag = 0;
    logic_adc_info.usb_endp3_up_count = 0;
}

/*********************************************************************
 * @fn      HSADC_Function_Start
 *
 * @brief   Starts HSADC acquisition, reconfiguring system PLL and enabling conversion.
 *
 * @return  none
 */
void HSADC_Function_Start(void)
{
    UHSIF_Clock_Set(RCC_PLLMUL16);    // Configure system PLL clock, 400M system clock 26-05-09
    HSADC_Function_Init();
    HSADC_Cmd(ENABLE);
    HSADC_SoftwareStartConvCmd(ENABLE);
}

/*********************************************************************
 * @fn      HSADC_Function_Stop
 *
 * @brief   Stops HSADC acquisition, disables interrupts, and resets the HSADC peripheral.
 *
 * @return  none
 */
void HSADC_Function_Stop(void)
{
    logic_adc_info.usb30_endp3_up = USB_SUCESEE_FLAG;
    logic_adc_info.usb20_endp3_up = USB_SUCESEE_FLAG;
    logic_adc_info.adc_rec_total = 0;
    logic_adc_info.adc_flag = 0;
    HSADC_Cmd(DISABLE);
    NVIC_DisableIRQ(HSADC_IRQn);
    HSADC->STATR = 0x07;
    RCC_HB2PeriphResetCmd(RCC_HB2Periph_HSADC, ENABLE);
    Delay_Ms(10);
    RCC_HB2PeriphResetCmd(RCC_HB2Periph_HSADC, DISABLE);
}

/*********************************************************************
 * @fn      LOGIC_Para_Init
 *
 * @brief   Initializes logic analyzer parameters to default values.
 *
 * @return  none
 */
void LOGIC_Para_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_HB2PeriphClockCmd(RCC_HB2Periph_GPIOB,ENABLE);
    logic_adc_info.usb_status = USB_NO_CONNECT;
    logic_adc_info.usb30_endp1_down = USB_SUCESEE_FLAG;
    logic_adc_info.usb20_endp1_down = USB_SUCESEE_FLAG;
    logic_adc_info.logic_bit = 0;
    logic_adc_info.logic_sys = 0;
    logic_adc_info.uhsif_div = 0;
    logic_adc_info.logic_level = 0;
    logic_adc_info.adc_bit = 0;
    logic_adc_info.adc_div = 0;
    logic_adc_info.adc_channel = 0;
    logic_adc_info.adc_flag = 0;
    logic_adc_info.usb_ram_over_flag = 0;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;      //usb link && usb trans
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Very_High;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    logic_adc_info.usb_trans_count = 0;
    logic_adc_info.usb_trans_flag = 0;
    USB_RUN_ON( );
    USB_LINK_OFF( );
}

/*********************************************************************
 * @fn      LOGIC_ADC_CMD_Process
 *
 * @brief   Initializes Logic&adc collection.
 *
 * @return  none
 */
void LOGIC_ADC_CMD_Process(void)
{
    uint8_t len;
    if((logic_adc_info.usb20_endp1_down == 0x00) && (logic_adc_info.usb30_endp1_down == 0x00))
    {
        return;
    }
    logic_adc_info.usb20_endp1_down = logic_adc_info.usb30_endp1_down = 0x00;    // Clear flag
    switch(pLogic_Para->Logic_Cmd)
    {
        /* Logic commands */
    case CMD_SET_LOGIC_PARA: /* Set acquisition parameters */
        logic_adc_info.logic_bit = pLogic_Para->Logic_Buf[0];
        logic_adc_info.logic_sys = pLogic_Para->Logic_Buf[1];
        Set_Logic_Para_Fun(logic_adc_info.logic_bit, logic_adc_info.logic_sys);
        pLogicSend_Para->Logic_Cmd = CMD_SET_LOGIC_PARA | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 1;
        pLogicSend_Para->Logic_Status = 0x00;
        len = 3;
        break;
    case CMD_SET_LOGIC_LEVEL: /* Set acquisition level */
        logic_adc_info.logic_level = ((uint16_t)pLogic_Para->Logic_Buf[0] << 8) | pLogic_Para->Logic_Buf[1];
        DAC_OUT(logic_adc_info.logic_level);                                    // Set DAC output voltage, configure DAC first
        pLogicSend_Para->Logic_Cmd = CMD_SET_LOGIC_LEVEL | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 1;
        pLogicSend_Para->Logic_Status = 0x00;
        len = 3;
        break;
    case CMD_SET_START: /* Start acquisition */
        UHSIF_Set_Para(logic_adc_info.logic_bit, logic_adc_info.uhsif_div);     // Configure parallel acquisition parameters
        logic_adc_info.usb_ram_over_flag = 0;
        logic_adc_info.usb_trans_flag = ENABLE;
        logic_adc_info.usb_trans_count = 0;
        UHSIF_Start(ENABLE);                     // Start data acquisition
        len = 0;
        break;
    case CMD_SET_STOP: /* Stop acquisition */
        UHSIF_Start(DISABLE);                                                   // Stop data acquisition
        UHSIF_Para_Init();
        logic_adc_info.usb_trans_flag = DISABLE;
        logic_adc_info.usb_trans_count = 0;
        USB_LINK_ON();
        logic_adc_info.usb_ram_over_flag = 0;
        len = 0;
        break;
    case CMD_GET_LOGIC_PARA: /* Get acquisition parameters */
        pLogicSend_Para->Logic_Cmd = CMD_GET_LOGIC_PARA | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 3;
        pLogicSend_Para->Logic_Status = 0x00;
        pLogicSend_Para->Logic_Buf[0] = logic_adc_info.logic_bit;
        pLogicSend_Para->Logic_Buf[1] = logic_adc_info.logic_sys;
        len = 5;
        break;
    case CMD_GET_LOGIC_LEVEL: /* Get acquisition level */
        pLogicSend_Para->Logic_Cmd = CMD_GET_LOGIC_LEVEL | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 3;
        pLogicSend_Para->Logic_Status = 0x00;
        pLogicSend_Para->Logic_Buf[0] = (uint8_t)(logic_adc_info.logic_level >> 8);
        pLogicSend_Para->Logic_Buf[1] = (uint8_t)(logic_adc_info.logic_level);
        len = 5;
        break;

        /* ADC commands */
    case CMD_SET_ADC_PARA: /* Set ADC acquisition parameters */
        logic_adc_info.adc_bit = pLogic_Para->Logic_Buf[0];
        logic_adc_info.adc_div = pLogic_Para->Logic_Buf[1];
        pLogicSend_Para->Logic_Cmd = CMD_SET_ADC_PARA | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 1;
        pLogicSend_Para->Logic_Status = 0x00;
        len = 3;
        break;
    case CMD_SET_ADC_CHANNEL: /* Set ADC acquisition channel */
        logic_adc_info.adc_channel = pLogic_Para->Logic_Buf[0];
        pLogicSend_Para->Logic_Cmd = CMD_SET_ADC_CHANNEL | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 1;
        pLogicSend_Para->Logic_Status = 0x00;
        len = 3;
        break;
    case CMD_SET_ADC_START: /* Start ADC acquisition */
        logic_adc_info.usb_ram_over_flag = 0;
        logic_adc_info.usb_trans_flag = ENABLE;
        logic_adc_info.usb_trans_count = 0;
        HSADC_Function_Start();
        len = 0;
        break;
    case CMD_SET_ADC_STOP: /* Stop ADC acquisition */
        logic_adc_info.usb_ram_over_flag = 0;
        HSADC_Function_Stop();
        logic_adc_info.usb_trans_flag = DISABLE;
        logic_adc_info.usb_trans_count = 0;
        USB_LINK_ON();
        len = 0;
        break;
    case CMD_GET_ADC_PARA: /* Get ADC acquisition parameters */
        pLogicSend_Para->Logic_Cmd = CMD_GET_ADC_PARA | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 3;
        pLogicSend_Para->Logic_Status = 0x00;
        pLogicSend_Para->Logic_Buf[0] = logic_adc_info.adc_bit;
        pLogicSend_Para->Logic_Buf[1] = logic_adc_info.adc_div;
        len = 5;
        break;
    case CMD_GET_ADC_CHANNEL: /* Get ADC acquisition channel */
        pLogicSend_Para->Logic_Cmd = CMD_GET_ADC_CHANNEL | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 2;
        pLogicSend_Para->Logic_Status = 0x00;
        pLogicSend_Para->Logic_Buf[0] = logic_adc_info.adc_channel;
        len = 4;
        break;
    case CMD_GET_VERSION: /* Get version */
        pLogicSend_Para->Logic_Cmd = CMD_GET_VERSION | CMD_RETURN_PARA;
        pLogicSend_Para->Logic_Len = 3;
        pLogicSend_Para->Logic_Status = 0x00;
        pLogicSend_Para->Logic_Buf[0] = SOFTWARE_VERSION;                       /* Software version */
        pLogicSend_Para->Logic_Buf[1] = HARDWARE_VERSION;                       /* Hardware version */
        len = 4;
        break;
    case CMD_SET_IAP: /* Set IAP download */
        FLASH_Unlock_Fast();
        FLASH_ErasePage(CalAddr & (~(Flash_Erase_Page_Size - 1)));
        FLASH_ProgramWord(CalAddr, 0x5aa55aa5);                                 // Write download flag
        FLASH->CTLR |= ((uint32_t)0x00008000);                                  // LOCK FLASH
        FLASH->CTLR |= ((uint32_t)0x00000080);                                  // LOCK CTLR
        len = 0;
        break;
    default: /* Default: invalid command */
        pLogicSend_Para->Logic_Cmd = 0xFA;
        pLogicSend_Para->Logic_Len = 1;
        pLogicSend_Para->Logic_Status = 0x00;
        len = 2;
        break;
    }

    if(len)
    {    // Send status response
        if(logic_adc_info.usb_status == USB_U3_CONNECT)
        {
            USBSSD->EP1_TX.UEP_TX_DMA = (uint32_t)USBSS_EP1_Tx_Buf;             // USB3.0 send
            USBSSD->EP1_TX.UEP_TX_CHAIN_LEN = 32;
            USBSSD->EP1_TX.UEP_TX_CHAIN_EXP_NUMP = 1;
        }
        else if(logic_adc_info.usb_status == USB_U2_CONNECT)
        {
            USBHSD->UEP1_TX_DMA = (uint32_t)USBSS_EP1_Tx_Buf;
            USBHSD->UEP1_TX_LEN = 32;
            USBHSD->UEP1_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
        }
        len = 0;
    }
}

/*********************************************************************
 * @fn      LOGIC_ADC_CMD_Send
 *
 * @brief   send Logic&adc status.
 *
 * @return  none
 */
void LOGIC_ADC_CMD_Send(uint8_t cmd, uint8_t status)
{
    pLogicSend_Para->Logic_Cmd = cmd | CMD_RETURN_PARA;
    pLogicSend_Para->Logic_Len = 1;
    pLogicSend_Para->Logic_Status = status;
    if(logic_adc_info.usb_status == USB_U3_CONNECT)
    {
        USBSSD->EP1_TX.UEP_TX_DMA = (uint32_t)USBSS_EP1_Tx_Buf;                 // USB3.0 send
        USBSSD->EP1_TX.UEP_TX_CHAIN_LEN = 32;
        USBSSD->EP1_TX.UEP_TX_CHAIN_EXP_NUMP = 1;
    }
    else if(logic_adc_info.usb_status == USB_U2_CONNECT)
    {
        USBHSD->UEP1_TX_DMA = (uint32_t)USBSS_EP1_Tx_Buf;
        USBHSD->UEP1_TX_LEN = 32;
        USBHSD->UEP1_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
    }
}
/*********************************************************************
 * @fn      LOGIC_UHSIF_Main_Process
 *
 * @brief   trans Logic data.
 *
 * @return  none
 */
void LOGIC_UHSIF_Main_Process(void)
{
    uint16_t len, temp, temp1;
    if(logic_adc_info.usb_status == USB_U3_CONNECT)
    {    // USB3.0 connected
        if((logic_adc_info.usb30_endp2_up == USB_SUCESEE_FLAG) && logic_adc_info.usb_endp2uhsif_total)
        {                                                                                           // Buffer has data, USB can send
            logic_adc_info.usb30_endp2_up = USB_BUSY_FLAG;                                          // Set USB3.0 endpoint 2 busy
            if((logic_adc_info.usb_endp2_up_count & 0x01) == 0x00)
            {
                USBSSD->EP2_TX.UEP_TX_DMA = (uint32_t)logic_adc_info.pusb_endp2_th0_up;
            }
            else
            {
                USBSSD->EP2_TX.UEP_TX_DMA = (uint32_t)logic_adc_info.pusb_endp2_th1_up;
            }
            len = logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_endp2_up_count];           // Get valid data length from DRAM
            logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_endp2_up_count] = 0;             // Default clear data length
            temp = len % DEF_USB_EP2_SS_SIZE;
            temp1 = len / DEF_USB_EP2_SS_SIZE;
            if(temp)
            {
                temp1 += 1;
            }
            else
            {
                temp = DEF_USB_EP2_SS_SIZE;
            }
            USBSSD->EP2_TX.UEP_TX_CHAIN_LEN = temp;
            USBSSD->EP2_TX.UEP_TX_CHAIN_EXP_NUMP = temp1;
            if((logic_adc_info.usb_endp2_up_count & 0x01) == 0x00)
            {
                logic_adc_info.pusb_endp2_th0_up += len;                                            // Buffer pointer advance
            }
            else
            {
                logic_adc_info.pusb_endp2_th1_up += len;                                            // Buffer pointer advance
            }
            logic_adc_info.usb_endp2_up_count++;
            __asm("fence");
            __asm("fence");
            if(logic_adc_info.usb_endp2_up_count == (DEF_UHSIF_TXBUF_CNT * 2 - 1))
            {    // Pointer wrap to buffer head
                logic_adc_info.pusb_endp2_th0_up = USBSS_EP2_Tx_Th0_Buf;
            }
            else if(logic_adc_info.usb_endp2_up_count == DEF_UHSIF_TXBUF_CNT * 2)
            {    // Pointer wrap to buffer head
                logic_adc_info.pusb_endp2_th1_up = USBSS_EP2_Tx_Th1_Buf;
                logic_adc_info.usb_endp2_up_count = 0;
            }
            __asm("fence");
            NVIC_DisableIRQ(USBSS_IRQn);
            NVIC_DisableIRQ(UHSIF_IRQn);
            logic_adc_info.usb_endp2uhsif_total--;
            NVIC_EnableIRQ(UHSIF_IRQn);
            NVIC_EnableIRQ(USBSS_IRQn);
            __asm("fence");
        }
    }
    else if(logic_adc_info.usb_status == USB_U2_CONNECT)
    {
        if((logic_adc_info.usb20_endp2_up == USB_SUCESEE_FLAG) && logic_adc_info.usb_endp2uhsif_total)
        {    // Buffer has data, USB can send

            logic_adc_info.usb20_endp2_up = USB_BUSY_FLAG;
            if((logic_adc_info.usb_endp2_up_count & 0x01) == 0x00)
            {
                USBHSD->UEP2_TX_DMA = (uint32_t)logic_adc_info.pusb_endp2_th0_up;
            }
            else
            {
                USBHSD->UEP2_TX_DMA = (uint32_t)logic_adc_info.pusb_endp2_th1_up;
            }
            len = logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_endp2_up_count];           // Get valid data length from DRAM
            logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_endp2_up_count] = 0;             // Default clear data length
            USBHSD->UEP2_TX_LEN = len;
            USBHSD->UEP2_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
            if((logic_adc_info.usb_endp2_up_count & 0x01) == 0x00)
            {
                logic_adc_info.pusb_endp2_th0_up += len;                                            // Buffer pointer advance
            }
            else
            {
                logic_adc_info.pusb_endp2_th1_up += len;                                            // Buffer pointer advance
            }
            logic_adc_info.usb_endp2_up_count++;
            __asm("fence");
            if(logic_adc_info.usb_endp2_up_count == (DEF_UHSIF_TXBUF_CNT * 2 - 1))
            {    // Pointer wrap to buffer head
                logic_adc_info.pusb_endp2_th0_up = USBSS_EP2_Tx_Th0_Buf;
            }
            else if(logic_adc_info.usb_endp2_up_count == DEF_UHSIF_TXBUF_CNT * 2)
            {    // Pointer wrap to buffer head
                logic_adc_info.pusb_endp2_th1_up = USBSS_EP2_Tx_Th1_Buf;
                logic_adc_info.usb_endp2_up_count = 0;
            }
            __asm("fence");
            NVIC_DisableIRQ(USBHS_IRQn);
            NVIC_DisableIRQ(UHSIF_IRQn);
            logic_adc_info.usb_endp2uhsif_total--;
            NVIC_EnableIRQ(UHSIF_IRQn);
            NVIC_EnableIRQ(USBHS_IRQn);
            __asm("fence");
        }
    }
}

/*********************************************************************
 * @fn      HSADC_IRQHandler
 *
 * @brief   HSADC Interrupt Service Function.
 *
 * @return  none
 */
void HSADC_IRQHandler(void)
{
    if(HSADC_GetITStatus(HSADC_IT_DMAEnd))
    {
        if((HSADC->STATR & 0x10))
        {    // Buffer A ready to send; Buffer B receiving ADC
            HSADC->ADDR0 = (uint32_t)ADC_BufA;
        }
        else
        {
            HSADC->ADDR1 = (uint32_t)ADC_BufB;                                                      // Buffer B ready to send; Buffer A receiving ADC
        }
        logic_adc_info.adc_rec_total++;
        HSADC_ClearITPendingBit(HSADC_IT_DMAEnd);
    }
}

/*********************************************************************
 * @fn      LOGIC_ADC_Main_Process
 *
 * @brief   trans ADC data.
 *
 * @return  none
 */
void LOGIC_ADC_Main_Process(void)
{
    if(logic_adc_info.usb_status == USB_U3_CONNECT)
    {    // Connected as USB3.0
        if((logic_adc_info.usb30_endp3_up == USB_SUCESEE_FLAG) && logic_adc_info.adc_rec_total)
        {
            logic_adc_info.usb30_endp3_up = USB_BUSY_FLAG;                                          // Set USB3.0 endpoint 2 busy
            if((logic_adc_info.usb_endp3_up_count & 0x01) == 0)
            {    // Even: use buffer A
                USBSSD->EP3_TX.UEP_TX_DMA = (uint32_t)ADC_BufA;
            }
            else
            {    // Odd: use buffer B
                USBSSD->EP3_TX.UEP_TX_DMA = (uint32_t)ADC_BufB;
            }
            USBSSD->EP3_TX.UEP_TX_CHAIN_LEN = DEF_USB_EP2_SS_SIZE;
            USBSSD->EP3_TX.UEP_TX_CHAIN_EXP_NUMP = 16;                                              // ADC_BUF_LEN/DEF_USB_EP2_SS_SIZE
            logic_adc_info.usb_endp3_up_count++;
            __asm("fence");
            NVIC_DisableIRQ(USBSS_IRQn);
            NVIC_DisableIRQ(HSADC_IRQn);
            logic_adc_info.adc_rec_total--;
            NVIC_EnableIRQ(HSADC_IRQn);
            NVIC_EnableIRQ(USBSS_IRQn);
            __asm("fence");
        }
    }
    else if(logic_adc_info.usb_status == USB_U2_CONNECT)
    {    // Connected as USB2.0
        if((logic_adc_info.usb20_endp3_up == USB_SUCESEE_FLAG) && logic_adc_info.adc_rec_total)
        {    // Buffer has data, USB can send
            logic_adc_info.usb20_endp3_up = USB_BUSY_FLAG;
            if((logic_adc_info.usb_endp3_up_count & 0x01) == 0)
            {    // Even: use buffer A
                USBHSD->UEP3_TX_DMA = (uint32_t)ADC_BufA;
            }
            else
            {    // Odd: use buffer B
                USBHSD->UEP3_TX_DMA = (uint32_t)ADC_BufB;
            }
            USBHSD->UEP3_TX_LEN = ADC_BUF_LEN;
            USBHSD->UEP3_TX_CTRL = (USBHSD->UEP3_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;
            logic_adc_info.usb_endp3_up_count++;
            __asm("fence");
            NVIC_DisableIRQ(USBHS_IRQn);
            NVIC_DisableIRQ(HSADC_IRQn);
            logic_adc_info.adc_rec_total--;
            NVIC_EnableIRQ(HSADC_IRQn);
            NVIC_EnableIRQ(USBHS_IRQn);
            __asm("fence");
        }
    }
}

/*********************************************************************
 * @fn      LOGIC_ADC_RAMOVER_Process
 *
 * @brief   ram over process.
 *
 * @return  none
 */
void LOGIC_ADC_RAMOVER_Process(void)
{
    if(logic_adc_info.usb_endp2uhsif_total >= 8 * 2)
    {
        DBG_PRINT("logic_over\n");
        // if( logic_adc_info.usb_ram_over_flag == 0 )
        // {
        //     LOGIC_ADC_CMD_Send( CMD_LOGIC_OVER,LOGIC_RAM_OVER );
        //     logic_adc_info.usb_ram_over_flag = 1;
        // }
    }
    if(logic_adc_info.adc_rec_total >= 2)
    {
        DBG_PRINT("adc_over\n");
        // if( logic_adc_info.usb_ram_over_flag == 0 )
        // {
        //     LOGIC_ADC_CMD_Send( CMD_LOGIC_OVER,ADC_RAM_OVER );
        //     logic_adc_info.usb_ram_over_flag = 1;
        // }
    }
}

/*********************************************************************
 * @fn      Get_Flash_Size
 *
 * @brief   get flash size init 8K.
 *
 * @return  none
 */
void Get_Flash_Size(void)
{
    if(((*(volatile uint32_t*)FLASH_CFGR0_BASE) & (1 << 28)) != 0)
    {
        Flash_Erase_Page_Size = Size_8KB;
    }
    else
    {
        Flash_Erase_Page_Size = Size_4KB;
    }
}

/*********************************************************************
 * @fn      IAP_JUMP_Process
 *
 * @brief   reset mcu input iap.
 *
 * @return  none
 */
void IAP_JUMP_Process(void)
{
    if(*(volatile uint32_t*)CalAddr == CheckNum)
    {
        DBG_PRINT("reset\n");
        Delay_Ms(10);
        NVIC_SystemReset();
        while(1);
    }
}



/*********************************************************************
 * @fn      TIM1_INT_Init
 *
 * @brief   Initializes TIM1 output .
 *
 * @param   none.
 *
 * @return  none
 */
void TIM1_INT_Init( u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_HB2PeriphClockCmd(RCC_HB2Periph_TIM1, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 10;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

    TIM_ClearITPendingBit( TIM1, TIM_IT_Update );

	NVIC_SetPriority(TIM1_UP_IRQn,0);
	NVIC_EnableIRQ(TIM1_UP_IRQn);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    TIM_Cmd( TIM1, ENABLE );
}


/*********************************************************************
 * @fn      TIM1_UP_IRQHandler
 *
 * @brief   This function handles TIM1 UP exception.
 *
 *
 * @return  none
 */
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update)==SET)
    {
        if( logic_adc_info.usb_trans_flag ){
            logic_adc_info.usb_trans_count++;
            if( logic_adc_info.usb_trans_count &0x01 ){
                USB_LINK_OFF( );
            }
            else{
                USB_LINK_ON( );
            }
        }
    }
    TIM_ClearITPendingBit( TIM1, TIM_IT_Update );
}


/*********************************************************************
 * @fn      Led_Time_Init
 *
 * @brief   This function  TIM1 Init.
 *
 *
 * @return  none
 */
void Led_Time_Init( void )
{
    TIM1_INT_Init( 10000, 400 );
    TIM_Cmd( TIM1, ENABLE );
}