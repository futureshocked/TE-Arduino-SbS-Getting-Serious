#include <DFRobot_SGP40.h>

DFRobot_SGP40    mySgp40;

void setup() {
  Serial.begin(115200);
  Serial.println("SGP40 is starting, the reading can be taken after 10 seconds...");
  
  while(mySgp40.begin(/*duration = */10000) !=true){
    Serial.println("failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }
  Serial.println("----------------------------------------------");
  Serial.println("sgp40 initialized successfully!");
  Serial.println("----------------------------------------------");
}

void loop() {
  /* 
   *    0-100，no need to ventilate,purify
   *    100-200，no need to ventilate,purify
   *    200-400，ventilate,purify
   *    400-500，ventilate,purify intensely
   */
  uint16_t index = mySgp40.getVoclndex();
  
  Serial.print("vocIndex = ");
  Serial.println(index);
  delay(1000);
}