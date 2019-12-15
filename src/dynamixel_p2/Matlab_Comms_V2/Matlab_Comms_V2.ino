#include <dynamixel_p2.h>
Dynamixel_p2 TEST(13);
bool receive = true; // Used to switch between recieve and transmit mode.
byte rxpacket[8]; //Holds Current1,2,3 and Event.

void setup() {
  Serial.begin(57600);
  TEST.begin(57600);
  TEST.setTorqueEnable(0xFE,true);

  //Debug

  
}

void loop() {
  
  
  if(receive) {
    while (Serial1.available()){
      Serial1.read();
    }
    TEST.MatlabTransmit();
    receive = false;
  }

  if (Serial.available() > 8){ // This is for marco.
    if(bitconstruct() == 5000){
    short current1 = bitconstruct();
    short current2 = bitconstruct();
    short current3 = bitconstruct();
    char event = Serial.read();
    
    //TEST.setGoalCurrent(0x01, current1);
    TEST.setGoalCurrent(0x02, current2);
    TEST.setGoalCurrent(0x03, current3);

    receive = true;
    }
  }
  
  
/*
  if(Serial.available() > 6){
    int data[3];
    for (int i = 0; i<3; i++){ //Fills in data array with currents for ID 1, 2 and 3.
      data[i] = bitconstruct();
    }
    
    TEST.setGoalCurrent(1, data[0]); //Set Current for dynamixel 1.
    TEST.setGoalCurrent(2, data[1]); //Set Current for dynamixel 2.
    TEST.setGoalCurrent(3, data[2]); //Set Current for dynamixel 3.

    switch (Serial.read()){ //Switch case for events (Gestures)
      case 1: //Opens Gripper
      TEST.setGoalPosition(5, 3072);
      TEST.setGoalPosition(4, 1024);
        break;
      case 2: //Closes Gripper
      TEST.setGoalPosition(5, 2048);
      TEST.setGoalPosition(4, 2048);
        break;
      case 4:
      //STUFF
        break;
      case 8:
      //STUFF
        break;
      case 16:
      //STUFF
        break;

      default:
        break;
    }

    receive = true;
  }*/
  
}



short bitconstruct(){ //Reads 2 bytes and turn them into an int (Used for the currents.)
  short value = 0;
  for (int i = 0; i < 2; i++){
    value += (Serial.read() << 8*i) & (0x000000FF << 8*i);
  }
  return value;
}
