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

    SOCKET m_listen_socket;
    SOCKET m_client_socket;
    int m_port;
    std::string m_ip_address;
    bool m_has_client;

public:

    Server();
    bool initialize_server();
    bool has_client();

    void set_port(int new_port);
    int get_port() const;

    void set_ip_address(std::string new_ip_address);
    const std::string& get_ip_address() const;

    void client_accept();

    void send_message(const std::string& message);
    void receive_message();

    void disconnect();
    void start_listening();
    SOCKET get_m_client_socket() const;

    void set_m_client_socket(SOCKET new_client_socket);
};



#endif //CAPSTONEPROJECT_SERVER_H
