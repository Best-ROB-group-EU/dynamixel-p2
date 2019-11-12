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
    void CreateHeader(unsigned char *tx_packet, unsigned char ID); // Function to build header (FF FF FD 00)
    void CreateInstruction(unsigned char *tx_packet, unsigned char instruction);
    unsigned short CreateLength(unsigned char *tx_packet, unsigned short blk_size);
    //void InsertBytes(unsigned char *tx_packet[], int position); // Function to insert an arbitrary amount of bytes at position in array
    void ConstructPacket(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                                       unsigned long params, unsigned char address); // Function that constructs packets, given id, instr, and parameters
    void TransmitPacket(unsigned char *tx_packet); // Function to send a package
    char ChooseParams(unsigned long value, unsigned char address, unsigned char *tx_packet); // Takes a parameter and an address. Figures out how many bytes is needed.
    status_packet_info ReceiveStatusPacket(); // Function to read the contents of received packages


    unsigned short update_crc (unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size); // Calculates CRC
    void CreateCRC(unsigned char *tx_packet, unsigned short blk_size);
    void Create6Params (unsigned long value, unsigned char *package, unsigned char address); // Function designed to split up a 32 Bit value in a 4x8 bit array.
    void Create4Params (unsigned int value, unsigned char *package, unsigned char address); // 16it to 2x8 bit.
    void Create3Params (unsigned char value, unsigned char *package, unsigned char address);
    void Create0Params (unsigned char value, unsigned char *package, unsigned char address); // The case for non read/write functions.
public:
    // CONSTRUCTORS
    Dynamixel_p2(int flow_control_pin);
    // UTILITY
    void begin(long baud_rate);
    // SETTERS
    void setTorqueEnable(unsigned char id, unsigned char value);
    void setLedStatus(unsigned char id, unsigned char value);
    void setStatusReturnLevel(unsigned char id, unsigned char value);
    void setVelocityGainI(unsigned char id, unsigned int value);
    void setVelocityGainP(unsigned char id, unsigned int value);
    void setVelocityGainD(unsigned char id, unsigned int value);
    void setPositionGainD(unsigned char id, unsigned int value);
    void setPositionGainI(unsigned char id, unsigned int value);
    void setPositionGainP(unsigned char id, unsigned int value);
    void setFF2Gain(unsigned char id, unsigned int value);
    void setFF1Gain(unsigned char id, unsigned int value);
    void setBusWatchdog(unsigned char id, unsigned char value);
    void setGoalPwm(unsigned char id, unsigned int value);
    void setGoalCurrent(unsigned char id, unsigned int value);
    void setGoalVelocity(unsigned char id, unsigned long value);
    void setProfileAcceleration(unsigned char id, unsigned long value);
    void setProfileVelocity(unsigned char id, unsigned long value);
    void setGoalPosition(unsigned char id, unsigned long value);

    void setAddress(unsigned char id, unsigned int address, unsigned long value);

    // GETTERS
    unsigned char getTorqueEnable(unsigned char id, unsigned int bytes);
    unsigned char getLedStatus(unsigned char id, unsigned int bytes);
    unsigned char getStatusReturnLevel(unsigned char id, unsigned int bytes);
    unsigned char getRegisteredInstruction(unsigned char id, unsigned int bytes);
    unsigned char getHardwareError(unsigned char id, unsigned int bytes);
    unsigned int getVelocityGainI(unsigned char id, unsigned int bytes);
    unsigned int getVelocityGainP(unsigned char id, unsigned int bytes);
    unsigned int getVelocityGainD(unsigned char id, unsigned int bytes);
    unsigned int getPositionGainD(unsigned char id, unsigned int bytes);
    unsigned int getPositionGainI(unsigned char id, unsigned int bytes);
    unsigned int getPositionGainP(unsigned char id, unsigned int bytes);
    unsigned int getFF2Gain(unsigned char id, unsigned int bytes);
    unsigned int getFF1Gain(unsigned char id, unsigned int bytes);
    unsigned char getBusWatchdog(unsigned char id, unsigned int bytes);
    unsigned int getGoalPwm(unsigned char id, unsigned int bytes);
    unsigned int getGoalCurrent(unsigned char id, unsigned int bytes);
    unsigned long getGoalVelocity(unsigned char id, unsigned int bytes);
    unsigned long getProfileAcceleration(unsigned char id, unsigned int bytes);
    unsigned long getProfileVelocity(unsigned char id, unsigned int bytes);
    unsigned long getGoalPosition(unsigned char id, unsigned int bytes);
    unsigned char getMoving(unsigned char id, unsigned int bytes);
    unsigned char getMovingDetailed(unsigned char id, unsigned int bytes);
    unsigned int getPresentPwm(unsigned char id, unsigned int bytes);
    unsigned int getPresentCurrent(unsigned char id, unsigned int bytes);
    unsigned long getPresentVelocity(unsigned char id, unsigned int bytes);
    unsigned long getPresentPosition(unsigned char id, unsigned int bytes);
    unsigned long getVelocityTrajectory(unsigned char id, unsigned int bytes);
    unsigned long getPositionTrajectory(unsigned char id, unsigned int bytes);
    unsigned int getPresentInputVoltage(unsigned char id, unsigned int bytes);
    unsigned char getTemperature(unsigned char id, unsigned int bytes);

    // PING
    void PingServo(unsigned char ID);

};
#endif //DYNAMIXEL_P2_DYNAMIXEL_P2_H
