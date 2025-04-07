#include <Arduino.h>
#define DBG 0
#if DBG == 1
#define TX_PIN 2    //  Must define this before including ATtinySerialOut lib.
#include <ATtinySerialOut.hpp>
#endif
#define OUT_PIN 4
#define IN_PIN  3
#define BTN_PIN 1

//   (PCINT5/RESET/ADC0/dW)          PB5 |1     8| VCC
//   (PCINT3/XTAL1/CLKI/OC1B/ADC3)   PB3 |2     7| PB2 (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
//   (PCINT4/XTAL2/CLKO/OC1B/ADC2)   PB4 |3     6| PB1 (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
//                                   GND |4     5| PB0 (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)

unsigned long lastCheckTime = 0;
unsigned long const checkInterval = 10;  //  Check every 10 milliseconds.
bool checkState = false;

unsigned long lastExecuteTime = 0;
unsigned long const executeInterval = 200;  //  execute every 200 milliseconds.
bool executeState = false;

// state variables
volatile uint16_t brightness = 0; 
int level = 0;
volatile bool on = false;          //  button on / off

// Tasks
void taskCheck(void);
void taskExecute(void);

//  Array of functions / tasks
void effect_fadein(void);
void effect_fadeinout(void);
void effect_blink(void);
void effect_spooky(void);
void effect_none(void);

static uint8_t effect_counter = 0;

typedef void (*effect)(void);
const struct{
  effect efct;
  const char *name;
} effect_table[] = {
  {effect_none, "none"},
  {effect_fadein, "fadein"},
  {effect_fadeinout, "fadeinout"},
  {effect_blink, "blink"},
  {effect_spooky, "spooky"}
};
