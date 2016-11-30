#include <board.h>
#include <adc.h>
#include <lcd.h>
#include <stdio.h>
#include <timer.h>
#include "pir.h"
#include "ldr.h"
#include "relay.h"

#define PORT0_BASE 0x50000000
#define PORT2_BASE 0x50020000
#define PORT3_BASE 0x50030000
#define DIR 0x8000
#define DATA 0x3FFC
#define CUTOFF 100

int main()
{
	timer_t timer1;

	board_init();
	lcd_init();
	timer_init();
	board_stdout(LCD_STDOUT);
	timer_setup(&timer1, 1000);
	timer_setcb(&timer1, (event_xhandle_t) func_call);
	event_poll();

	
	return 0;
}
