#include <serial.h>
#include <lcd.h>
#include <stdio.h>
#include <button.h>
#include <string.h>
#include "rfidread.h"
#include "main_func.h"
#include "storage.h"
#include "buzzer.h"
#include "stepper.h"

static uint8_t read_flag;
static uint8_t add_flag;
static uint8_t buff_id[MAX_CHAR];
static uint8_t master_count;
static uint8_t master_tag[MAX_CHAR] = MASTER_TAG;

void main_func(void)
{
	int8_t tx_err = RESET;
	int8_t ret = RESET;

	if (read_flag == RESET) {
		read_rfid(buff_id);
		tx_err = valid(buff_id);
		read_flag = 1;

		if (tx_err) {
			printf("Transmission Error\n");
			printf("Swipe Again\n");
			read_flag = RESET;
		} else {
			read_valid(buff_id);

			if (!strcmp(master_tag, buff_id) && !master_count) {
				master_count++;
				read_flag = RESET;
				printf("Swipe tag and\nPress 1 to \nAdd Tag\n");
			} 

			if (!master_count){
				ret = store_read(buff_id);

				if (ret) {
					printf("Not Found!\n");
					mdelay(2000);
					buzzer_sound();
					printf("buzz over\n");
				} else {
					printf("User Found\n");
					door_open();
					mdelay(FIVE_SEC);
					door_close();
				}

				read_flag = RESET;
				lcd_clear();
			}
			serial_init();
		}
	}
}

void key_press(void)
{
	uint8_t key;
	int8_t ret;

	lcd_clear();

	if (read_flag) {
		key = (uint8_t)button_getc();

		if (key == KEY_1 && strcmp(master_tag, buff_id)) {
			if (!store_read(buff_id))
				lcd_puts("User Already Added\n");
			else {
				store_write(buff_id);
				lcd_puts("Tag added");
			}
		} else if (key && strcmp(master_tag, buff_id)){
			printf("Press key 1 only!\n");
		} else {
			printf("Cant add Master Tag\n");
		}
	} else {
		printf("Swipe Tag First\n");
	}

	master_count = RESET;
	button_init();
	serial_init();
	mdelay(FIVE_SEC);
	lcd_clear();
	read_flag = RESET;
}
