/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000
/* Defines for SYSPLL_ERR_01 Workaround */
/* Represent 1.000 as 1000 */
#define FLOAT_TO_INT_SCALE                                               (1000U)
#define FCC_EXPECTED_RATIO                                                  2000
#define FCC_UPPER_BOUND                       (FCC_EXPECTED_RATIO * (1 + 0.003))
#define FCC_LOWER_BOUND                       (FCC_EXPECTED_RATIO * (1 - 0.003))

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);


/* Defines for PWM_Up */
#define PWM_Up_INST                                                        TIMG7
#define PWM_Up_INST_IRQHandler                                  TIMG7_IRQHandler
#define PWM_Up_INST_INT_IRQN                                    (TIMG7_INT_IRQn)
#define PWM_Up_INST_CLK_FREQ                                               50000
/* GPIO defines for channel 1 */
#define GPIO_PWM_Up_C1_PORT                                                GPIOA
#define GPIO_PWM_Up_C1_PIN                                        DL_GPIO_PIN_27
#define GPIO_PWM_Up_C1_IOMUX                                     (IOMUX_PINCM60)
#define GPIO_PWM_Up_C1_IOMUX_FUNC                    IOMUX_PINCM60_PF_TIMG7_CCP1
#define GPIO_PWM_Up_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_Under */
#define PWM_Under_INST                                                     TIMG6
#define PWM_Under_INST_IRQHandler                               TIMG6_IRQHandler
#define PWM_Under_INST_INT_IRQN                                 (TIMG6_INT_IRQn)
#define PWM_Under_INST_CLK_FREQ                                            50000
/* GPIO defines for channel 1 */
#define GPIO_PWM_Under_C1_PORT                                             GPIOA
#define GPIO_PWM_Under_C1_PIN                                     DL_GPIO_PIN_22
#define GPIO_PWM_Under_C1_IOMUX                                  (IOMUX_PINCM47)
#define GPIO_PWM_Under_C1_IOMUX_FUNC                 IOMUX_PINCM47_PF_TIMG6_CCP1
#define GPIO_PWM_Under_C1_IDX                                DL_TIMER_CC_1_INDEX

/* Defines for Buzzer */
#define Buzzer_INST                                                       TIMG12
#define Buzzer_INST_IRQHandler                                 TIMG12_IRQHandler
#define Buzzer_INST_INT_IRQN                                   (TIMG12_INT_IRQn)
#define Buzzer_INST_CLK_FREQ                                            80000000
/* GPIO defines for channel 0 */
#define GPIO_Buzzer_C0_PORT                                                GPIOB
#define GPIO_Buzzer_C0_PIN                                        DL_GPIO_PIN_13
#define GPIO_Buzzer_C0_IOMUX                                     (IOMUX_PINCM30)
#define GPIO_Buzzer_C0_IOMUX_FUNC                   IOMUX_PINCM30_PF_TIMG12_CCP0
#define GPIO_Buzzer_C0_IDX                                   DL_TIMER_CC_0_INDEX



/* Defines for CAPTURE_Up */
#define CAPTURE_Up_INST                                                  (TIMG8)
#define CAPTURE_Up_INST_IRQHandler                              TIMG8_IRQHandler
#define CAPTURE_Up_INST_INT_IRQN                                (TIMG8_INT_IRQn)
#define CAPTURE_Up_INST_LOAD_VALUE                                      (65535U)
/* GPIO defines for channel 0 */
#define GPIO_CAPTURE_Up_C0_PORT                                            GPIOA
#define GPIO_CAPTURE_Up_C0_PIN                                     DL_GPIO_PIN_1
#define GPIO_CAPTURE_Up_C0_IOMUX                                  (IOMUX_PINCM2)
#define GPIO_CAPTURE_Up_C0_IOMUX_FUNC                 IOMUX_PINCM2_PF_TIMG8_CCP0

/* Defines for CAPTURE_Down */
#define CAPTURE_Down_INST                                                (TIMG0)
#define CAPTURE_Down_INST_IRQHandler                            TIMG0_IRQHandler
#define CAPTURE_Down_INST_INT_IRQN                              (TIMG0_INT_IRQn)
#define CAPTURE_Down_INST_LOAD_VALUE                                    (65535U)
/* GPIO defines for channel 0 */
#define GPIO_CAPTURE_Down_C0_PORT                                          GPIOA
#define GPIO_CAPTURE_Down_C0_PIN                                  DL_GPIO_PIN_12
#define GPIO_CAPTURE_Down_C0_IOMUX                               (IOMUX_PINCM34)
#define GPIO_CAPTURE_Down_C0_IOMUX_FUNC              IOMUX_PINCM34_PF_TIMG0_CCP0





