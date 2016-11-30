#include"remote_api.h"
#include<timer.h>
#include"ir3.h"
#include<board.h>
#include<gpio.h>
#include<lcd.h>
static bool fan_state = 0;
static bool light_state = 0;

void check_queue_status(timer_t *timer)
{
	
	unsigned char j = check_key('r');
	execute_command(j);
	timer_setup(timer, 10);
}

int execute_command(unsigned char l)
{
	if (l == 46)
		toggle_light_state();
	else
		return 0;
}

void toggle_light_state(void)
{
	if(light_state == 0) {
		gpio_enable_pin(LED1_GPIO);
		gpio_direction_output(LED1_GPIO, 0);
		gpio_set_pin(LED1_GPIO, 1);
		light_state = 1;
	} else {
		gpio_enable_pin(LED1_GPIO);
		gpio_direction_output(LED1_GPIO, 0);
		gpio_set_pin(LED1_GPIO, 0);
		light_state = 0;
	}
}
		
	
		
