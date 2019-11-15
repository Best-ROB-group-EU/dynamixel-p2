#include <dynamixel_p2.h>

Dynamixel_p2 TEST(13);

unsigned char trqen = 0;
unsigned short pos_gain_p = 0;

void setup() {
 Serial.begin(57600);
 TEST.begin(57600);
 //TEST.RAM(0xFE);
 TEST.setTorqueEnable(0xFE, (unsigned long) 1);
 //delay(1000);
 //TEST.setGoalPosition(0xFE, (unsigned long) 2048);
 //TEST.PingServo(0x01);
 //TEST.setGoalPWM(0x01, (unsigned long)512);
 trqen = TEST.getTorqueEnable(1);
 //pos_gain_p = TEST.getPositionGainP(1);
 Serial.println(trqen);
 //Serial.println(pos_gain_p);
 //delay(2000);
 //Serial.println(TEST.getPositionGainP(1));

}

void loop() {
  //Serial.println(TEST.getPresentPosition(1));
}
