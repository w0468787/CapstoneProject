#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <conio.h>
#include "include/client.h"
#include "include/server.h"

using namespace std;

int main(int argc,char *argv[]) {
    Server server;
    Client client;
    bool network_flag=false;
    bool server_flag=false;
    bool client_flag=false;
    const int ESC=27;
    const int BUFFER_SIZE = 256;
    const int ERROR_SIZE = 256;
    std::cout << "Hello! Welcome to SecureNetChat, this application provides real time encryption\nby"
                 " encrypting user input then sending it across OSI 7 layer model.\n and decrypting"
                 " it at the side of the receiver.\n" << std::endl;

    //networking attempts
    const std::string IP_ADDRESS = "192.168.192.1";
    const int PORT = 12345;

    bool serverConnected = false;
    bool clientConnected = false;


    try {
        if (argc >= 2 && std::string(argv[1]) == "-server") {
            server.set_port(PORT);
            server.set_ip_address(IP_ADDRESS);
            server.initialize_server();
            server.start_listening();
            if (server.has_client()) {
                serverConnected = true;
                server_flag=true;
            }
        } else {
            client.set_client_port(PORT);
            client.set_client_ip(IP_ADDRESS);
            client.initialize_client();
            clientConnected = true;
        }

        // Attempt to receive messages from the other end before starting chat
        if (serverConnected) {
            client.set_m_client_socket(server.get_m_client_socket());
            //client.receive_message();
        } else if (clientConnected) {
            // Start a detached thread for receiving messages
            server.set_m_client_socket(client.get_m_client_socket());

        }
    } catch (std::exception &e) {
        // Handle initialization errors here if necessary
    }
    std::cout<<"You have entered the chat:"<<std::endl;
    //chat loop
    try{
        std::string message;
        server.start_thread();
        client.start_thread();
        while (serverConnected || clientConnected) {
            std::getline(std::cin, message);

            if (argc >= 2 && server_flag) {
                server.send_message(message);
                // client.receive_message();
            } else {
                client.send_message(message);
                // server.receive_message();
            }

            // Check for termination condition
            if (message == "q") {
                std::cout << "You hit 'q'. Terminating connection." << std::endl;
                if (argc >= 2 && server_flag) {
                    server.disconnect();
                    serverConnected = false;
                } else {
                    client.disconnect();
                    clientConnected = false;
                }

                serverConnected = false;
                clientConnected = false;
                network_flag = false;
            }
        }

    }catch (exception& e){
        cout<<e.what()<<'\n';
    }

    //Testing




    return 0;
}