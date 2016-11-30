#include <buzzer.h>
#include <pwm.h>
#include <delay.h>
#include <lcd.h>
#include "main_func.h"
#include <stdio.h>

int buzzer_sound(void)
{
	pwm_init();
	pwm_start(PWM_CH1);

	int frequency1[]={659,554,659,554,550,494,554,587,494,659,554,440};
	uint16_t i;
	int j;
	
	for (j = 0; j < 5; j++)
		for (i = 0; i <= 11; i++) {
			pwm_set_period(PWM_CH1, 1/frequency1[i]);
			pwm_set_frequency(PWM_CH1, frequency1[i]);
			pwm_set_duty(PWM_CH1, 60);
			mdelay(100);
		}
	//pwm_stop(PWM_CH1);
	lcd_init();
	printf("in\n");
}
