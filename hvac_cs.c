#include <timer.h>
#include <stdio.h>
#include <dht11.h>
#include <ir.h>
#include <dc_motor.h>
#include <hdisplay.h>
#include <stdbool.h>

static bool on_off_flag = 0;
static uint32_t temperature;
static uint32_t fan_speed;
static timer_t timer1;
static timer_t timer0;

static void alter_temperature(int t)
{
  volatile uint32_t * led_dir = (uint32_t *) 0x50038000;
  volatile uint32_t * led_data = (uint32_t *) 0x50033ffc;
  
  uint8_t room_temp = dht11_get_temperature();

  if(on_off_flag == 1) {
    * led_dir = 1;
    if(t > 30)
      temperature = 30;
    if(t < 16)
      temperature = 16;
    if(room_temp < temperature) {
      // compressor off
      * led_data = 0;
    } else if(room_temp >= temperature) {
      // compressor on
      * led_data = 1;
    }
  }
}


static void time_call()
{
  alter_temperature(temperature);
  timer_setup(&timer1, 5000);
}

static void alter_fan_speed(int f)
{
  if(on_off_flag == 1) {
    if(f > 3)
      fan_speed = 1;
  }
}

static void power(void)
{
  
  volatile uint32_t * led2_dir = (uint32_t *) 0x50008000;
  volatile uint32_t * led2_data = (uint32_t *) 0x50003ffc;

  *led2_dir |= (1 << 7);
  *led2_data &= ~(1 << 7);
  
  on_off_flag = !on_off_flag;
  if(on_off_flag == 1) {
    *led2_data |= (1 << 7);
    temperature = 22;
    fan_speed = 2;
    alter_temperature(temperature);
    alter_fan_speed(fan_speed);
  }else if(on_off_flag == 0)
    *led2_data &= ~(1 << 7);
}

static void ac_key(void)
{
  int key;
  unsigned char hkey;
  hdisplay_temp(temperature);
  hkey = check_key('a');
  if(hkey != 99) {
    key = (int) hkey;
    switch(key) {
    case 84:
      power();
      break;
    case 23:
      alter_temperature(++temperature);
      break;
    case 87:
      alter_temperature(--temperature);
      break;
    case 83:
      alter_fan_speed(++fan_speed);
    }
  }
}

void hvac_init()
{
  timer_init();
  hdisplay_init();
  dht11_init();
  motor_init();
  remote_init();
  motor_start();
  timer_setup(&timer0, 50);
  timer_setcb(&timer0,(event_xhandle_t) ac_key);
  timer_setup(&timer1, 5000);
  timer_setcb(&timer1,(event_xhandle_t) time_call);	
  event_poll();

}

