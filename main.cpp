#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <conio.h>
#include "include/client.h"
#include "include/server.h"
#include "include/setup_chat.h"

using namespace std;

int main(int argc, char *argv[]) {
    Server server;
    Client client;
    SetupChat setup_chat;
    bool network_flag = false;
    bool server_flag = false;
    bool client_flag = false;
    const int ESC = 27;
    const int BUFFER_SIZE = 256;
    const int ERROR_SIZE = 256;
    std::cout << "Hello! Welcome to SecureNetChat, this application provides real time encryption\nby"
                 " encrypting user input then sending it across OSI 7 layer model.\n and decrypting"
                 " it at the side of the receiver.\n" << std::endl;

    const std::string IP_ADDRESS = "192.168.192.1";
    const int PORT = 12345;
    bool server_connected = false;
    bool client_connected = false;

    try {
        if (argc >= 2 && std::string(argv[1]) == "-server") {
            server.set_port(PORT);
            server.set_ip_address(IP_ADDRESS);
            server.initialize_server();
            server.start_listening();
            if (server.has_client()) {
                server_connected = true;
                server_flag = true;
            }
        } else {
            client.set_client_port(PORT);
            client.set_client_ip(IP_ADDRESS);
            client.initialize_client();
            client_connected = true;
        }
        // Attempt to receive messages from the other end before starting chat
        if (server_connected) {
            client.set_m_client_socket(server.get_m_client_socket());
            //client.receive_message();
        } else if (client_connected) {
            // Start a detached thread for receiving messages
            server.set_m_client_socket(client.get_m_client_socket());

        }
    } catch (std::exception &e) {
        // Handle initialization errors here if necessary
    }
    setup_chat.chat_loop(server, client, server_connected, client_connected, network_flag, server_flag);

    return 0;
}

//Testing
#if TESTING
    int main(int argc, char* argv[]) {
        Server server;
        Client client;
        bool network_flag = false;
        bool serverConnected = false;
        bool clientConnected = false;
        bool server_flag = false;

        std::cout << "Hello! Welcome to SecureNetChat, this application provides real time encryption\n"
                     "by encrypting user input then sending it across OSI 7 layer model.\n and decrypting"
                     " it at the side of the receiver.\n"
                  << std::endl;
        SetupChat setup_chat;
        setup_chat.perform_networking(server, client, serverConnected,
                                      clientConnected, server_flag);

        setup_chat.chat_loop(server, client, serverConnected, clientConnected,
                             network_flag, server_flag);

        // Testing

        return 0;
    }
#endif

