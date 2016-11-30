#include <board.h>
#include <lcd.h>
#include "relay.h"

void light_on_out(void)
{
	volatile uint32_t *dir1 = (uint32_t *) (PORT3_BASE + DIR);
	volatile uint32_t *led1 = (uint32_t *) (PORT3_BASE + DATA);

	*dir1 = 1;
	*led1 = 1;
}

void light_off_out(void)
{
	volatile uint32_t *dir1 = (uint32_t *) (PORT3_BASE + DIR);
	volatile uint32_t *led1 = (uint32_t *) (PORT3_BASE + DATA);
 
	*dir1 = 1;
	*led1 = 0;
}

void light_on_in(void)
{
	volatile uint32_t *dir2 = (uint32_t *) (PORT0_BASE + DIR);
	volatile uint32_t *led2 = (uint32_t *) (PORT0_BASE + DATA);

	*dir2 = 0x80;
	*led2 = 0x80;
}

void light_off_in(void)
{
	volatile uint32_t *dir2 = (uint32_t *) (PORT0_BASE + DIR);
	volatile uint32_t *led2 = (uint32_t *) (PORT0_BASE + DATA);

	*dir2 = 0x80;
	*led2 = 0x0;
}

void func_call(timer_t *timer)
{
	int in;
	int out;
	ldr_init();
	out = ldr_read();
	board_stdout(LCD_STDOUT);
	printf("%d", out);
	in = sense_pir();
	if (out == 1)
		light_on_out();
	else
		light_off_out();
	if (in == 1)
		light_on_in();
	else
		light_off_in();
	timer_setup(timer, 1000);
}
