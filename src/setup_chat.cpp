#include "../include/setup_chat.h"
using namespace std;

SetupChat::SetupChat() {
    // Constructor implementation, if needed
}

// Getter and Setter for IP_ADDRESS
const std::string& SetupChat::get_ip_addr() const {
    return M_IP_ADDRESS;
}

// Getter and Setter for PORT
int SetupChat::get_port() const {
    return M_PORT;
}

void SetupChat::perform_networking(Server& server, Client& client, bool& serverConnected,
                                   bool& clientConnected, bool& server_flag) {
    try {
        if (server_flag) {
            server.set_port(M_PORT);
            server.set_ip_address(M_IP_ADDRESS);
            server.initialize_server();
            server.start_listening();
            if (server.has_client()) {
                serverConnected = true;
            }
        } else {
            client.set_client_port(M_PORT);
            client.set_client_ip(M_IP_ADDRESS);
            client.initialize_client();
            clientConnected = true;
        }

        // Attempt to receive messages from the other end before starting chat
        if (serverConnected) {
            client.set_m_client_socket(server.get_m_client_socket());
        } else if (clientConnected) {
            server.set_m_client_socket(client.get_m_client_socket());
        }
    } catch (std::exception& e) {
        // Handle initialization errors here if necessary
    }
}

void SetupChat::chat_loop(Server& server, Client& client, bool& server_connected,
                          bool& client_connected, bool& network_flag, bool& server_flag) {
    std::cout << "You have entered the chat:" << std::endl;

    if(server_connected || client_connected) {
        try {
            std::string message;
            server.start_thread();
            client.start_thread();

            while (server_connected || client_connected) {
                std::getline(std::cin, message);

                if (server_flag) {
                    server.send_message(message);
                } else {
                    client.send_message(message);
                }

                // Check for termination condition
                if (message == "q") {
                    std::cout << "You hit 'q'. Terminating connection." << std::endl;
                    if (server_flag) {
                        server.disconnect();
                        server_connected = false;
                    } else {
                        client.disconnect();
                        client_connected = false;
                    }

                    server_connected = false;
                    client_connected = false;
                    network_flag = false;
                }
            }

        } catch (exception &e) {
            cout << e.what() << '\n';
        }
    }
}
