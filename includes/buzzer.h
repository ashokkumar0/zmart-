#ifndef BUZZER_H
#define BUZZER_H

/**
 * Initalzes the PWM and delay needed
 * sets the pulse width and duty cycle.
 */
void buzzer_init(void);

/**
 * The frequency is varied by the pwm
 * to produce tones.
 */
int buzzer_sound(void);
#endif
