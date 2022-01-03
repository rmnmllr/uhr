// script for displaying the time with 24 hour LEDs and 12 minute LEDs (one per 5 minutes)
// note: be sure to set the time on the RTC before loading this script onto the Arduino

#include "RTClib.h"   // library for RTC communication

// intialise RTC class
RTC_DS1307 rtc;

// initialise hours digital pin output array according to connected wires
int hours[] = {23,25,27,29,31,33,35,37,39,41,43,45,36,34,32,30,28,26,24,22,50,51,49,47};

// number LEDs for hours
int h_zero_three = 44;    // 03
int h_zero_five = 42;     // 05
int h_zero_nine = 40;     // 09
int h_one_seven = 52;     // 17
int h_two_three = 48;     // 23

// number LEDs for minutes
int min_zero_five = 38;   // 05
int min_five_five = 55;   // 55

// initialise minutes digital pin output array
int minutes[12];
int m_pin_start = 2;

// get array length
int hours_len = sizeof(hours)/sizeof(*hours);
int minutes_len = sizeof(minutes)/sizeof(*minutes);

// initialise counting variables
int i, j, k, l, m, n;

void setup() {

  Serial.begin(57600);   // set baud rate of serial monitor

  Serial.println("Initialise output pins..");

  for (i=0; i<minutes_len; i++){
    minutes[i] = m_pin_start+i;
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

  // turn on all hour LEDs
  Serial.println("Turning on hour LEDs..");
  
  for (k=0; k<hours_len; k++){
    pinMode(hours[k], OUTPUT);      // set pin to output
    
    Serial.print("Turn hour LED output ");
    Serial.print(hours[k]);
    Serial.print(" on..");
    digitalWrite(hours[k], HIGH);   // turn LED on

    // switch conditional on hour number LEDs 03, 05, 09, 17, 23
    switch(k) {
      case 3:
        pinMode(h_zero_three, OUTPUT);
        digitalWrite(h_zero_three, HIGH);
        break;
      case 5:
        pinMode(h_zero_five, OUTPUT);
        digitalWrite(h_zero_five, HIGH);
        break;
      case 9:
        pinMode(h_zero_nine, OUTPUT);
        digitalWrite(h_zero_nine, HIGH);
        break;
      case 17:
        pinMode(h_one_seven, OUTPUT);
        digitalWrite(h_one_seven, HIGH);
        break;
      case 23:
        pinMode(h_two_three, OUTPUT);
        digitalWrite(h_two_three, HIGH);
        break;
    }
    Serial.println("");
    delay(100);                     // wait for 100 ms
  }

  Serial.println("All hour LEDs turned on!");
  delay(100);

  // turn on all minute LEDs
  Serial.println("Turning on minute LEDs..");
  
  for (l=0; l<minutes_len; l++){
    pinMode(minutes[l], OUTPUT);

    Serial.print("Turn minute LED output ");
    Serial.print(minutes[l]);
    Serial.print(" on..");
    digitalWrite(minutes[l], HIGH);

    // switch conditional on minute number LEDs 05 and 55
    switch(l) {
      case 0:
        pinMode(min_zero_five, OUTPUT);
        digitalWrite(min_zero_five, HIGH);
        break;
      case 11:
        pinMode(min_five_five, OUTPUT);
        digitalWrite(min_five_five, HIGH);
        break;
    }
    Serial.println("");
    delay(100);
  }
  
  Serial.println("All minute LEDs on!");
  Serial.println("Waiting for 5 seconds..");
  delay(5000);
  Serial.println("End of test, proceed to clock mode");
}

void loop() {

  // get time from RTC
  DateTime now = rtc.now();     // get time from RTC
  
  int current_hr = now.hour();
  int current_min = now.minute();
  int current_sec = now.second();

  // print time to serial monitor
  Serial.print("Current time according to RTC: ");
  Serial.print(current_hr);
  Serial.print(":");
  Serial.print(current_min);
  Serial.print(":");
  Serial.print(current_sec);
  Serial.println("");
  
  // set hour LEDs output after current time
  for (m=0; m<hours_len; m++){
    if (m<=current_hr){
      digitalWrite(hours[m], HIGH);
      switch(m) {
        case 3:
          pinMode(h_zero_three, OUTPUT);
          digitalWrite(h_zero_three, HIGH);
          break;
        case 5:
          pinMode(h_zero_five, OUTPUT);
          digitalWrite(h_zero_five, HIGH);
          break;
        case 9:
          pinMode(h_zero_nine, OUTPUT);
          digitalWrite(h_zero_nine, HIGH);
          break;
        case 17:
          pinMode(h_one_seven, OUTPUT);
          digitalWrite(h_one_seven, HIGH);
          break;
        case 23:
          pinMode(h_two_three, OUTPUT);
          digitalWrite(h_two_three, HIGH);
          break;
      }
      
    } else {
      digitalWrite(hours[m], LOW);
      switch(m) {
        case 3:
          pinMode(h_zero_three, OUTPUT);
          digitalWrite(h_zero_three, LOW);
          break;
        case 5:
          pinMode(h_zero_five, OUTPUT);
          digitalWrite(h_zero_five, LOW);
          break;
        case 9:
          pinMode(h_zero_nine, OUTPUT);
          digitalWrite(h_zero_nine, LOW);
          break;
        case 17:
          pinMode(h_one_seven, OUTPUT);
          digitalWrite(h_one_seven, LOW);
          break;
        case 23:
          pinMode(h_two_three, OUTPUT);
          digitalWrite(h_two_three, LOW);
          break;
      }
    }
  }

  // set minute LEDs output after current time
  for (n=0; n<minutes_len; n++){
    if (n<current_min/5){   // current_min/5 returns an integer since dividing integers will cut decimal values 
      digitalWrite(minutes[n], HIGH);
      switch(n) {
        case 0:
          pinMode(min_zero_five, OUTPUT);
          digitalWrite(min_zero_five, HIGH);
          break;
        case 11:
          pinMode(min_five_five, OUTPUT);
          digitalWrite(min_five_five, HIGH);
          break;
      }
      
      } else {
      digitalWrite(minutes[n], LOW);
      switch(n) {
        case 0:
          pinMode(min_zero_five, OUTPUT);
          digitalWrite(min_zero_five, LOW);
          break;
        case 11:
          pinMode(min_five_five, OUTPUT);
          digitalWrite(min_five_five, LOW);
          break;
      }
    }
  }

  delay(1000);

}
