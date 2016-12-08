#include <hdisplay.h>
#include <stdint.h>

void hdisplay_init()
{
	volatile uint32_t * data = (uint32_t *) gpio2_data;
	volatile uint32_t * dir = (uint32_t *) gpio2_dir;

	*dir = 0x00000FFF;
	*data = 0;
}

void hdisplay_temp(int num)
{
	
        uint32_t arr[] = {
		0x3f,
		0x06,
		0x5b,
		0x4f,
		0x66,
		0x6d,
		0x7d,
		0x07,
		0x7f
	};
	volatile uint32_t * data = (uint32_t *) gpio2_data;
	int b[2];
	int i;
	
	for(i = 0; i < 2; i++) {
		b[i] = num % 10;
		num = num / 10;
	}
	for(i = 0;i < 5000; i++) {
		*data = 0x000 | arr[b[0]];
		*data = 0x100 | arr[b[1]];
	}
}
