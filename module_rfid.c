#include <board.h>
#include <serial.h>
#include<delay.h>
#include <lcd.h>
#include <string.h>
#include <event.h>
#include <eeprom.h>
#include <fifo.h>
#include "main_func.h"
#include "storage.h"

int main(void)
{
	board_init();
	lcd_init();
	serial_init();
	event_init();
	eeprom_init();
	button_init();
	delay_init();

	int i;

	board_stdout(LCD_STDOUT);
	serial_rx_setcb(main_func);
	button_setcb(key_press);
	eeprom_write(0, 0);
	lcd_puts("Swipe Tag\n");
	
	event_poll();
	return 0;
}
