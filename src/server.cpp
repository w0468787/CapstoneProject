//
// Created by drew on 2023-10-04.
//

#include "../include/server.h"

Server::Server(int port, const char* ip_address) {
    if(port<=0&&ip_address==NULL){

    }else {
        WSADATA wsa_data;
        int i_result;


// Initialize Winsock
        i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (i_result != 0) {
            printf("WSAStartup failed: %d\n", i_result);
            return;
        }

        // Convert portNum to string
        std::stringstream ss;
        ss << port;
        std::string port_string = ss.str();

        struct addrinfo *result = nullptr;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and port to be used by the server
        i_result = getaddrinfo(ip_address, port_string.c_str(), &hints, &result);
        if (i_result != 0) {
            printf("getaddrinfo failed: %d\n", i_result);
            WSACleanup();
            return;
        }
        //Old start function
        // Create a SOCKET for the server to listen for client connections
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        // Starts the listener and displays a message for better UX
        std::cout << "Server Started Waiting For Client Connection:" << std::endl;
        listen(ListenSocket, SOMAXCONN);
    }
}

void Server::client_accept() {
    // Accept a client socket
    ClientSocket = accept(ListenSocket, nullptr, nullptr);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    std::cout << "Connection established with client" << std::endl;
}

void Server::send_message(const std::string& message) {
    // Send a message to the client
    int result = send(ClientSocket, message.c_str(), message.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(ClientSocket);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
}

void Server::disconnect() {
    // Close the client socket and the listener socket
    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();

    std::cout << "Disconnected from client" << std::endl;
}
