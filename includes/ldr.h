/**
 * ldr_init - enables ldr adc
 * 
 * enables adc for the ldr sensor
 **/
void ldr_init(void);

/**
 * ldr_read - Read the value of ldr
 * 
 * Read and return the value of ldr
 * @return : ldr value
 **/
uint8_t ldr_read(void);
