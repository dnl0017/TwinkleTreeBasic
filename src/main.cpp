#include <Arduino.h>
#define TX_PIN 2    //  Must define this before including ATtinySerialOut lib.
#include <ATtinySerialOut.hpp>
#define OUT_PIN 4
#define IN_PIN 3

int brightness = 0;

void setup() {
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);
  initTXPin();
}

void loop() {
    brightness = analogRead(IN_PIN);
  
    Serial.println("Hello World!");
    Serial.println(brightness);

    analogWrite(OUT_PIN, brightness / 4 );
    delay(200);
  
}




// void effect_fadein(){
//   playing = true;

//   int level = 0;
//   while (playing && state_on) {
//       pio_pwm_set_level(pio, sm, level * level);
//       level = (level + 1) % 256;
//       sleep_ms(10);
//   }
// }

// void effect_blink(){ 
//   playing = true;

//   while (playing && state_on) {
//     pio_pwm_set_level(pio, sm, 0);
//     sleep_ms(500);
//     pio_pwm_set_level(pio, sm, 256*256-1);
//     sleep_ms(500);
//   }
// }

// void effect_fadeinout(){
//   playing = true;

//   int level = 255;

//   while (playing && state_on) {
//       pio_pwm_set_level(pio, sm, level * level);
//       level = (level - 1) % 256; 
//       level = level < -254 ? 255 : level;
//       sleep_ms(10);
//   }
// }

// void effect_spooky(){
//     playing = true;

//     int level = 0;
//     srand(255);

//     while (playing && state_on) {
//         pio_pwm_set_level(pio, sm, level * level);
//         level = rand() %  256; 
//         sleep_ms(100);
//     }
// }