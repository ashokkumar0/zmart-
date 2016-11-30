#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#define MAX_CHAR 12
#define TAG_SWIPED 1
#define SET 1
#define RESET 0
#define KEY_1 0
#define FIVE_SEC 5000
#define MASTER_TAG "15001A601D"

/**
 * The main function which reads the tag 
 * and checks all the errors occured
 * it calls all the other needed functions.
 */
void main_func(void);

/**
 * Detects the Key pressed and differentiates
 * the operations based on it
 * Will add tag to storage or check with
 * existing tags.
 */
void key_press(void);

#endif
