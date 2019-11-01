//
// Created by rns on 10/1/19.
//

#ifndef DYNAMIXEL_P2_DYNAMIXEL_P2_H
#define DYNAMIXEL_P2_DYNAMIXEL_P2_H


class Dynamixel_p2 {
private:
    void CreateHeader(unsigned char *tx_packet){}; // Function to build header (FF FF FD 00)
    void CreateId(unsigned char *tx_packet, unsigned char id){}; // Function to add ID to package
    unsigned char CreateInstruction(unsigned char *tx_packet unsigned char instruction, unsigned char parameters){};
    int CreateLength(unsigned char *tx_packet int parameters_size){};
    //void InsertBytes(unsigned char *tx_packet[], int position){}; // Function to insert an arbitrary amount of bytes at position in array
    void PacketConstructor(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                           unsigned char *params){};
    void TransmitPacket(unsigned char *tx_packet){}; // Function to send a package
    void ReceiveStatusPacket(){}; // Function to read the contents of received packages
public:
    // SETTERS
    void setTorqueEnable(){};
    // GETTERS
    void getTorqueEnable(){};

};
#endif //DYNAMIXEL_P2_DYNAMIXEL_P2_H
