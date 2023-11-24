//
// Created by drew on 2023-11-24.
//

#ifndef CAPSTONEPROJECT_SETUP_CHAT_H
#define CAPSTONEPROJECT_SETUP_CHAT_H

#include <iostream>
#include <string>
#include <exception>
#include "client.h"
#include "server.h"

class SetupChat {
private:
    const int M_ESC = 27;
    const int M_BUFFER_SIZE = 256;
    const int M_ERROR_SIZE = 256;

    const std::string M_IP_ADDRESS = "192.168.192.1";
    const int M_PORT = 12345;

public:
    SetupChat(); // Constructor
    ~SetupChat() = default; // Destructor

    // Getter and Setter for IP_ADDRESS
    const std::string& get_ip_addr() const;

    // Getter and Setter for PORT
    int get_port() const;


    void perform_networking(Server& server, Client& client, bool& serverConnected,
                           bool& clientConnected, bool& server_flag);
    void chat_loop(Server& server, Client& client,
                  bool& server_connected, bool& client_connected, bool& network_flag, bool& server_flag);
};

#endif //CAPSTONEPROJECT_SETUP_CHAT_H
