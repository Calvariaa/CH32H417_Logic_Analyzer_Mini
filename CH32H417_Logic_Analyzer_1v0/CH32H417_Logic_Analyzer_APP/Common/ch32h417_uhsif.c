/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32h417_uhsif.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2026/05/18
 * Description        : This file provides all the UHSIF firmware functions.
 *********************************************************************************
 * Copyright (c) 2026 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "ch32H417_uhsif.h"
#include "ch32h417_logic.h"
#include "ch32h417_usbss_device.h"

/*******************************************************************************
 * @fn      UHSIF_Init
 *
 * @brief   UHSIF initialization.
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Init(void)
{
    UHSIF_Para_Init();

    /* For the UHSIF pin initialization, the host needs to configure the frequency division coefficient */
    UHSIF_GPIO_Init(DEF_UHSIF_SLAVE_FPGA_MODE, DEF_UHSIF_PINREMAP2, DEF_UHSIF_CLKREMAP1, 2, DEF_UHSIF_DATA_BIT16);    // Divide 400M HSI by 2 to get 200M

    /* Initialization of UHSIF-related registers */
    UHSIF_Cfg();

    /* UHSIF line and buff initialization */
    UHSIF_Line_Cfg(DEF_LINE0, DEF_LINE_DIR_IN, DEF_BUFF_COUNT_8, USBSS_EP2_Tx_Th0_Buf, 0);
    UHSIF_Line_Cfg(DEF_LINE1, DEF_LINE_DIR_IN, DEF_BUFF_COUNT_8, USBSS_EP2_Tx_Th1_Buf, 0);

    /* UHSIF enabled */
    UHSIF_Start(ENABLE);
}

/*******************************************************************************
 * @fn      UHSIF_Set_Para
 *
 * @brief   Configure UHSIF parameters with specified data bit width and clock divider.
 *
 * @param   logic_bit: Data bit width (8 or 0x10 for 16-bit).
 * @param   logic_div: Clock frequency division coefficient.
 *
 * @return  None
 */
void UHSIF_Set_Para(uint8_t logic_bit, uint8_t logic_div)
{
    uint8_t logic_set = 0;
    if(logic_bit == 8)
    {
        logic_set = DEF_UHSIF_DATA_BIT8;
    }
    else if(logic_bit == 0x10)
    {
        logic_set = DEF_UHSIF_DATA_BIT16;
    }
    UHSIF_Start(DISABLE);    // First disable parallel port acquisition
    UHSIF_Para_Init();

    /* For the UHSIF pin initialization, the host needs to configure the frequency division coefficient */
    UHSIF_GPIO_Init(DEF_UHSIF_SLAVE_FPGA_MODE, DEF_UHSIF_PINREMAP2, DEF_UHSIF_CLKREMAP1, logic_div, logic_set);    // Divide 400M HSI by 2 to get 200M

    /* Initialization of UHSIF-related registers */
    UHSIF_Cfg();

    /* UHSIF line and buff initialization */
    UHSIF_Line_Cfg(DEF_LINE0, DEF_LINE_DIR_IN, DEF_BUFF_COUNT_8, USBSS_EP2_Tx_Th0_Buf, 0);
    UHSIF_Line_Cfg(DEF_LINE1, DEF_LINE_DIR_IN, DEF_BUFF_COUNT_8, USBSS_EP2_Tx_Th1_Buf, 0);
}

/*******************************************************************************
 * @fn      UHSIF_Para_Init
 *
 * @brief   UHSIF-Related initialization.
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Para_Init(void)
{
    logic_adc_info.usb30_endp2_up = 0;                           /* USB 3.0 upload flag */
    logic_adc_info.usb20_endp2_up = 0;                           /* USB 2.0 upload flag */
    logic_adc_info.usb_endp2_up_count = 0;                       /* USB upload count */
    logic_adc_info.pusb_endp2_th0_up = &USBSS_EP2_Tx_Th0_Buf[0]; /* USB upload buffer pointer */
    logic_adc_info.pusb_endp2_th1_up = &USBSS_EP2_Tx_Th1_Buf[0]; /* USB upload buffer pointer */
    logic_adc_info.usb_endp2uhsif_total = 0;                     /* UHSIF receive and USB transmit total count */
    logic_adc_info.usb_uhsif_Th0_count = 0;                      /* UHSIF line 0 receive buffer count */
    logic_adc_info.usb_uhsif_Th1_count = 0;                      /* UHSIF line 1 receive buffer count */
    memset(logic_adc_info.usb_uhsif_reclen_buf, 0x00, 255);      /* UHSIF received data length buffer */
}

