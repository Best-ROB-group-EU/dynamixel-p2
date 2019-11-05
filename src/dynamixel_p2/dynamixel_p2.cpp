// Created by 19gr362 Aalborg University, Robotics third semester.
#include "dynamixel_p2.h"

// CONSTRUCTOR
Dynamixel_p2::Dynamixel_p2(int flow_control_pin = 13)
{
    _flow_control_pin = flow_control_pin;
    pinMode(_flow_control_pin, OUTPUT);
}

// PUBLIC METHODS
// Following method written by TODO: Insert original author
void Dynamixel_p2::begin(long baud_rate = 57600)
{
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__) || defined(__AVR_ATmega2560__)
    Serial1.begin(baud_rate);  // Set up Serial for Leonardo and Mega
    _serialport = &Serial1;
#else
    Serial.begin(baud_rate);   // Set up Serial for all others (Uno, etc)
    _serialport = &Serial;
#endif
}

// PRIVATE METHODS

unsigned char Dynamixel_p2::CreateblkSize (unsigned char instruction, unsigned char address){ // TODO Convert if else structure to switch for better processing
    unsigned char blkSize = 0;
    if (instruction == 0x01 || 0x05 || 0x08){ // If it's a ping, action or Reboot
        blkSize = 10; // This is always the case for pings, action and Reboot
    }

    if (instruction == 0x02){ // If it's a read
        blkSize = 14; // Always the case for a read.
    }

    if (instruction == 0x03 || 0x04) { // If it's a write or reg write
        blkSize = 10 + prefBytes[address] + 2; // 10 Always present bytes plus x prefBytes plus 2 CRC. Pref bytes for torque_enable is 1.
    }

    if (instruction == 0x06){ // Factory reset
        blkSize = 11;
    }


    if (instruction == 0x10){ // Clear
        blkSize = 15;
    }

    if (instruction == 0x55){ // Status(return)

    }

    if (instruction == 0x82){ // Sync read

    }

    if (instruction == 0x83){ // Sync write

    }

    if (instruction == 0x92){ // Bulk read

    }

    if (instruction == 0x93){ // Bulk write

    }
    return blkSize;
};

void Dynamixel_p2::CreateHeader(unsigned char *tx_packet)
{
    tx_packet[0] = 0xFF;
    tx_packet[1] = 0xFF;
    tx_packet[2] = 0xFD;
    tx_packet[3] = 0x00;
}

void Dynamixel_p2::CreateId(unsigned char *tx_packet, unsigned char id)
{
    tx_packet[4] = id;
    return
}


void Dynamixel_p2::CreateInstruction(unsigned char *tx_packet, unsigned char instruction, unsigned char *parameters)
{
    tx_packet[7] = instruction;

    for (int i = 0; i < sizeof(parameters) ; ++i)
    {
        tx_packet[8+i] = parameters[i];
    }
}

int Dynamixel_p2::CreateLength(unsigned char *tx_packet, unsigned char parameters_size) // Todo, once we know the instruction we know if we need address. If we do we can look up how many bytes is needed.
{
    int packet_length = parameters_size + 3;
    unsigned char length1 = packet_length & 0xFF;
    unsigned char length2 = 0x00;
    if (packet_length > 0xFF)
    {
        length2 = (packet_length >> 8) & 0xFF;
    }
    tx_packet[5] = length1;
    tx_packet[6] = length2;
    return packet_length;
}

void Dynamixel_p2::ConstructPacket(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                                     unsigned char *params)
{
    CreateHeader(tx_packet);
    CreateId(tx_packet, device_id);
    CreateInstruction(tx_packet, instruction, params);
    int packet_length = CreateLength(tx_packet, sizeof(params));
    // TODO: Add CRC
}

void Dynamixel_p2::TransmitPacket(unsigned char *tx_packet)
{
    digitalWrite(_flow_control_pin, HIGH);
    int bytes_in_packet = (tx_packet[6] << 8) + tx_packet[5] + 7;

    for (int i = 0; i < bytes_in_packet; i++)
    {
        _serialport->write(tx_packet[i]);
    }
    _serialport->flush();
    digitalWrite(_flow_control_pin, LOW);
}

unsigned short Dynamixel_p2::update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
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

unsigned short Dynamixel_p2::data_blk_size(unsigned char *packet) { //Not finished we need length of 1 and 2. In case of long packets
    // There is no point in considering Length 2, since no RAM addresses are above 255.
    unsigned short data_blk_size = packet[5] + 5;
    cout << "Length1: " << int (data_blk_size) << endl;
    return data_blk_size;
}

void Dynamixel_p2::Create4Params (unsigned long long value, unsigned char *package){ // Function to split 32 bit value into 4x8 bit array.
    package[4];
    for (int i = 0; i<4; i++){ // Repeats 4 times.
        package[i] = value & 0x000000FF; // Runs bitmask over 32 bit value to 8 bit.
        value = value >> 8; //Bitshift value by 8 bits to the right.
    }
}

void Dynamixel_p2::Create2Params (unsigned long value, unsigned char *package){ // Function split 16 bit value into 2x8 bit array.
    package[2];
    for (int i = 0; i < 2; i++){ // Repeats twice.
        package[i] = value & 0x00FF; // Runs bitmask over 16bit value to 8bit.
        value = value >> 8; // Bitshifts value by 8 bits to the right.
    }
}

void Dynamixel_p2::Create1Params (unsigned long value, unsigned char *package){ // Function split 8 bit value into 1x8 bit array.
        package[1] = value & 0x00FF; // Runs bitmask over 8bit value to 8bit.
}
