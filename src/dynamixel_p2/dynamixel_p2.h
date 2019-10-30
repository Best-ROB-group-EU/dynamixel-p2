//
// Created by rns on 10/1/19.
//

#ifndef DYNAMIXEL_P2_DYNAMIXEL_P2_H
#define DYNAMIXEL_P2_DYNAMIXEL_P2_H


class Dynamixel_p2 {
private:
    void createHeader(){}; // Function to build header (FF FF FD 00)
    void insertBytes(){}; // Function to insert an arbitrary amount of bytes at position in array
    void transmitPackage(){}; // Function to send a package
    void receiveStatusPackage(){}; // Function to read the contents of received packages
public:
    void ping(){};
    // SETTERS
    void setTorqueEnable(){};
    // GETTERS
    void getTorqueEnable(){};

};


#endif //DYNAMIXEL_P2_DYNAMIXEL_P2_H
