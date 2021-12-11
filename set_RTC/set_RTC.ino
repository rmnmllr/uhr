// script for setting the DS1307 RTC time and reading it back every second
// note: Arduino needs to be connected via USB

#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {

  Serial.begin(57600);   // set baud rate of serial monitor

  // check USB connection
  #ifndef ESP8266
  while (!Serial);
  #endif

  // check RTC connection
  while (! rtc.begin()) {
    Serial.println("Couldn't find RTC, check connection.");
    Serial.flush();
    delay(1000);
  }

  Serial.println("RTC found!");

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
}

void loop() {

  DateTime now = rtc.now();     // get time from RTC

  // testing the RTC by reading the time
  int current_hr = now.hour();
  int current_min = now.minute();
  int current_sec = now.second()+5;   // +5 sec because of the delay from compiling until the Funduino runs the code

  // print time to SerialMonitor
  Serial.print("The current time is: ");
  Serial.print(current_hr);
  Serial.print(":");
  Serial.print(current_min);
  Serial.print(":");
  Serial.print(current_sec);
  Serial.println();

  delay(1000);
}
