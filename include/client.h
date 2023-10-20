//
// Created by drew on 2023-10-04.
//

#ifndef CAPSTONEPROJECT_CLIENT_H
#define CAPSTONEPROJECT_CLIENT_H


#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>

class Client {
private:
    SOCKET m_client_socket;

public:
    Client(const std::string& server_ip="", int server_port=0);
    void send_message(std::string& message);
    void disconnect();
};


#endif //CAPSTONEPROJECT_CLIENT_H
