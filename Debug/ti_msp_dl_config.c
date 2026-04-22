/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gPWM_UpBackup;
DL_TimerG_backupConfig gPWM_UnderBackup;
DL_TimerA_backupConfig gTimer_GimbalBackup;
DL_UART_Main_backupConfig gUART_3Backup;
DL_SPI_backupConfig gSPI1Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_Up_init();
    SYSCFG_DL_PWM_Under_init();
    SYSCFG_DL_Buzzer_init();
    SYSCFG_DL_CAPTURE_Up_init();
    SYSCFG_DL_CAPTURE_Down_init();
    SYSCFG_DL_Timer_Gimbal_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_K230_init();
    SYSCFG_DL_UART_1_init();
    SYSCFG_DL_UART_3_init();
    SYSCFG_DL_SPI1_init();
    SYSCFG_DL_ADC12_0_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWM_UpBackup.backupRdy 	= false;
	gPWM_UnderBackup.backupRdy 	= false;

	gTimer_GimbalBackup.backupRdy 	= false;
	gUART_3Backup.backupRdy 	= false;
	gSPI1Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(PWM_Up_INST, &gPWM_UpBackup);
	retStatus &= DL_TimerG_saveConfiguration(PWM_Under_INST, &gPWM_UnderBackup);
	retStatus &= DL_TimerA_saveConfiguration(Timer_Gimbal_INST, &gTimer_GimbalBackup);
	retStatus &= DL_UART_Main_saveConfiguration(UART_3_INST, &gUART_3Backup);
	retStatus &= DL_SPI_saveConfiguration(SPI1_INST, &gSPI1Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(PWM_Up_INST, &gPWM_UpBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(PWM_Under_INST, &gPWM_UnderBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(Timer_Gimbal_INST, &gTimer_GimbalBackup, false);
	retStatus &= DL_UART_Main_restoreConfiguration(UART_3_INST, &gUART_3Backup);
	retStatus &= DL_SPI_restoreConfiguration(SPI1_INST, &gSPI1Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_Up_INST);
    DL_TimerG_reset(PWM_Under_INST);
    DL_TimerG_reset(Buzzer_INST);
    DL_TimerG_reset(CAPTURE_Up_INST);
    DL_TimerG_reset(CAPTURE_Down_INST);
    DL_TimerA_reset(Timer_Gimbal_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_K230_INST);
    DL_UART_Main_reset(UART_1_INST);
    DL_UART_Main_reset(UART_3_INST);
    DL_SPI_reset(SPI1_INST);
    DL_ADC12_reset(ADC12_0_INST);

    DL_MathACL_reset(MATHACL);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_Up_INST);
    DL_TimerG_enablePower(PWM_Under_INST);
    DL_TimerG_enablePower(Buzzer_INST);
    DL_TimerG_enablePower(CAPTURE_Up_INST);
    DL_TimerG_enablePower(CAPTURE_Down_INST);
    DL_TimerA_enablePower(Timer_Gimbal_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_K230_INST);
    DL_UART_Main_enablePower(UART_1_INST);
    DL_UART_Main_enablePower(UART_3_INST);
    DL_SPI_enablePower(SPI1_INST);
    DL_ADC12_enablePower(ADC12_0_INST);

    DL_MathACL_enablePower(MATHACL);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Up_C1_IOMUX,GPIO_PWM_Up_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Up_C1_PORT, GPIO_PWM_Up_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_Under_C1_IOMUX,GPIO_PWM_Under_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_Under_C1_PORT, GPIO_PWM_Under_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Buzzer_C0_IOMUX,GPIO_Buzzer_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Buzzer_C0_PORT, GPIO_Buzzer_C0_PIN);

    DL_GPIO_initPeripheralInputFunction(GPIO_CAPTURE_Up_C0_IOMUX,GPIO_CAPTURE_Up_C0_IOMUX_FUNC);
    DL_GPIO_initPeripheralInputFunction(GPIO_CAPTURE_Down_C0_IOMUX,GPIO_CAPTURE_Down_C0_IOMUX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_K230_IOMUX_TX, GPIO_UART_K230_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_K230_IOMUX_RX, GPIO_UART_K230_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_1_IOMUX_TX, GPIO_UART_1_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_1_IOMUX_RX, GPIO_UART_1_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_3_IOMUX_TX, GPIO_UART_3_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_3_IOMUX_RX, GPIO_UART_3_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI1_IOMUX_SCLK, GPIO_SPI1_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI1_IOMUX_PICO, GPIO_SPI1_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI1_IOMUX_POCI, GPIO_SPI1_IOMUX_POCI_FUNC);

    DL_GPIO_initDigitalOutput(DIR_UP_PIN_0_IOMUX);

    DL_GPIO_initDigitalOutput(EN_UP_PIN_1_IOMUX);

    DL_GPIO_initDigitalOutput(EN_DOWN_PIN_2_IOMUX);

    DL_GPIO_initDigitalOutput(DIR_DOWN_PIN_3_IOMUX);

    DL_GPIO_initDigitalOutput(LED_PIN_4_IOMUX);

    DL_GPIO_initDigitalOutput(LED_1_PIN_8_IOMUX);

    DL_GPIO_initDigitalOutput(LED_2_PIN_9_IOMUX);

    DL_GPIO_initDigitalOutput(LED_3_PIN_10_IOMUX);

    DL_GPIO_initDigitalOutput(BUTTON_1_PIN_11_IOMUX);

    DL_GPIO_initDigitalOutput(BUTTON_2_PIN_12_IOMUX);

    DL_GPIO_initDigitalOutput(BUTTON_3_PIN_13_IOMUX);

    DL_GPIO_initDigitalOutput(BUTTON_4_PIN_14_IOMUX);

    DL_GPIO_initDigitalOutput(BUTTON_PIN_15_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_CS_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_RES_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_DC_IOMUX);

    DL_GPIO_clearPins(GPIOA, DIR_UP_PIN_0_PIN |
		EN_DOWN_PIN_2_PIN |
		DIR_DOWN_PIN_3_PIN |
		BUTTON_1_PIN_11_PIN |
		BUTTON_3_PIN_13_PIN |
		BUTTON_PIN_15_PIN);
    DL_GPIO_setPins(GPIOA, LED_1_PIN_8_PIN);
    DL_GPIO_enableOutput(GPIOA, DIR_UP_PIN_0_PIN |
		EN_DOWN_PIN_2_PIN |
		DIR_DOWN_PIN_3_PIN |
		LED_1_PIN_8_PIN |
		BUTTON_1_PIN_11_PIN |
		BUTTON_3_PIN_13_PIN |
		BUTTON_PIN_15_PIN);
    DL_GPIO_clearPins(GPIOB, EN_UP_PIN_1_PIN |
		LED_PIN_4_PIN |
		BUTTON_2_PIN_12_PIN |
		BUTTON_4_PIN_14_PIN |
		OLED_CS_PIN |
		OLED_RES_PIN |
		OLED_DC_PIN);
    DL_GPIO_setPins(GPIOB, LED_2_PIN_9_PIN |
		LED_3_PIN_10_PIN);
    DL_GPIO_enableOutput(GPIOB, EN_UP_PIN_1_PIN |
		LED_PIN_4_PIN |
		LED_2_PIN_9_PIN |
		LED_3_PIN_10_PIN |
		BUTTON_2_PIN_12_PIN |
		BUTTON_4_PIN_14_PIN |
		OLED_CS_PIN |
		OLED_RES_PIN |
		OLED_DC_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 3,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_HFCLK,
	.qDiv                   = 3,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};

SYSCONFIG_WEAK bool SYSCFG_DL_SYSCTL_SYSPLL_init(void)
{
    bool fFCCRatioStatus = false;
    uint32_t fFCCSysoscCount;
    uint32_t fFCCPllCount;
    uint32_t fFCCRatio;
    uint32_t fccTimeOutCounter;

    DL_SYSCTL_setFCCPeriods( DL_SYSCTL_FCC_TRIG_CNT_01 );

    /* Measuring PLL. */
    DL_SYSCTL_configFCC(DL_SYSCTL_FCC_TRIG_TYPE_RISE_RISE,
                        DL_SYSCTL_FCC_TRIG_SOURCE_LFCLK,
                        DL_SYSCTL_FCC_CLOCK_SOURCE_SYSPLLCLK0);
    /* Get SYSPLL frequency using FCC */
    fccTimeOutCounter = 0;
    DL_SYSCTL_startFCC();
    while (DL_SYSCTL_isFCCDone() == 0) {
        delay_cycles(977);  /* 1x LFCLK cycle = 32MHz/32.768kHz = 977, 30.5us */
        fccTimeOutCounter++;
        if(fccTimeOutCounter > 65){
            /* Timeout set to approximately 2ms (user-customizable) */
            break;
        }
    }

    /* get measA= SYSPLLCLK0 freq wrt LFOSC*/
    fFCCPllCount = DL_SYSCTL_readFCC();

    /* Measuring SYSPLL Source */
    DL_SYSCTL_configFCC(DL_SYSCTL_FCC_TRIG_TYPE_RISE_RISE,
                        DL_SYSCTL_FCC_TRIG_SOURCE_LFCLK,
                        DL_SYSCTL_FCC_CLOCK_SOURCE_HFCLK);
    /* Get SYSPLL frequency using FCC */
    fccTimeOutCounter = 0;
    DL_SYSCTL_startFCC();
    while (DL_SYSCTL_isFCCDone() == 0) {
        delay_cycles(977);  /* 1x LFCLK cycle = 32MHz/32.768kHz = 977, 30.5us */
        fccTimeOutCounter++;
        if(fccTimeOutCounter > 65){
            /* Timeout set to approximately 2ms (user-customizable) */
            break;
        }
    }

    /* get measB= SYSOSC freq wrt LFOSC*/
    fFCCSysoscCount = DL_SYSCTL_readFCC();

    /* Get ratio of both measurements*/
    fFCCRatio = (fFCCPllCount * FLOAT_TO_INT_SCALE) / fFCCSysoscCount;
    /* Check ratio is within bounds*/
    if ((FCC_LOWER_BOUND <  fFCCRatio) && (fFCCRatio < FCC_UPPER_BOUND))
    {
        /* ratio is good for proceeding into application code. */
        fFCCRatioStatus = true;
    }

    return fFCCRatioStatus;
}
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ,10, true);
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);

    /*
     * [SYSPLL_ERR_01]
     * PLL Incorrect locking WA start.
     * Insert after every PLL enable.
     * This can lead an infinite loop if the condition persists
     * and can block entry to the application code.
     */

    while (SYSCFG_DL_SYSCTL_SYSPLL_init() == false)
    {
        /* Toggle SYSPLL enable to re-enable SYSPLL and re-check incorrect locking */
        DL_SYSCTL_disableSYSPLL();
        DL_SYSCTL_enableSYSPLL();

        /* Wait until SYSPLL startup is stabilized*/
        while ((DL_SYSCTL_getClockStatus() & SYSCTL_CLKSTATUS_SYSPLLGOOD_MASK) != DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD){}
    }
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);

}


