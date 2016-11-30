#define GPIO1DIR 0x50018000
#define GPIO1DATA 0x50013ffc
/**
 * dht11_init - Initialize the dht11 module
 * 
 * Initialize the timer and dht11 modules.
 */
void dht11_init(void);

/**
 * dht11_read - read the value from dht11
 * @data : Pointer to a memory
 *
 * Read the dht11 sensor value and return error no.
 * return : error no
 */
int dht11_read(uint8_t *data);

/**
 * dht11_get_humidity -return the humidity value
 *
 * Returns the humidity value from the sensor
 * return : Humidity value
 */
uint8_t dht11_get_humidity(void);

/**
 * dht11_get_temperature - returns the temperature value
 *
 * Returns the temperature value
 * return: Temperature value
 */
uint8_t dht11_get_temperature(void);
