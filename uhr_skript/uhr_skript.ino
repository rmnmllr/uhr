// script for displaying the time with 24 hour LEDs and 12 minute LEDs (one per 5 minutes)
// note: be sure to set the time on the RTC before loading this script onto the Arduino

#include "RTClib.h"

// intialise RTC class
RTC_DS1307 rtc;

// initialise hours digital pin output array
int hours[24];
int h_pin_start = 22;

// initialise minutes digital pin output array
int minutes[12];
int m_pin_start = 2;

int i, j, k, l, m, n;

void setup() {

  Serial.begin(57600);   // set baud rate of serial monitor

  Serial.println("Initialise output pins..");

  for (i=0; i<24; i++){
    hours[i] = h_pin_start+i;

    if (i<12) {
      minutes[i] = m_pin_start+i;
    }
  }

  Serial.println("Initialise done!");
  
  pinMode(LED_BUILTIN, OUTPUT);

  // blink internal Arduino LED 3 times every 3 seconds if error with RTC
  while (!(rtc.begin())){

    Serial.println("Couldn't find RTC, check connection.");
    Serial.flush();
    
    for (j=0; j<3; j++){
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
    delay(3000);
  }

  // test all hour LEDs
  Serial.println("Testing LEDs..");
  
  for (k=0; k<24; k++){
    pinMode(hours[k], OUTPUT);      // set pin to output
    delay(100);                     // wait for 100 ms
    
    Serial.print("Turn hour LED output ");
    Serial.print(hours[k]);
    Serial.print(" on..");
    digitalWrite(hours[k], HIGH);   // turn LED on
    delay(100);
    Serial.println(" and off");
    digitalWrite(hours[k], LOW);    // turn LED off
  }

  Serial.println("Hour LEDs tested!");
  delay(100);

  // test all minute LEDs
  for (l=0; l<12; l++){
    pinMode(minutes[l], OUTPUT);
    delay(100);

    Serial.print("Turn minute LED output ");
    Serial.print(minutes[l]);
    Serial.print(" on..");
    digitalWrite(minutes[l], HIGH);
    delay(100);
    Serial.println(" and off");
    digitalWrite(minutes[l], LOW);
  }
  
  Serial.println("Minute LEDs tested!");

  delay(500);
  
}

void loop() {

  // get time from RTC
  DateTime now = rtc.now();     // get time from RTC
  
  int current_hr = now.hour();
  int current_min = now.minute();
  int current_sec = now.second()+5;   // +5 sec because of the delay from compiling delay while setting up the RTC

  // set hour LEDs output after current time
  for (m=0; m<24; m++){
    if (m<current_hr){
      digitalWrite(hours[m], HIGH);
      delay(100);
    } else {
      digitalWrite(hours[m], LOW);
      delay(100);
    }
  }

  // set minute LEDs output after current time
  for (n=0; n<12; n++){
    if (n<current_min/5){   // current_min/5 returns an integer since dividing integers will cut decimal values 
      digitalWrite(minutes[n], HIGH);
      delay(100);
      } else {
      digitalWrite(minutes[n], LOW);
      delay(100);
      }
  }

  delay(1000);

}
