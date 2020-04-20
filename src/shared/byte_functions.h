#ifndef BYTE_FUNCTIONS_H
#define BYTE_FUNCTIONS_H

#include <vector>

void addHeader(std::vector<char> &send_buffer);
void intToBytes(const int value, char &buffer_char);
size_t getPayloadSize(std::vector<char> &header_buffer);

//metatropi (serialization) enos int se vector<char> wste na ginetai
//dynati i metafora tou sto socket.
//to buffer pernaei byref kai analoga me tin arxikopoiisi pou tou exei ginei
//diladei ean exei length 1,2 h 4 bytes ginetai i analogi metatropi
void intToBytes(const int value, std::vector<char> &buffer);

//lamvanei ena vector<char> pou periexei arithmo pou egine
//serialize me to intToBytes kai epistrefei ton arxiko arithmo.
//epitrepetai na exei megethos 1,2 h 4 bytes.
int bytesToInt(const std::vector<char> &buffer);

#endif // BYTE_FUNCTIONS_H
