#include <dynamixel_p2.h>

Dynamixel_p2 TEST(13);

void setup() {
 Serial.begin(9600);
 TEST.setGoalPosition(0x01, (unsigned long)512);

}

void loop() {

}