/*******************************************************************************
 * @fn      UHSIF_Line0_IN_Callback
 *
 * @brief   The interrupt callback function for line 0 configuration input
 *
 * @param   rcv_count: The length of the data received by line 0
 *
 * @return  None
 */
void UHSIF_Line0_IN_Callback(uint32_t rcv_count)
{
    if(rcv_count)
    {
        logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_uhsif_Th0_count * 2] = rcv_count;
        UHSIF_Trans_Cfg(DEF_LINE0, logic_adc_info.usb_uhsif_Th0_count, 0);
        logic_adc_info.usb_uhsif_Th0_count++;
        if(logic_adc_info.usb_uhsif_Th0_count >= DEF_UHSIF_RXBUF_CNT)
        {
            logic_adc_info.usb_uhsif_Th0_count = 0;
        }
        logic_adc_info.usb_endp2uhsif_total++; /* Total transfer count increment */
    }
}

/*******************************************************************************
 * @fn      UHSIF_Line1_IN_Callback
 *
 * @brief   The interrupt callback function for line 1 configuration input
 *
 * @param   rcv_count: The length of the data received by line 1
 *
 * @return  None
 */
void UHSIF_Line1_IN_Callback(uint32_t rcv_count)
{
    if(rcv_count)
    {
        logic_adc_info.usb_uhsif_reclen_buf[logic_adc_info.usb_uhsif_Th1_count * 2 + 1] = rcv_count;
        /* Allow to continue receiving next packet */
        UHSIF_Trans_Cfg(DEF_LINE1, logic_adc_info.usb_uhsif_Th1_count, 0);
        logic_adc_info.usb_uhsif_Th1_count++;
        if(logic_adc_info.usb_uhsif_Th1_count >= DEF_UHSIF_RXBUF_CNT)
        {
            logic_adc_info.usb_uhsif_Th1_count = 0;
        }
        logic_adc_info.usb_endp2uhsif_total++; /* Total transfer count increment */
    }
}

/*******************************************************************************
 * @fn      UHSIF_Line2_IN_Callback
 *
 * @brief   The interrupt callback function for line 2 configuration input
 *
 * @param   rcv_count: The length of the data received by line 2
 *
 * @return  None
 */
void UHSIF_Line2_IN_Callback(uint32_t rcv_count)
{
}

/*******************************************************************************
 * @fn      UHSIF_Line3_IN_Callback
 *
 * @brief   The interrupt callback function for line 3 configuration input
 *
 * @param   rcv_count: The length of the data received by line 3
 *
 * @return  None
 */
void UHSIF_Line3_IN_Callback(uint32_t rcv_count)
{
}

/*******************************************************************************
 * @fn      UHSIF_Line0_OUT_Callback
 *
 * @brief   The interrupt callback function for line 0 configuration output
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Line0_OUT_Callback(void)
{
}

/*******************************************************************************
 * @fn      UHSIF_Line1_OUT_Callback
 *
 * @brief   The interrupt callback function for line 1 configuration output
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Line1_OUT_Callback(void)
{
}

/*******************************************************************************
 * @fn      UHSIF_Line2_OUT_Callback
 *
 * @brief   The interrupt callback function for line 2 configuration output
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Line2_OUT_Callback(void)
{
}

/*******************************************************************************
 * @fn      UHSIF_Line3_OUT_Callback
 *
 * @brief   The interrupt callback function for line 3 configuration output
 *
 * @param   None
 *
 * @return  None
 */
void UHSIF_Line3_OUT_Callback(void)
{
}
