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
    std::string m_client_ip;
    int m_client_port;

public:
    Client();

    void set_client_ip(const std::string& client_ip);
    std::string get_client_ip() const;

    void set_client_port(int client_port);
    int get_client_port() const;


    bool initialize_client();
    void send_message(const std::string& message);
    void receive_message();
    void disconnect();
    SOCKET get_m_client_socket() const;

    void set_m_client_socket(SOCKET new_client_socket);
};


#endif //CAPSTONEPROJECT_CLIENT_H
