/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32h417_logic.h
 * Author             : Q2H2
 * Version            : V1.0.0
 * Date               : 2026/05/18
 * Description        : Header file for ch32h417_logic.c
 ********************************************************************************/
#ifndef __CH32H417_LOGIC_H
#define __CH32H417_LOGIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch32h417.h"
#include "debug.h"

#define pLogic_Para         ((PLOGIC_PARA)USBSS_EP1_Rx_Buf)     /* Logic analyzer RX command buffer */
#define pLogicSend_Para     ((PSENDLOGIC_PARA)USBSS_EP1_Tx_Buf) /* Logic analyzer TX command buffer */

/* Logic analyzer command codes */
#define CMD_SET_LOGIC_PARA  0xA0                                                /* Set acquisition parameters */
#define CMD_SET_LOGIC_LEVEL 0xA1                                                /* Set acquisition trigger level */
#define CMD_SET_START       0xA2                                                /* Start acquisition */
#define CMD_SET_STOP        0xA3                                                /* Stop acquisition */
#define CMD_GET_LOGIC_PARA  0xA4                                                /* Get acquisition parameters */
#define CMD_GET_LOGIC_LEVEL 0xA5                                                /* Get acquisition trigger level */

/* ADC command codes */
#define CMD_SET_ADC_PARA    0xA6                                                /* Set ADC acquisition parameters */
#define CMD_SET_ADC_CHANNEL 0xA7                                                /* Set ADC acquisition channel */
#define CMD_SET_ADC_START   0xA8                                                /* Start ADC acquisition */
#define CMD_SET_ADC_STOP    0xA9                                                /* Stop ADC acquisition */
#define CMD_GET_ADC_PARA    0xAA                                                /* Get ADC acquisition parameters */
#define CMD_GET_ADC_CHANNEL 0xAB                                                /* Get ADC acquisition channel */
#define CMD_LOGIC_OVER      0xAD                                                /* Logic analyzer or ADC buffer overflow. status=1: logic overflow, status=2: ADC overflow */
#define CMD_GET_VERSION     0xAC                                                /* Get firmware version */
#define CMD_SET_IAP         0xAE                                                /* IAP upgrade command */

#define SOFTWARE_VERSION    0x02
#define HARDWARE_VERSION    0x01

#define LOGIC_RAM_OVER      0x01                                                /* Logic RAM overflow */
#define ADC_RAM_OVER        0x02                                                /* ADC RAM overflow */

#define CMD_RETURN_PARA     0x10                                                /* Command response */

#define ADC_CHANNEL0        0x00
#define ADC_CHANNEL1        0x01

#define ADC_GET_WIDTH8      0x08                                                /* ADC 8-bit sampling */
#define ADC_GET_WIDTH10     0x0a                                                /* ADC 10-bit sampling */

#define USB_NO_CONNECT      0x00                                                /* USB disconnected */
#define USB_U2_CONNECT      0x01                                                /* USB 2.0 connected */
#define USB_U3_CONNECT      0x02                                                /* USB 3.0 connected */

#define USB_SUCESEE_FLAG    0x00
#define USB_BUSY_FLAG       0x01

#define ADC_BUF_LEN         (16 * 1024)                                         /* ADC buffer size */

#define Size_256B           0x100
#define Size_4KB            0x1000
#define Size_8KB            0x2000
#define CalAddr             (0x08078000 - 4)                                    /* IAP flag address in flash */
#define CheckNum            (0x5aa55aa5)                                        /* IAP flag check value */


#define	USB_RUN_OFF()	{ GPIOB->BSHR = GPIO_Pin_0; }		//PB3 HIGH
#define	USB_RUN_ON()	{ GPIOB->BCR  = GPIO_Pin_0; }		//PB3 LOW

#define	USB_LINK_OFF()	{ GPIOB->BSHR = GPIO_Pin_1; }		//PB4 HIGH
#define	USB_LINK_ON()	{ GPIOB->BCR  = GPIO_Pin_1; }		//PB4 LOW


typedef __attribute__((aligned(1))) struct _LOGIC_param
{
    uint8_t Logic_Cmd;                                                          /* Command code */
    uint8_t Logic_Len;                                                          /* Payload length */
    uint8_t Logic_Buf[5];                                                       /* Payload data */
} LOGIC_PARA, *PLOGIC_PARA;

