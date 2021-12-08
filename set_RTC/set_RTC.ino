// script for setting the DS1307 RTC time and reading it back every second
// note: Arduino needs to be connected via USB


#include <DFRobot_DS1307.h>

Serial.begin(115200);   // set baud rate of serial monitor

void setup() {
  // put your setup code here, to run once:

  // check RTC connection
  while( !(DS1307.begin()) ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  DS1307.setTypeTime(DS1307.eHR, 12);
  DS1307.setTypeTime(DS1307.eMIN, 0);
  DS1307.setTypeTime(DS1307.eSEC, 0);
}

void loop() {

  // testing the RTC by reading the time
  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)

  // print time to SerialMonitor
  Serial.print(current_hr)
  Serial.print(current_min)
  Serial.print(current_sec)

  delay(1000)

}
