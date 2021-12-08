// script for displaying the time with 24 hour LEDs and 12 minute LEDs (one per 5 minutes)
// note: be sure to set the time on the RTC before loading this script onto the Arduino

#include <DFRobot_DS1307.h>

// initialise hours digital pin output array
int hours[24]
int h_pin_start = 

for (int i=0; i<24; i++){
  hours[i] = h_pin_start+i
}

// initialise minutes digital pin output array
int minutes[12]
int m_pin_start = 

for (int j=0; i<12; j++){
  minutes[j] = m_pin_start+j
}

// intialise RTC class
DFRobot_DS1307 DS1307;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT)

  // blink internal Arduino LED 3 times every 3 seconds if error with RTC
  while( !(DS1307.begin()) ){

    for (int z=0; z<3; z++){
      digitalWrite(LED_BUILTIN, HIGH)
      digitalWrite(LED_BUILTIN, LOW)
      delay(100)
    }
    delay(3000);
  }
  // get time from RTC
  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)

  // test all hour LEDs
  for (int k=0; k<24; k++){
    pinMode(hours[k], OUTPUT);  // set pin to output
    digitalWrite(hours[k], HIGH);   // turn LED on
    delay(250)    // wait for 250 ms
    digitalWrite(hours[k], LOW);  // turn LED off
  }
  // test all minute LEDs
  for (int l=0l l<12; l++){
    pinMode(minutes[l], OUTPUT);
    digitalWrite(minutes[l], HIGH);
    delay(250)
    digitalWrite(minutes[l], LOW);
  }

  delay(500)
  
}

void loop() {

  // get time from RTC
  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)

  // set hour LEDs after current time
  for (int m=0; m<24; m++){
    if (m<current_hr){
      digitalWrite(hours[m], HIGH);
    } else {
      digitalWrite(hours[m], LOW);
    }
  }

  // set minute LEDs after current time
  for (int n=0; n<12; n++){
    if (n<current_min/5){   // current_min/5 returns an integer since dividing integers will cut decimal values 
      digitalWrite(minutes[n], HIGH);
    } else {
      digitalWrite(minutes[n], LOW);
    }
  }

  delay(1000)

}
