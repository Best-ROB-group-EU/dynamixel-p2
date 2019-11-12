#include <dynamixel_p2.h>

Dynamixel_p2 TEST(13);

void setup() {
 Serial.begin(57600);
 TEST.begin(57600);
 TEST.setTorqueEnable(0xFE, (unsigned long) 1);
 TEST.setGoalPosition(0xFE, (unsigned long) 0);
 //TEST.PingServo(0x01);
 //TEST.setGoalPWM(0x01, (unsigned long)512);

}

void loop() {

}
