#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

/*
   This program uses two variables to track events: the current event (event) and a previous event (lastEvent).  
   The event codes are as follows:
   
   0 - No event / ignore
   1 - Pot placed on the scale
   2 - Weight decrease from last measurement
   3 - Pot removed from scale
*/


//Global Variables
SR04 sensor = SR04(ECHO_PIN,TRIG_PIN);
const long MAX_DISTANCE = 40;
const long DISTANCE_BUFFER = 3;
long oldDistance;
int lastEvent;
int d = 500;


void setup() {
   Serial.begin(9600);
   delay(1000);

   oldDistance = 999;
   lastEvent = 3;
}


void loop() {
    long newDistance = sensor.Distance();
   

    int event = 0;

    if(lastEvent == 3) {
      if(newDistance < MAX_DISTANCE) {
        event = 1;
        lastEvent = 1;
        oldDistance = newDistance;
      }
      else {
        oldDistance = newDistance;
      }
    }
    else {
      if(newDistance > MAX_DISTANCE){
        event = 3;
        lastEvent = 3;
        oldDistance = newDistance;
      }
      else if(newDistance > oldDistance) {
        event = 2;
        lastEvent = 2;
        oldDistance = newDistance;
      }
    }

    //output data
    if(event > 0) {
      Serial.print("NEW: ");
      Serial.print(newDistance);
      Serial.print(" OLD: ");
      Serial.print(oldDistance);
      Serial.print(" EVENT: ");
      Serial.print(event);
      Serial.print("\n");

      lastEvent = event;
    }

    delay(d);
}
