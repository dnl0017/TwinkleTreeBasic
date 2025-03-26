#include "ledtreebasic.h"

void setup() {
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);
  pinMode(BTN_PIN, INPUT);
#if DBG == 1   
  initTXPin();
#endif
  srand(256);
}

void loop() {

    taskCheck();

    taskExecute();
#if DBG == 1 
    Serial.print("brightness: ");Serial.print(brightness);  
    Serial.print(", state: ");Serial.print(on?"on":"off");
    Serial.print(", effect: ");Serial.print(effect_table[effect_counter].name);
    Serial.print(", counter: ");Serial.println(effect_counter);
#endif
    delay(1);  
}

void taskCheck(){
  if (millis() - lastCheckTime >= checkInterval){
    lastCheckTime = millis();
    checkState = !checkState;

    brightness = analogRead(IN_PIN) / 4;
    on = digitalRead(BTN_PIN);    

  }
}

void taskExecute(){
  if (millis() - lastExecuteTime >= executeInterval){
    lastExecuteTime = millis();
    executeState = !executeState;

    if(on){
      effect_counter = (effect_counter + 1) % (sizeof(effect_table) / 4);
    }

    effect_table[effect_counter].efct();
  } 
}

void effect_fadein(){
  analogWrite(OUT_PIN, level * level);
  level = (level + 1) % 16;
  delay(150);
}

void effect_blink(){ 
  analogWrite(OUT_PIN, 0);
  delay(75);
  analogWrite(OUT_PIN, 255);
  delay(75);
}

void effect_fadeinout(){
  analogWrite(OUT_PIN, level * level);
  level = (level - 1) % 16; 
  level = level < -14 ? 15 : level;
  delay(150);
}

void effect_spooky(){
  analogWrite(OUT_PIN, level * level);
  level = rand() %  16; 
  delay(150);
}

void effect_none(){
  analogWrite(OUT_PIN, brightness);
  delay(150);
}

