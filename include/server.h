//
// Created by drew on 2023-10-04.
//

#ifndef CAPSTONEPROJECT_SERVER_H
#define CAPSTONEPROJECT_SERVER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <sstream>



class Server {
private:
    SOCKET ListenSocket;
    SOCKET ClientSocket;

public:
    Server(int port = 0, const char* ip_address = nullptr);
    void client_accept();
    void send_message(const std::string& message);
    void disconnect();
};


#endif //CAPSTONEPROJECT_SERVER_H
