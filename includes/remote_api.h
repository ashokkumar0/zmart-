#ifndef REMOTE_H_
#define REMOTE_H_
#include<fifo.h>
#include<timer.h>
void check_queue_status(timer_t *timer);
int execute_command(unsigned char l);
void toggle_light_state(void);
#endif
