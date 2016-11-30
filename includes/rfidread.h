#include <stdint.h>

#define MAX_CHAR 12
#define START 0
#define STOP 11
#define AUTH_FAIL -1
#define AUTH_PASS 0
#define FIVE_SEC 5000

void read_rfid(uint8_t *arr);
int8_t valid(uint8_t *arr);
void read_valid(uint8_t *arr);
