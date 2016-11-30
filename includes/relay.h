#include <timer.h>
#include <board.h>

#define PORT0_BASE 0x50000000
#define PORT2_BASE 0x50020000
#define PORT3_BASE 0x50030000
#define DIR 0x8000
#define DATA 0x3FFC

void light_on_out(void);
void light_off_out(void);
void light_on_in(void);
void light_off_in(void);
void func_call(timer_t *timer);
