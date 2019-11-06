// Created by 19gr362 Aalborg University, Robotics third semester.
#ifndef DYNAMIXEL_P2_DYNAMIXEL_P2_H
#define DYNAMIXEL_P2_DYNAMIXEL_P2_H

#define WRITE 0x03
#define READ 0x02
#define PING 0x01

#include <Arduino.h>

#include <iostream>
#include <iomanip>
// Contains adresses of the RAM control table
unsigned char addresses[27] = {64,65,68,69,70,76,78,80,82,84,88,90,98,100,102,104,108,112,116,120,122,126,128,132,136,140,144,146};
// Contains the expected amount of Bytes to the addresses.
unsigned char prefBytes[27] = {1,1,1,1,2,2,2,2,2,2,2,1,2,2,4,4,4,4,2,1,1,2,2,4,4,4,4,2,1};
// Holds instructions
unsigned char instructions[13] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x10, 0x55, 0x82, 0x83, 0x92, 0x93};
// Holds the beginning of parameters for those instructions.
unsigned char firstParameter[13] = {0, 10, 10, 10, 0, 8, 0, 0};

using namespace std;

class Dynamixel_p2 {
private:
    // ATTRIBUTES
    Stream *_serialport;
    int _flow_control_pin = 13;
    struct status_packet_info{
        unsigned char id;
        unsigned char error;
        unsigned char parameters[4];
    };
    // METHODS
    unsigned char Dynamixel_p2::CreateblkSize (unsigned char instruction, unsigned char address){};
    void CreateHeader(unsigned char *tx_packet){}; // Function to build header (FF FF FD 00)
    void CreateId(unsigned char *tx_packet, unsigned char id){}; // Function to add ID to package
    unsigned char CreateInstruction(unsigned char *tx_packet unsigned char instruction, unsigned char parameters){};
    unsigned short CreateLength(unsigned char *tx_packet int parameters_size){};
    //void InsertBytes(unsigned char *tx_packet[], int position){}; // Function to insert an arbitrary amount of bytes at position in array
    void ConstructPacket(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                         unsigned long long params, unsigned char address){}; // Function that constructs packets, given id, instr, and parameters
    void TransmitPacket(unsigned char *tx_packet){}; // Function to send a package
    void ChooseParams(unsigned long long value, unsigned char address, unsigned char *tx_packet){}; // Takes a parameter and an address. Figures out how many bytes is needed.
    status_packet_info ReceiveStatusPacket(){}; // Function to read the contents of received packages

    unsigned short update_crc (unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size){}; // Calculates CRC
    unsigned short data_blk_size(unsigned char *packet); // Calculates the block size for use in CRC Calculation
    void Create4Params (unsigned long value, unsigned char *package, unsigned char address){}; // Function designed to split up a 32 Bit value in a 4x8 bit array.
    void Create2Params (unsigned long value, unsigned char *package, unsigned char address){}; // 16it to 2x8 bit.
    void Create1Params (unsigned long value, unsigned char *package, unsigned char address){};
public:
    // CONSTRUCTORS
    Dynamixel_p2(int flow_control_pin = 13){};
    // UTILITY
    void begin(long baud_rate = 57600){};
    // SETTERS
    void setTorqueEnable(){};
    // GETTERS
    void getTorqueEnable(){};
};
#endif //DYNAMIXEL_P2_DYNAMIXEL_P2_H
