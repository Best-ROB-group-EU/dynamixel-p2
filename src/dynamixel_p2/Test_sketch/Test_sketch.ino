#include <Wire.h>
#include <dynamixel_p2.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
int frequency = 10; // Value is in Hz.
Dynamixel_p2 TEST(13);
unsigned char trqen = 0;
unsigned short pos_gain_p = 0;
unsigned long samplingT = micros();


void setup() {
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);
 lcd.begin(16, 2); // The LCD is a 16x2.
 lcd.setBacklightPin(3, POSITIVE);
 lcd.setBacklight(HIGH);
 lcd.home(); //Cursor go to home
 lcd.print("READY");
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);
 Serial.begin(57600);
 TEST.begin(57600);
 //TEST.RAM(0xFE);
 TEST.setTorqueEnable(0xFE,false);
 //TEST.setGoalPosition(0x05, (unsigned long) 2200);
 //TEST.PingServo(0x01);
 //TEST.setGoalPWM(0x01, (unsigned long)512);
 //trqen = TEST.getTorqueEnable(1);
 //pos_gain_p = TEST.getPositionGainP(1);
 //Serial.println(trqen);
 //Serial.println(pos_gain_p);
 //delay(2000);
 //Serial.println(TEST.getPositionGainP(1));

  delay(500);
}

void loop() {
  lcd.clear();
  lcd.home();
  lcd.print(TEST.getPresentPosition(0x01));
  Serial.write((unsigned long)512);

  //TEST.MatlabTransmit();

  if(Serial.available() >= 3){
    for (int i = 0; i<3; i++){
      lcd.clear();
      lcd.print(bitconstruct());
      lcd.print(" ");
      lcd.print(Serial.read());
    }
  }
  delay(1000);
  
 /*
  if (micros() - samplingT > 1000000/frequency){ 
    //Serial.println(TEST.getPresentPosition((unsigned char)1));
    
  

    
    samplingT = micros();
  } */
}


unsigned long bitconstruct(){
  unsigned long value = 0;
  for (int i = 0; i < 2; i++){
    value += (Serial.read() << 8*i) & (0x000000FF << 8*i);
  }
  return value;
}
