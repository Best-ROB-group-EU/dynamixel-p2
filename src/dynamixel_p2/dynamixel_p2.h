//
// Created by rns on 10/1/19.
//
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
unsigned short update_crc (unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);
unsigned short data_blk_size(unsigned char *packet);
void unint16to8 (unsigned long value, unsigned char *package, unsigned char startParameters); // Function designed to split up a 32 Bit value in a 4x8 bit array.
void unint16to8 (unsigned long value, unsigned char *package, unsigned char startParameters); // 16it to 2x8 bit.
void initSettings();

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

void initSettings (){ //Initializes preferred settings for all Dynamixel servos.
    // Initial conditions should be Gain 100, Torque on, Position 0 for all servos.
    unsigned char pkgGain[14] = {0xFF,0xFF,0xFD,0x00,0xFE,0x07,0x00,0x03,0x54,0x00,0x00,0x64, 0x3A, 0x3E}; //Writes 100 (0x0064) to gain adress,
    unsigned char pkgTorque[13] = {0xFF,0xFF,0xFD,0x00,0xFE,0x06,0x00,0x03,0x40,0x00,0x01, 0x2B, 0x96};
    unsigned char pkgPosition[16] = {0xFF,0xFF,0xFD,0x00,0xFE,0x09,0x00,0x03,0x74,0x00,0x00, 0x00, 0x00, 0x00, 0x2E, 0xA5};


};

/*
// Package is always [OxFF, 0xFF, 0xFD, 0x00, ID, LENGTH_1, LENGTH_2, INSTRUCTION, LOW BYTE ADDRESS, HIGH BYTE ADDRESS, Parameters, CRC_L, CRC_H]
    unsigned char package[16] = {0xFF, 0xFF, 0xFD, 0x00, 0x02, 0x09, 0x00, 0x03, 0x41, 0x00, 0x00, 0x00, 0x00, 0x01, 0xEE, 0x31};
// Package sends to ID 2, Address 65 (LED On MX-64) And sends 0x00000001 In parameter which is 1. So LED should turn on, it does not.
    unsigned short cal_crc = update_crc(0, package, data_blk_size(package));
    unsigned char CRC_L = (cal_crc & 0x00FF);
    unsigned char CRC_H = (cal_crc >> 8) & 0x00FF;

    cout << "CRC: " << hex << int(cal_crc) << endl;
    cout << "CRC_L: " << hex << int (CRC_L) << endl;
    cout << "CRC_H: " << hex << int (CRC_H) << endl;
*/



unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
    unsigned short i, j;
    unsigned short crc_table[256] = {
            0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
            0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
            0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
            0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
            0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
            0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
            0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
            0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
            0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
            0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
            0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
            0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
            0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
            0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
            0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
            0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
            0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
            0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
            0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
            0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
            0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
            0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
            0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
            0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
            0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
            0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
            0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
            0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
            0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
            0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
            0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
            0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for(j = 0; j < data_blk_size; j++)
    {
        i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    return crc_accum;
}

unsigned short data_blk_size(unsigned char *packet) { //Not finished we need length of 1 and 2. In case of long packets
    // There is no point in considering Length 2, since no RAM addresses are above 255.
    unsigned short data_blk_size = packet[5] + 5;
    cout << "Length1: " << int (data_blk_size) << endl;
    return data_blk_size;
}


void uint32to8 (unsigned long long value, unsigned char *package, unsigned char startParameters){ // Function to split 32 bit value into 4x8 bit array.
    for (int i = 0; i<4; i++){ // Repeats 4 times.
        package[i+startParameters] = value & 0x000000FF; // Runs bitmask over 32 bit value to 8 bit.
        value = value >> 8; //Bitshift value by 8 bits to the right.
        cout << package << endl; //  TEST PRINT REMOVE LATER
    }
}

void unint16to8 (unsigned long value, unsigned char *package, unsigned char startParameters){ // Function split 16 bit value into 2x8 bit array.
    for (int i = 0; i < 2; i++){ // Repeats twice.
        package[i+startParameters] = value & 0x00FF; // Runs bitmask over 16bit value to 8bit.
        value = value >> 8; // Bitshifts value by 8 bits to the right.
        cout << package[i] << endl; // TEST PRINT REMOVE LATER
    }

}
