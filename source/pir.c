#include <pir.h>
#include <stdint.h>
#define PORT2_BASE 0x50020000
#define DIR 0x8000
#define DATA 0x3FFC
#define MASK 1

int sense_pir(void)
{
	volatile uint32_t *dir = (uint32_t *) (PORT2_BASE + DIR);
	volatile uint32_t *input = (uint32_t *) (PORT2_BASE + DATA);
 
	if ((*input & MASK))
		return 1;
	else
		return 0;
}
