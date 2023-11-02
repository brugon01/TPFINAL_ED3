/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */


#include "LPC17xx.h"
#include "lpc17xx_pwm.h"
#include "lpc17xx_pinsel.h"

void configPin();

int main(void) {

	configPin();

	PWM_TIMERCFG_Type PWMconfig;
	PWMconfig.PrescaleOption=PWM_TIMER_PRESCALE_TICKVAL;
	PWMconfig.PrescaleValue=1;

	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, &PWMconfig);

	PWM_MATCHCFG_Type match0;
	match0.IntOnMatch=DISABLE;
	match0.MatchChannel=0;
	match0.ResetOnMatch=ENABLE;
	match0.StopOnMatch=DISABLE;

	PWM_ConfigMatch(LPC_PWM1, &match0);

	PWM_MATCHCFG_Type match1;
	match1.IntOnMatch=DISABLE;
	match1.MatchChannel=1;
	match1.ResetOnMatch=DISABLE;
	match1.StopOnMatch=DISABLE;

	PWM_ConfigMatch(LPC_PWM1, &match1);

	PWM_MatchUpdate(LPC_PWM1, 0, 500000, PWM_MATCH_UPDATE_NEXT_RST); //VER update next rst

	PWM_MatchUpdate(LPC_PWM1, 1, 25000, PWM_MATCH_UPDATE_NEXT_RST);

	PWM_ChannelCmd(LPC_PWM1, 1, ENABLE);

	PWM_ResetCounter(LPC_PWM1);

	PWM_CounterCmd(LPC_PWM1, ENABLE);

	PWM_Cmd(LPC_PWM1, ENABLE);




    while(1) {

    }
    return 0 ;
}

void configPin()
{
	PINSEL_CFG_Type pinCfg;
	pinCfg.Funcnum = 2;                     //A
	pinCfg.OpenDrain = 0;
	pinCfg.Pinmode = 0;
	pinCfg.Portnum = 1;
	pinCfg.Pinnum = 18;
	PINSEL_ConfigPin(&pinCfg);
}