typedef __attribute__((aligned(1))) struct _SEND_LOGIC_param
{
    uint8_t Logic_Cmd;                                                          /* Command code */
    uint8_t Logic_Len;                                                          /* Payload length */
    uint8_t Logic_Status;                                                       /* Status */
    uint8_t Logic_Buf[5];                                                       /* Payload data */
} SENDLOGIC_PARA, *PSENDLOGIC_PARA;

typedef __attribute__((aligned(1))) struct _LOGIC_ADC_param
{
    /* Logic acquisition parameters */
    uint8_t logic_bit;                                                          /* Sample bit width */
    uint8_t logic_sys;                                                          /* Sampling frequency */
    uint8_t uhsif_div;                                                          /* Clock divider */
    uint16_t logic_level;                                                       /* Trigger level */
    /* ADC acquisition parameters */
    uint8_t adc_bit;                                                            /* ADC sample bit width: 0x08=8-bit, 0x0a=10-bit */
    uint8_t adc_div;                                                            /* ADC clock divider: 0=no division, 1=/2 ... 0x3f=/64 */
    uint8_t adc_channel;                                                        /* ADC channel: 0=ch0, 1=ch1 */
    uint8_t adc_flag;                                                           /* ADC buffer flag: 0=buf0, 1=buf1 */
    /* USB status - logic */
    uint8_t volatile usb_status;                                                /* USB connection: 0x01=USB3.0, 0x02=USB2.0 */
    uint8_t volatile usb30_endp1_down;                                          /* USB3.0 EP1 RX flag */
    uint8_t volatile usb20_endp1_down;                                          /* USB2.0 EP1 RX flag */
    uint8_t volatile usb_ram_over_flag;                                         /* USB RAM overflow flag */
    uint8_t* pusb_endp2_th0_up;                                                 /* USB TX buffer pointer */
    uint8_t* pusb_endp2_th1_up;                                                 /* USB TX buffer pointer */
    uint8_t volatile usb30_endp2_up;                                            /* USB3.0 EP2 TX flag (logic upload) */
    uint8_t volatile usb20_endp2_up;                                            /* USB2.0 EP2 TX flag (logic upload) */
    uint8_t volatile usb_endp2_up_count;                                        /* USB upload count */
    uint8_t volatile usb_endp2uhsif_total;                                      /* UHSIF RX + USB TX total count */
    uint8_t volatile usb_uhsif_Th0_count;                                       /* UHSIF thread 0 RX count */
    uint8_t volatile usb_uhsif_Th1_count;                                       /* UHSIF thread 1 RX count */
    uint16_t usb_uhsif_reclen_buf[255];                                         /* UHSIF received data length buffer */
    /* USB status - ADC */
    uint8_t volatile usb30_endp3_up;                                            /* USB3.0 EP3 TX flag (ADC upload) */
    uint8_t volatile usb20_endp3_up;                                            /* USB2.0 EP3 TX flag (ADC upload) */
    uint8_t volatile adc_rec_total;                                             /* ADC total sample count */
    uint8_t volatile usb_endp3_up_count;                                        /* USB upload count */

    /* LED status - LED*/
    uint16_t volatile usb_trans_count;                                            /* USB3.0 EP3 TX flag (ADC upload) */
    uint8_t volatile usb_trans_flag;
} LOGIC_ADC_PARA, *PLOGIC_ADC_PARA;

extern LOGIC_ADC_PARA logic_adc_info;                                           /* Logic and ADC parameter buffer */
extern void LOGIC_UHSIF_Main_Process(void);                                     /* Logic acquisition main process */
extern void LOGIC_ADC_Main_Process(void);                                       /* ADC acquisition main process */
extern void LOGIC_Para_Init(void);                                              /* Parameter initialization */
extern void LOGIC_ADC_CMD_Process(void);                                        /* Logic & ADC command processing */
extern void Dac_Init(void);                                                     /* DAC output initialization */
extern void LOGIC_ADC_CMD_Send(uint8_t cmd, uint8_t status);                    /* Report command status */
extern void LOGIC_ADC_RAMOVER_Process(void);                                    /* RAM overflow handler */
extern void Get_Flash_Size(void);                                               /* Get flash size for IAP upgrade */
extern void IAP_JUMP_Process(void);                                             /* Jump to IAP bootloader */
extern void HSADC_Function_Start(void);
extern void HSADC_Function_Stop(void);
extern void Led_Time_Init( void );

#ifdef __cplusplus
}
#endif
#endif
