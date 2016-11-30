#include <board.h>
#include <pir.h>
#define PORT0_BASE 0x50000000
#define PORT2_BASE 0x50020000
#define PORT3_BASE 0x50030000
#define DIR 0x8000
#define DATA 0x3FFC

int sense_pir(void)
{
	volatile uint32_t *dir = (uint32_t *) (PORT2_BASE + DIR);
	volatile uint32_t *input = (uint32_t *) (PORT2_BASE + DATA);
 
	if ((*input & MASK))
		return 1;
	else
		return 0;
}
