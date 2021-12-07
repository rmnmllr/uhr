
#include <DFRobot_DS1307.h>


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
  // put your main code here, to run repeatedly:

  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)
  
  Serial.print(current_hr)
  Serial.print(current_min)
  Serial.print(current_sec)

  delay(1000)

}
