#include <eeprom.h>
#include <string.h>
#include <storage.h>

void store_write(const uint8_t *addptr)
{
	static uint8_t curr_addr = START_ADR;
	uint8_t total_tag = eeprom_read(TOT_ADD);
	uint8_t j;

	for (j = 0; addptr[j]; j++) {
		eeprom_write(curr_addr, addptr[j]);
		curr_addr++;
	}
	eeprom_write(curr_addr, '\0');

	curr_addr++;
	total_tag++;
	eeprom_write(0, total_tag);
	mdelay(1000);
}

int8_t store_read(uint8_t *readptr)
{
	lcd_puts("5");
	uint8_t temp_buff[MAX_CHAR];
	static uint8_t start_read = START_ADR; 
	int8_t ret;
	uint8_t j;
	uint8_t i = 0;

	while (i != (uint8_t)eeprom_read(TOT_ADD)) {
		printf("i%u, t%u", i, eeprom_read(TOT_ADD));
		for (j = 0; eeprom_read(start_read); j++, start_read++) {
			temp_buff[j] = eeprom_read(start_read);
		}

		temp_buff[j] = '\0';
		start_read++;
		i++;

		ret = strcmp(temp_buff, readptr);
		
		if (ret == 0) {
			start_read = START_ADR;
			return 0;
		}
	}

	start_read = START_ADR;
	return -1;
}
