#define MASK 1

/**
 *
 * Checks for the last bit in the register
 * where PIR value is stored
 *
 * Return: 1 if PIR is detected
 *         0 if not present
 */
int sense_pir(void);
