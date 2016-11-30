#include"remote_api.h"
#include<board.h>
#include<lcd.h>
#include<timer.h>
#include"ir3.h"
#include<gpio.h>

timer_t timer1;
		
int main(void)
{
	board_init();
	lcd_init();
	gpio_init();
	board_stdout(LCD_STDOUT);
	remote_init();
	timer_setup(&timer1, 10);
	timer_setcb(&timer1, check_queue_status);
	event_poll();
	return 0;
}