/* Defines for Timer_Gimbal */
#define Timer_Gimbal_INST                                                (TIMA0)
#define Timer_Gimbal_INST_IRQHandler                            TIMA0_IRQHandler
#define Timer_Gimbal_INST_INT_IRQN                              (TIMA0_INT_IRQn)
#define Timer_Gimbal_INST_LOAD_VALUE                                    (31999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)
/* Defines for UART_K230 */
#define UART_K230_INST                                                     UART2
#define UART_K230_INST_FREQUENCY                                        40000000
#define UART_K230_INST_IRQHandler                               UART2_IRQHandler
#define UART_K230_INST_INT_IRQN                                   UART2_INT_IRQn
#define GPIO_UART_K230_RX_PORT                                             GPIOB
#define GPIO_UART_K230_TX_PORT                                             GPIOB
#define GPIO_UART_K230_RX_PIN                                     DL_GPIO_PIN_16
#define GPIO_UART_K230_TX_PIN                                     DL_GPIO_PIN_15
#define GPIO_UART_K230_IOMUX_RX                                  (IOMUX_PINCM33)
#define GPIO_UART_K230_IOMUX_TX                                  (IOMUX_PINCM32)
#define GPIO_UART_K230_IOMUX_RX_FUNC                   IOMUX_PINCM33_PF_UART2_RX
#define GPIO_UART_K230_IOMUX_TX_FUNC                   IOMUX_PINCM32_PF_UART2_TX
#define UART_K230_BAUD_RATE                                             (115200)
#define UART_K230_IBRD_40_MHZ_115200_BAUD                                   (21)
#define UART_K230_FBRD_40_MHZ_115200_BAUD                                   (45)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                           40000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOB
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_4
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM17)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM17_PF_UART1_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_1_FBRD_40_MHZ_9600_BAUD                                        (27)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART3
#define UART_3_INST_FREQUENCY                                           80000000
#define UART_3_INST_IRQHandler                                  UART3_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOA
#define GPIO_UART_3_TX_PORT                                                GPIOA
#define GPIO_UART_3_RX_PIN                                        DL_GPIO_PIN_25
#define GPIO_UART_3_TX_PIN                                        DL_GPIO_PIN_26
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM55)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM59)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM55_PF_UART3_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM59_PF_UART3_TX
#define UART_3_BAUD_RATE                                                  (9600)
#define UART_3_IBRD_80_MHZ_9600_BAUD                                       (520)
#define UART_3_FBRD_80_MHZ_9600_BAUD                                        (53)




/* Defines for SPI1 */
#define SPI1_INST                                                          SPI1
#define SPI1_INST_IRQHandler                                    SPI1_IRQHandler
#define SPI1_INST_INT_IRQN                                        SPI1_INT_IRQn
#define GPIO_SPI1_PICO_PORT                                               GPIOB
#define GPIO_SPI1_PICO_PIN                                        DL_GPIO_PIN_8
#define GPIO_SPI1_IOMUX_PICO                                    (IOMUX_PINCM25)
#define GPIO_SPI1_IOMUX_PICO_FUNC                    IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI1_POCI_PORT                                               GPIOB
#define GPIO_SPI1_POCI_PIN                                        DL_GPIO_PIN_7
#define GPIO_SPI1_IOMUX_POCI                                    (IOMUX_PINCM24)
#define GPIO_SPI1_IOMUX_POCI_FUNC                    IOMUX_PINCM24_PF_SPI1_POCI
/* GPIO configuration for SPI1 */
#define GPIO_SPI1_SCLK_PORT                                               GPIOB
#define GPIO_SPI1_SCLK_PIN                                        DL_GPIO_PIN_9
#define GPIO_SPI1_IOMUX_SCLK                                    (IOMUX_PINCM26)
#define GPIO_SPI1_IOMUX_SCLK_FUNC                    IOMUX_PINCM26_PF_SPI1_SCLK



/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC1
#define ADC12_0_INST_IRQHandler                                  ADC1_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC1_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define GPIO_ADC12_0_C0_PORT                                               GPIOA
#define GPIO_ADC12_0_C0_PIN                                       DL_GPIO_PIN_15
#define GPIO_ADC12_0_IOMUX_C0                                    (IOMUX_PINCM37)
#define GPIO_ADC12_0_IOMUX_C0_FUNC                (IOMUX_PINCM37_PF_UNCONNECTED)



/* Port definition for Pin Group DIR_UP */
#define DIR_UP_PORT                                                      (GPIOA)

/* Defines for PIN_0: GPIOA.14 with pinCMx 36 on package pin 7 */
#define DIR_UP_PIN_0_PIN                                        (DL_GPIO_PIN_14)
#define DIR_UP_PIN_0_IOMUX                                       (IOMUX_PINCM36)
/* Port definition for Pin Group EN_UP */
#define EN_UP_PORT                                                       (GPIOA)

/* Defines for PIN_1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define EN_UP_PIN_1_PIN                                         (DL_GPIO_PIN_17)
#define EN_UP_PIN_1_IOMUX                                        (IOMUX_PINCM39)
/* Port definition for Pin Group EN_DOWN */
#define EN_DOWN_PORT                                                     (GPIOB)

