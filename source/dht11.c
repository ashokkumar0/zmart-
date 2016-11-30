#include <timer32.h>
#include <dht11.h>
#include <stdbool.h>

bool state;

void dht11_init(void)
{
	bool state = 0;
	timer32_init();
	timer32_reset();
}

int dht11_read(uint8_t *data)
{	
	int i = 0;
	int j = 0;
	int val = 0;
	volatile uint32_t * port1_dir  = (uint32_t *) GPIO1DIR;
	volatile uint32_t * port1_data = (uint32_t *) GPIO1DATA;
	for (i = 0; i < 5; i++)
		data[i] = 0;
	timer32_reset();
	if (state == 0) {
		state = 1;
		while (timer32_mread() < 2000)
			;
	}
	*port1_dir |= 0x2;
	*port1_data &= ~(0x2);
	timer32_reset();
	while (timer32_mread() < 20)
		;
	*port1_dir &= ~(0x2);
	timer32_reset();
	while((*port1_data >> 1) & 0x1)
		if (timer32_uread() > 10000)
			return -1;
	timer32_reset();
	while(!((*port1_data >> 1) & 0x1))
		if(timer32_uread() > 10000)
			return -1;
	timer32_reset();
	while((*port1_data >> 1) & 0x1)
		if (timer32_uread() > 10000)
			return -1;
	timer32_reset();
	while(!((*port1_data >> 1) & 0x1))
		if(timer32_uread() > 10000)
			return -1;
	timer32_reset();
	while((*port1_data >> 1) & 0x1)
		if (timer32_uread() > 10000)
			return -1;		
	for (i = 0; i < 5; i++) {
		for (j = 7; j >= 0; j--) {
			timer32_reset();	
			while(!((*port1_data >> 1) & 0x1)) 
				if(timer32_uread() > 10000)
					return -1;
			timer32_reset();
			while((*port1_data >> 1) & 0x1) 		
				if (timer32_uread() > 40) 
					data[i] |= (1 << j);				
		}
	}
	val = data[0] + data[1] + data[2] + data[3];
	if (!(val == data[4]))
		return -1;
	return 0;
}

uint8_t dht11_get_humidity(void)
{
	uint8_t data[5];
	int i;
	for (i = 0; i < 10; i++)
		if(!(dht11_read(data)))
			return data[0];	   
}

uint8_t dht11_get_temperature(void)
{
	uint8_t data[5];
	int i;
	for (i = 0; i < 10; i++)
		if(!(dht11_read(data)))
			return data[2];
}
