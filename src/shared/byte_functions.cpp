#include "byte_functions.h"
#include "payload_types.h"

//#include <stdexcept>

void addHeader(std::vector<char> &send_buffer)
{
    size_t send_buffer_size = send_buffer.size() - HEADER_SIZE ;

    send_buffer[0] = (send_buffer_size >> 16) & 0xff;
    send_buffer[1] = (send_buffer_size >> 8)  & 0xff;
    send_buffer[2] =  send_buffer_size        & 0xff;
}

size_t getPayloadSize(std::vector<char> &header_buffer)
{
    return
        (((unsigned char)header_buffer[0]) << 16) +
        (((unsigned char)header_buffer[1]) << 8) +
          (unsigned char)header_buffer[2];
}

void intToBytes(const int value, char &buffer_char)
{
    buffer_char = value & 0xff;
}


//metatropi (serialization) enos int se vector<char> wste na ginetai
//dynati i metafora tou sto socket.
//to buffer pernaei byref kai analoga me tin arxikopoiisi pou tou exei ginei
//diladei ean exei length 1,2 h 4 bytes ginetai i analogi metatropi
void intToBytes(const int value, std::vector<char> &buffer)
{
    if(buffer.size() == 4){
        buffer[0] = (value >> 24) & 0xff;
        buffer[1] = (value >> 16) & 0xff;
        buffer[2] = (value >> 8)  & 0xff;
        buffer[3] = value & 0xff;
    }
    else if(buffer.size() == 3){
        buffer[0] = (value >> 16) & 0xff;
        buffer[1] = (value >> 8)  & 0xff;
        buffer[2] = value & 0xff;
    }
    else if(buffer.size() == 2){
        buffer[0] = (value >> 8)  & 0xff;
        buffer[1] = value & 0xff;
    }
    else if(buffer.size() == 1){
        buffer[0] = value & 0xff;
    }
}

//lamvanei ena vector<char> pou periexei arithmo pou egine
//serialize me to intToBytes kai epistrefei ton arxiko arithmo.
//epitrepetai na exei megethos 1,2 h 4 bytes.
int bytesToInt(const std::vector<char> &buffer)
{
    if (buffer.size() == 4){
        return
            (((unsigned char)buffer[0]) << 24) +
            (((unsigned char)buffer[1]) << 16) +
            (((unsigned char)buffer[2]) << 8) +
              (unsigned char)buffer[3];
    }
    if (buffer.size() == 3){
        return
            (((unsigned char)buffer[0]) << 16) +
            (((unsigned char)buffer[1]) << 8) +
              (unsigned char)buffer[2];
    }
    if (buffer.size() == 2){
        return
            (((unsigned char)buffer[0]) << 8) +
              (unsigned char)buffer[1];
    }
    else if (buffer.size() == 1){
        return
              (unsigned char)buffer[0];
    }
    return 0;
}
