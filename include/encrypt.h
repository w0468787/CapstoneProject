//
// Created by drew on 2023-10-16.
//

#ifndef CAPSTONEPROJECT_ENCRYPT_H
#define CAPSTONEPROJECT_ENCRYPT_H
#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <conio.h>


class Encrypt {
public:
Encrypt();
std::string encrypt_message(const std::string& message);
std::string decrypt_message(const std::string& message);
    static const int M_BUFFER_SIZE = 256;
    static const int M_ERROR_SIZE = 256;
private:
    char m_buffer[M_BUFFER_SIZE]; // Define buffer with a size of 256 (adjust according to your needs)
    int m_ceaser_key=5;

};


#endif //CAPSTONEPROJECT_ENCRYPT_H