/* Defines for PIN_2: GPIOB.24 with pinCMx 52 on package pin 23 */
#define EN_DOWN_PIN_2_PIN                                       (DL_GPIO_PIN_24)
#define EN_DOWN_PIN_2_IOMUX                                      (IOMUX_PINCM52)
/* Port definition for Pin Group DIR_DOWN */
#define DIR_DOWN_PORT                                                    (GPIOA)

/* Defines for PIN_3: GPIOA.24 with pinCMx 54 on package pin 25 */
#define DIR_DOWN_PIN_3_PIN                                      (DL_GPIO_PIN_24)
#define DIR_DOWN_PIN_3_IOMUX                                     (IOMUX_PINCM54)
/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_4: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_4_PIN                                           (DL_GPIO_PIN_22)
#define LED_PIN_4_IOMUX                                          (IOMUX_PINCM50)
/* Port definition for Pin Group LED_1 */
#define LED_1_PORT                                                       (GPIOA)

/* Defines for PIN_8: GPIOA.13 with pinCMx 35 on package pin 6 */
#define LED_1_PIN_8_PIN                                         (DL_GPIO_PIN_13)
#define LED_1_PIN_8_IOMUX                                        (IOMUX_PINCM35)
/* Port definition for Pin Group LED_2 */
#define LED_2_PORT                                                       (GPIOB)

/* Defines for PIN_9: GPIOB.3 with pinCMx 16 on package pin 51 */
#define LED_2_PIN_9_PIN                                          (DL_GPIO_PIN_3)
#define LED_2_PIN_9_IOMUX                                        (IOMUX_PINCM16)
/* Port definition for Pin Group LED_3 */
#define LED_3_PORT                                                       (GPIOB)

/* Defines for PIN_10: GPIOB.23 with pinCMx 51 on package pin 22 */
#define LED_3_PIN_10_PIN                                        (DL_GPIO_PIN_23)
#define LED_3_PIN_10_IOMUX                                       (IOMUX_PINCM51)
/* Port definition for Pin Group BUTTON_1 */
#define BUTTON_1_PORT                                                    (GPIOA)

/* Defines for PIN_11: GPIOA.30 with pinCMx 5 on package pin 37 */
#define BUTTON_1_PIN_11_PIN                                     (DL_GPIO_PIN_30)
#define BUTTON_1_PIN_11_IOMUX                                     (IOMUX_PINCM5)
/* Port definition for Pin Group BUTTON_2 */
#define BUTTON_2_PORT                                                    (GPIOB)

/* Defines for PIN_12: GPIOB.0 with pinCMx 12 on package pin 47 */
#define BUTTON_2_PIN_12_PIN                                      (DL_GPIO_PIN_0)
#define BUTTON_2_PIN_12_IOMUX                                    (IOMUX_PINCM12)
/* Port definition for Pin Group BUTTON_3 */
#define BUTTON_3_PORT                                                    (GPIOA)

/* Defines for PIN_13: GPIOA.7 with pinCMx 14 on package pin 49 */
#define BUTTON_3_PIN_13_PIN                                      (DL_GPIO_PIN_7)
#define BUTTON_3_PIN_13_IOMUX                                    (IOMUX_PINCM14)
/* Port definition for Pin Group BUTTON_4 */
#define BUTTON_4_PORT                                                    (GPIOB)

/* Defines for PIN_14: GPIOB.19 with pinCMx 45 on package pin 16 */
#define BUTTON_4_PIN_14_PIN                                     (DL_GPIO_PIN_19)
#define BUTTON_4_PIN_14_IOMUX                                    (IOMUX_PINCM45)
/* Port definition for Pin Group BUTTON */
#define BUTTON_PORT                                                      (GPIOA)

/* Defines for PIN_15: GPIOA.21 with pinCMx 46 on package pin 17 */
#define BUTTON_PIN_15_PIN                                       (DL_GPIO_PIN_21)
#define BUTTON_PIN_15_IOMUX                                      (IOMUX_PINCM46)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOB)

/* Defines for CS: GPIOB.14 with pinCMx 31 on package pin 2 */
#define OLED_CS_PIN                                             (DL_GPIO_PIN_14)
#define OLED_CS_IOMUX                                            (IOMUX_PINCM31)
/* Defines for RES: GPIOB.10 with pinCMx 27 on package pin 62 */
#define OLED_RES_PIN                                            (DL_GPIO_PIN_10)
#define OLED_RES_IOMUX                                           (IOMUX_PINCM27)
/* Defines for DC: GPIOB.11 with pinCMx 28 on package pin 63 */
#define OLED_DC_PIN                                             (DL_GPIO_PIN_11)
#define OLED_DC_IOMUX                                            (IOMUX_PINCM28)






/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);
void SYSCFG_DL_PWM_Up_init(void);
void SYSCFG_DL_PWM_Under_init(void);
void SYSCFG_DL_Buzzer_init(void);
void SYSCFG_DL_CAPTURE_Up_init(void);
void SYSCFG_DL_CAPTURE_Down_init(void);
void SYSCFG_DL_Timer_Gimbal_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_K230_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_3_init(void);
void SYSCFG_DL_SPI1_init(void);
void SYSCFG_DL_ADC12_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
