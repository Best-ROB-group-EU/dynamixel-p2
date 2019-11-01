//
// Created by rns on 10/1/19.
//

#include "dynamixel_p2.h"

// PRIVATE METHODS

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

int Dynamixel_p2::CreateLength(unsigned char *tx_packet, unsigned char parameters_size)
{
    unsigned char length1, length2 = 0x00;
    int packet_length = parameters_size + 10;
    if (packet_length > 0xFF)
    {
        length1 = packet_length & 0xFF;
        length2 = (packet_length >> 8) & 0xFF;
    }
    tx_packet[5] = length1;
    tx_packet[6] = length2;
    return packet_length;
}

void Dynamixel_p2::PacketConstructor(unsigned char *tx_packet, unsigned char device_id, unsigned char instruction,
                                     unsigned char *params)
{
    CreateHeader(tx_packet);
    CreateId(tx_packet, device_id);
    CreateInstruction(tx_packet, instruction, params);
    int packet_length = CreateLength(tx_packet, sizeof(params));

}

void Dynamixel_p2::TransmitPacket(unsigned char *tx_packet)
{
    for (int i = 0; i < ((tx_packet[6] << 8) + tx_packet[5]); ++i) // TODO: Move length calculation elsewhere
    {

    }
}
