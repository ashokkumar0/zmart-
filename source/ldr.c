#include <board.h>
#include <adc.h>

void ldr_init(void)
{
	adc_init();
	adc_enable(0);
}
uint8_t ldr_read (void)
{
	return adc_read8(0);	
}
