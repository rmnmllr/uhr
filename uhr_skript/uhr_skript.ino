
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

// intialise RTC
DFRobot_DS1307 DS1307;

void setup() {

  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)

  
  
}

void loop() {

  int current_hr = DS1307.getTypeTime(DS1307.eHR)
  int current_min = DS1307.getTypeTime(DS1307.eMIN)
  int current_sec = DS1307.getTypeTime(DS1307.eSEC)

}
