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
                server.set_m_client_socket(client.get_m_client_socket());
                //server.receive_message();
            }
        } catch (std::exception &e) {
            // Handle initialization errors here if necessary
        }
    std::cout<<"you got free of the server client loop headed to chat"<<std::endl;
    //chat loop
    try{
        std::string message;

        while (serverConnected||clientConnected) {
            std::getline(std::cin, message);

            if (message == "i" || message == "I") {
                std::cout << "Insertion Mode" << std::endl;
                std::getline(std::cin, message); // Get the message from the user in insertion mode

                if (argc >= 2 && server_flag) {
                    server.send_message(message);
                    client.receive_message();
                } else {
                    client.send_message(message);
                    server.receive_message();
                }
            } else if (message == "q") {
                std::cout << "You hit escape" << std::endl;
                if (argc >= 2 && server_flag) {
                    server.disconnect();
                    serverConnected=false;
                } else {
                    client.disconnect();
                    clientConnected=false;

                }
                serverConnected=false;
                clientConnected=false;
                network_flag = false;
            } else {
                std::cout << "Invalid input. Please enter 'i' for Insertion Mode or 'ESC' to quit." << std::endl;
            }
        }

    }catch (exception& e){
        cout<<e.what()<<'\n';
    }
    //Encrypt trial
    char trial_string[] = "hello world";
    char buffer[BUFFER_SIZE]; // Define buffer with a size of 256 (adjust according to your needs)
    char curr;
    int ceaser_key = 5;


    // Copy trial_string to buffer
    strncpy(buffer, trial_string, BUFFER_SIZE);
    cout << "Normal: " << buffer << std::endl;
   
    for (int i = 0; buffer[i] != '\0'; i++) {
        curr = buffer[i];
        // Perform operations on buffer[i] here
        if (curr >= 'a' && curr <= 'z') {
            curr = curr + ceaser_key;
            if (curr > 'z') {
                curr = curr - 'z' + 'a' + 1;
            }
        }
        buffer[i] = curr;
    }
    cout << "Modified: " << buffer<<std::endl;

    // Decrypt Trial
    for (int i = 0; buffer[i] != '\0'; ++i) {
        curr = buffer[i];
        if (curr >= 'a' && curr <= 'z') {
            curr = curr - ceaser_key;
            if (curr < 'a') {
                curr = curr + 'z' - 'a' -1;
            }
        }
        buffer[i] = curr;
    }

    cout<<"decrypted: "<<buffer;

    //Testing




    return 0;
}