/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   50000 Hz = 10000000 Hz / (8 * (199 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_UpClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 199U
};

static const DL_TimerG_PWMConfig gPWM_UpConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_Up_init(void) {

    DL_TimerG_setClockConfig(
        PWM_Up_INST, (DL_TimerG_ClockConfig *) &gPWM_UpClockConfig);

    DL_TimerG_initPWMMode(
        PWM_Up_INST, (DL_TimerG_PWMConfig *) &gPWM_UpConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerG_setCounterControl(PWM_Up_INST,DL_TIMER_CZC_CCCTL1_ZCOND,DL_TIMER_CAC_CCCTL1_ACOND,DL_TIMER_CLC_CCCTL1_LCOND);

    DL_TimerG_setCaptureCompareOutCtl(PWM_Up_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_Up_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_Up_INST, 500, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_Up_INST);


    
    DL_TimerG_setCCPDirection(PWM_Up_INST , DL_TIMER_CC1_OUTPUT );
    DL_TimerG_enableShadowFeatures(PWM_Up_INST);


}
/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   50000 Hz = 10000000 Hz / (8 * (199 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_UnderClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 199U
};

static const DL_TimerG_PWMConfig gPWM_UnderConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_Under_init(void) {

    DL_TimerG_setClockConfig(
        PWM_Under_INST, (DL_TimerG_ClockConfig *) &gPWM_UnderClockConfig);

    DL_TimerG_initPWMMode(
        PWM_Under_INST, (DL_TimerG_PWMConfig *) &gPWM_UnderConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerG_setCounterControl(PWM_Under_INST,DL_TIMER_CZC_CCCTL1_ZCOND,DL_TIMER_CAC_CCCTL1_ACOND,DL_TIMER_CLC_CCCTL1_LCOND);

    DL_TimerG_setCaptureCompareOutCtl(PWM_Under_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_Under_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_Under_INST, 500, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_Under_INST);


    
    DL_TimerG_setCCPDirection(PWM_Under_INST , DL_TIMER_CC1_OUTPUT );
    DL_TimerG_enableShadowFeatures(PWM_Under_INST);


}
/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gBuzzerClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gBuzzerConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 30000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_Buzzer_init(void) {

    DL_TimerG_setClockConfig(
        Buzzer_INST, (DL_TimerG_ClockConfig *) &gBuzzerClockConfig);

    DL_TimerG_initPWMMode(
        Buzzer_INST, (DL_TimerG_PWMConfig *) &gBuzzerConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerG_setCounterControl(Buzzer_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerG_setCaptureCompareOutCtl(Buzzer_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(Buzzer_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(Buzzer_INST, 15000, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(Buzzer_INST);


    
    DL_TimerG_setCCPDirection(Buzzer_INST , DL_TIMER_CC0_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 40000000 Hz / (1 * (1 + 1))
 */
static const DL_TimerG_ClockConfig gCAPTURE_UpClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 1U
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * CAPTURE_Up_INST_LOAD_VALUE = (3.2768ms * 20000000 Hz) - 1
 */
static const DL_TimerG_CaptureCombinedConfig gCAPTURE_UpCaptureConfig = {
    .captureMode    = DL_TIMER_CAPTURE_COMBINED_MODE_PULSE_WIDTH_AND_PERIOD,
    .period         = CAPTURE_Up_INST_LOAD_VALUE,
    .startTimer     = DL_TIMER_STOP,
    .inputChan      = DL_TIMER_INPUT_CHAN_0,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_CAPTURE_Up_init(void) {

    DL_TimerG_setClockConfig(CAPTURE_Up_INST,
        (DL_TimerG_ClockConfig *) &gCAPTURE_UpClockConfig);

    DL_TimerG_initCaptureCombinedMode(CAPTURE_Up_INST,
        (DL_TimerG_CaptureCombinedConfig *) &gCAPTURE_UpCaptureConfig);
    DL_Timer_setCaptureCompareInputFilter(CAPTURE_Up_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_0_INDEX);
    DL_Timer_enableCaptureCompareInputFilter(CAPTURE_Up_INST,
        DL_TIMER_CC_0_INDEX);
    DL_TimerG_enableInterrupt(CAPTURE_Up_INST , DL_TIMERG_INTERRUPT_CC1_DN_EVENT |
		DL_TIMERG_INTERRUPT_ZERO_EVENT);

    DL_TimerG_enableClock(CAPTURE_Up_INST);

}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (40000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 40000000 Hz / (1 * (1 + 1))
 */
static const DL_TimerG_ClockConfig gCAPTURE_DownClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 1U
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * CAPTURE_Down_INST_LOAD_VALUE = (3.2768ms * 20000000 Hz) - 1
 */
static const DL_TimerG_CaptureCombinedConfig gCAPTURE_DownCaptureConfig = {
    .captureMode    = DL_TIMER_CAPTURE_COMBINED_MODE_PULSE_WIDTH_AND_PERIOD,
    .period         = CAPTURE_Down_INST_LOAD_VALUE,
    .startTimer     = DL_TIMER_STOP,
    .inputChan      = DL_TIMER_INPUT_CHAN_0,
    .inputInvMode   = DL_TIMER_CC_INPUT_INV_NOINVERT,
};

SYSCONFIG_WEAK void SYSCFG_DL_CAPTURE_Down_init(void) {

    DL_TimerG_setClockConfig(CAPTURE_Down_INST,
        (DL_TimerG_ClockConfig *) &gCAPTURE_DownClockConfig);

    DL_TimerG_initCaptureCombinedMode(CAPTURE_Down_INST,
        (DL_TimerG_CaptureCombinedConfig *) &gCAPTURE_DownCaptureConfig);
    DL_Timer_setCaptureCompareInputFilter(CAPTURE_Down_INST,
        DL_TIMER_CC_INPUT_FILT_CPV_CONSEC_PER, DL_TIMER_CC_INPUT_FILT_FP_PER_8,
        DL_TIMER_CC_0_INDEX);
    DL_Timer_enableCaptureCompareInputFilter(CAPTURE_Down_INST,
        DL_TIMER_CC_0_INDEX);
    DL_TimerG_enableInterrupt(CAPTURE_Down_INST , DL_TIMERG_INTERRUPT_CC1_DN_EVENT |
		DL_TIMERG_INTERRUPT_ZERO_EVENT);

    DL_TimerG_enableClock(CAPTURE_Down_INST);

}


/*
 * Timer clock configuration to be sourced by BUSCLK /  (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   16000000 Hz = 80000000 Hz / (1 * (4 + 1))
 */
static const DL_TimerA_ClockConfig gTimer_GimbalClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 4U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * Timer_Gimbal_INST_LOAD_VALUE = (2ms * 16000000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTimer_GimbalTimerConfig = {
    .period     = Timer_Gimbal_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_Timer_Gimbal_init(void) {

    DL_TimerA_setClockConfig(Timer_Gimbal_INST,
        (DL_TimerA_ClockConfig *) &gTimer_GimbalClockConfig);

    DL_TimerA_initTimerMode(Timer_Gimbal_INST,
        (DL_TimerA_TimerConfig *) &gTimer_GimbalTimerConfig);
    DL_TimerA_enableInterrupt(Timer_Gimbal_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(Timer_Gimbal_INST);





}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_40_MHZ_115200_BAUD, UART_0_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_0_INST_INT_IRQN, 1);

    /* Configure digital glitch filter */
    DL_UART_setDigitalPulseWidth(UART_0_INST, 5);

    DL_UART_Main_enable(UART_0_INST);
}
static const DL_UART_Main_ClockConfig gUART_K230ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_K230Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_K230_init(void)
{
    DL_UART_Main_setClockConfig(UART_K230_INST, (DL_UART_Main_ClockConfig *) &gUART_K230ClockConfig);

    DL_UART_Main_init(UART_K230_INST, (DL_UART_Main_Config *) &gUART_K230Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART_K230_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_K230_INST, UART_K230_IBRD_40_MHZ_115200_BAUD, UART_K230_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_K230_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_K230_INST_INT_IRQN, 1);

    /* Configure digital glitch filter */
    DL_UART_setDigitalPulseWidth(UART_K230_INST, 5);

    DL_UART_Main_enable(UART_K230_INST);
}
static const DL_UART_Main_ClockConfig gUART_1ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_1Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_1_init(void)
{
    DL_UART_Main_setClockConfig(UART_1_INST, (DL_UART_Main_ClockConfig *) &gUART_1ClockConfig);

    DL_UART_Main_init(UART_1_INST, (DL_UART_Main_Config *) &gUART_1Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9599.81
     */
    DL_UART_Main_setOversampling(UART_1_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_1_INST, UART_1_IBRD_40_MHZ_9600_BAUD, UART_1_FBRD_40_MHZ_9600_BAUD);



    DL_UART_Main_enable(UART_1_INST);
}
static const DL_UART_Main_ClockConfig gUART_3ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_3Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_3_init(void)
{
    DL_UART_Main_setClockConfig(UART_3_INST, (DL_UART_Main_ClockConfig *) &gUART_3ClockConfig);

    DL_UART_Main_init(UART_3_INST, (DL_UART_Main_Config *) &gUART_3Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.1
     */
    DL_UART_Main_setOversampling(UART_3_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_3_INST, UART_3_IBRD_80_MHZ_9600_BAUD, UART_3_FBRD_80_MHZ_9600_BAUD);



    DL_UART_Main_enable(UART_3_INST);
}

static const DL_SPI_Config gSPI1_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI1_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI1_init(void) {
    DL_SPI_setClockConfig(SPI1_INST, (DL_SPI_ClockConfig *) &gSPI1_clockConfig);

    DL_SPI_init(SPI1_INST, (DL_SPI_Config *) &gSPI1_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     100000 = (80000000)/((1 + 399) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI1_INST, 399);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI1_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI1_INST);
}

/* ADC12_0 Initialization */
static const DL_ADC12_ClockConfig gADC12_0ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_SYSOSC,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC12_0_init(void)
{
    DL_ADC12_setClockConfig(ADC12_0_INST, (DL_ADC12_ClockConfig *) &gADC12_0ClockConfig);
    DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_0,
        DL_ADC12_INPUT_CHAN_0, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_enableConversions(ADC12_0_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /*
     * Initializes the SysTick period to 1.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    DL_SYSTICK_config(80000);
}

