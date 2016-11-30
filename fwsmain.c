#include <gpio.h>
#include <adc.h>
#include <serial.h>
#include <pwm.h>
#include <delay.h>
#include <timer.h>
#include <fws.h>

static timer_t timer1;

int fws_init(void)
{
	gpio_init();
	timer_init();
	delay_init();
	serial_init();
	adc_init();
	motor_init();
	motor_start();
	timer_setup(&timer1, 1000);
	timer_setcb(&timer1, timer_call);
	event_poll();
	return 0;
}
