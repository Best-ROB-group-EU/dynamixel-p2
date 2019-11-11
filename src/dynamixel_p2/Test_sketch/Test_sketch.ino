#include <dynamixel_p2.h>

byte pkg [16];
Dynamixel_p2 TEST(13);

void setup() {
 TEST.setGoalPosition(0x01, (unsigned long)512);
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i<16; i++){
    Serial.print(pkg[i]);
  }

}
