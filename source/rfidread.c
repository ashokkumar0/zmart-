#include "rfidread.h"
#include <board.h>
#include <serial.h>
#include <stdio.h>

/*
* read_rfid()- Read Tag ID
* @arr - Pointer to array
* Read the Tag ID by serial communication
*/

void read_rfid(uint8_t *arr)
{
	int8_t i;

	for (i = 0; i < 12; i++)
		arr[i] = serial_getc();
	serial_init();
}



/*
* valid() - Validating Tag ID
* @arr - Pointer to input array
* Validating Tag ID based on start and stop byte
* return 0 for valid Tag ID -1 for invalid Tag ID
*/

int8_t valid(uint8_t *arr)
{
	if (arr[START] != '\n' || arr[STOP] != '\r')
		return -1;
	return 0;
}



/*
* read_valid() - Read valid Tag ID
* @rfid_no - Pointer to array
* Read valid Tag ID by removing start and stop byte
*/

void read_valid(uint8_t *rfid_no)
{
	uint8_t i = 0;
	uint8_t j = 0;

	for (; rfid_no[j] != '\r';) {
		if (rfid_no[j] == '\n')
			rfid_no[i] = rfid_no[++j];
		rfid_no[i++] = rfid_no[j++];
	}
	rfid_no[i] = '\0';
	printf("ID: %s\n", rfid_no);
	printf("work\n");
}

