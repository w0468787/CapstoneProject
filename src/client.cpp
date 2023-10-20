//
// Created by drew on 2023-10-04.
//

#include "../include/client.h"

Client::Client(const std::string& server_ip, int server_port) {
    if(server_port<=0&& server_ip==""){

    }else {
        WSADATA wsa_data;
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
            std::cerr << "Failed to initialize Winsock" << std::endl;
            return;
        }

        m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_client_socket == INVALID_SOCKET) {
            std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(server_port);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str()); // Use inet_addr instead of inet_pton

        if (connect(m_client_socket, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) ==
            SOCKET_ERROR) {
            std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
            closesocket(m_client_socket);
            WSACleanup();
            return;
        }

        std::cout << "Connected to server" << std::endl;
    }
}

void Client::send_message(std::string& message) {
    int result = send(m_client_socket, message.c_str(), message.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
        closesocket(m_client_socket);
        WSACleanup();
        return;
    }
}

void Client::disconnect() {
    closesocket(m_client_socket);
    WSACleanup();
    std::cout << "Disconnected" << std::endl;
}

