// Created by 19gr362 Aalborg University, Robotics third semester.
#ifndef DYNAMIXEL_P2_DYNAMIXEL_P2_H
#define DYNAMIXEL_P2_DYNAMIXEL_P2_H

#define WRITE 0x03
#define READ 0x02
#define PING 0x01

#include <Arduino.h>


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
    void CreateHeader(unsigned char *tx_packet); // Function to build header (FF FF FD 00)
    void CreateId(unsigned char *tx_packet, unsigned char id); // Function to add ID to package
    void CreateInstruction(unsigned char *tx_packet, unsigned char instruction);
    void CreateLength(unsigned char *tx_packet, unsigned short blk_size);
    //void InsertBytes(unsigned char *tx_packet[], int position); // Function to insert an arbitrary amount of bytes at position in array
    void ConstructPacket(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                                       unsigned long params, unsigned char address); // Function that constructs packets, given id, instr, and parameters
    void TransmitPacket(unsigned char *tx_packet); // Function to send a package
    unsigned char ChooseParams(unsigned long value, unsigned char address, unsigned char *tx_packet); // Takes a parameter and an address. Figures out how many bytes is needed.
    status_packet_info ReceiveStatusPacket(); // Function to read the contents of received packages


    unsigned short update_crc (unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size); // Calculates CRC
    void CreateCRC(unsigned char *tx_packet, unsigned short blk_size);
    void Create4Params (unsigned long value, unsigned char *package, unsigned char address); // Function designed to split up a 32 Bit value in a 4x8 bit array.
    void Create2Params (unsigned int value, unsigned char *package, unsigned char address); // 16it to 2x8 bit.
    void Create1Params (unsigned char value, unsigned char *package, unsigned char address);
public:
    // CONSTRUCTORS
    Dynamixel_p2(int flow_control_pin);
    // UTILITY
    void begin(long baud_rate);
    // SETTERS
    void setTorqueEnable();
    void setGoalPosition(unsigned char ID, unsigned long value);
    // GETTERS
    void getTorqueEnable();

};
#endif //DYNAMIXEL_P2_DYNAMIXEL_P2_H
