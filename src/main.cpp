#include <Arduino.h>
#define TX_PIN 2    //  Must define this before including ATtinySerialOut lib.
#include <ATtinySerialOut.hpp>
#define OUT_PIN 4
#define IN_PIN 3
#define BUTT_PIN 1

void effect_fadein(void);
void effect_fadeinout(void);
void effect_blink(void);
void effect_spooky(void);

static uint8_t effect_counter = 0;

typedef void (*effect)(void);
const struct{
  effect efct;
  const char *name;
} effect_table[] = {
  {NULL, "none"},
  {effect_fadein, "fadein"},
  {effect_fadeinout, "fadeinout"},
  {effect_blink, "blink"},
  {effect_spooky, "spooky"}
};

volatile int brightness = 0;
volatile int on = 0;

void setup() {
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);
  pinMode(BUTT_PIN, INPUT);
  initTXPin();
}

void loop() {
    brightness = analogRead(IN_PIN);
    on = digitalRead(BUTT_PIN);
    Serial.print("brightness: ");
    Serial.print(brightness);  
    Serial.print(", state: ");  
    Serial.print(on?"on":"off");
    Serial.print(", effect: ");
    Serial.println(effect_table[effect_counter++ % sizeof(effect_table)].name);

    analogWrite(OUT_PIN, brightness / 4 );

    if(on){
      effect_table[effect_counter++ % sizeof(effect_table)].efct();
    }

    delay(200);  
}


void effect_fadein(){

  int level = 0;
  //while (on) {
      analogWrite(OUT_PIN, level * level);
      level = (level + 1) % 256;
      delay(10);
  //}
}

void effect_blink(){ 

  //while (on) {
    analogWrite(OUT_PIN, 0);
    delay(500);
    analogWrite(OUT_PIN, 255*255-1);
    delay(500);
  //}
}

void effect_fadeinout(){

  int level = 255;

 // while (on) {
      analogWrite(OUT_PIN, level * level);
      level = (level - 1) % 256; 
      level = level < -254 ? 255 : level;
      delay(10);
  //}
}

void effect_spooky(){

    int level = 0;
    srand(255);

   // while (on) {
        analogWrite(OUT_PIN, level * level);
        level = rand() %  256; 
        delay(100);
   // }
}