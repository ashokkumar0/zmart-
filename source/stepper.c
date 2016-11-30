#include <stepper.h>
#include <stdint.h>
#include <board.h>
#include <delay.h>
#include <gpio.h>

void stepper_turn(uint8_t *turn)
{
	int mask = 0x01;
	int count;
	int i;
	int j;

	for (count = 0; count < ROTATION; count++) {
		for (i = 0; i < STEP; i++) {
			for (j = 0; j < PHASE; j++) {
				if (turn[i] & (mask << j))
					gpio_set_pin(GPIO2_0 + j, 1);
				else
					gpio_set_pin(GPIO2_0 + j, 0);
			}
			mdelay(50);
		}
	}
}

void door_open(void)
{
	uint8_t forward_dir[STEP] = { 8, 9, 1, 5, 4, 6, 2, 10};
	stepper_turn(forward_dir);
}

void door_close(void)
{
	uint8_t reverse_dir[STEP] = { 2, 6, 4, 5, 1, 9, 8, 10};
	stepper_turn(reverse_dir);
}
