
#ifndef STEPPER_H
#define STEPPER_H

#define STEP 8
#define ROTATION 3
#define PHASE 4

void door_open(void);
void door_close(void);
void stepper_turn(int *);

#endif
