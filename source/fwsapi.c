#include "fws.h"
#include "dc_motor.c"

volatile unsigned int *gpio2_dir = (unsigned int *)0x50023ffc;
volatile unsigned int *gpio2_data = (unsigned int *)0x50028000;
volatile unsigned int *gpio3_dir = (unsigned int *)0x50038000;
volatile unsigned int *gpio3_data = (unsigned int *)0x50033ffc;
timer_t timer1;

void timer_call()
{
	sense_smoke(2, 4);
	timer_setup(&timer1, 1000);
}
void sense_smoke(int min_threshold, int max_threshold)
{
	int sensor_value;
	
	adc_enable(0);
	sensor_value = adc_read8(0);
	if (sensor_value > max_threshold || sensor_value < min_threshold) {
		glow_led();
		buzzer_on();
		send_sms();
		water_sprinkle();
	}
	else {
		led_off();
		buzzer_off();
		turnoff_motor();
	}
}
void glow_led(void)
{
	*gpio3_dir = 1;
	*gpio3_data = 1;
}
void led_off(void)
{
	*gpio3_dir = 1;
	*gpio3_data = 0;
}
void buzzer_on(void)
{
	*gpio2_dir = 1;
	*gpio2_data = 1;
}
void buzzer_off(void)
{
	*gpio2_dir = 1;
	*gpio2_data = 0;
}

void water_sprinkle(void)
{
	while (1) {
		motor_rotate(100, 0);
		mdelay(5000);
		motor_rotate(0, 100);
		mdelay(5000);
	}
}
void turnoff_motor(void)
{
	motor_stop();
}
void send_sms(void)
{
	serial_puts("AT\r");
	mdelay(10);
	serial_puts("AT+CMGF=1\r");
	mdelay(10);
	serial_puts("AT+CMGS=\"9597990320\"\r");
	mdelay(10);
	serial_puts("Save the life of people\r");
	mdelay(10);
	serial_putc(0x1A);
}

