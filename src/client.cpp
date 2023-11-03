//
// Created by drew on 2023-10-04.
//

#include "../include/client.h"

Client::Client():m_client_port(0),m_client_ip(""),m_client_socket(INVALID_SOCKET){
}

bool Client::initialize_client() {
    if (m_client_port <= 0 || m_client_ip.empty()) {
        // Handle invalid port and IP address (throw exception, print error, etc.)
        // For now, just return false indicating initialization failure
        return false;
    } else {
        WSADATA wsa_data;
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
            std::cerr << "Failed to initialize Winsock" << std::endl;
            return false;
        }

        m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_client_socket == INVALID_SOCKET) {
            std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return false;
        }

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(m_client_port);
        server_address.sin_addr.s_addr = inet_addr(m_client_ip.c_str()); // Use inet_addr instead of inet_pton

        if (connect(m_client_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) ==
            SOCKET_ERROR) {
            std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
            closesocket(m_client_socket);
            WSACleanup();
            return false;
        }

        std::cout << "Connected to server" << std::endl;
        return true;
    }
}

void Client::set_client_ip(const std::string &client_ip) {
    m_client_ip=client_ip;
}

std::string Client::get_client_ip() const {
    return m_client_ip;
}

void Client::set_client_port(int client_port) {
    m_client_port=client_port;
}
int Client::get_client_port() const {
    return m_client_port;
}

void Client::send_message(const std::string& message) {
    int result = send(m_client_socket, message.c_str(), message.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
        closesocket(m_client_socket);
        WSACleanup();
        return;
    }
}
void Client::receive_message() {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(m_client_socket, buffer, BUFFER_SIZE, 0);

    if (bytes_received == SOCKET_ERROR) {
        std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
    } else if (bytes_received == 0) {
        std::cout << "Connection closed by client." << std::endl;
        // Handle the case where the connection is closed by the server
    } else {
        buffer[bytes_received] = '\0';
        std::cout << "Received data from client: " << buffer << std::endl;
    }
}

void Client::disconnect() {
    closesocket(m_client_socket);
    WSACleanup();
    std::cout << "Disconnected" << std::endl;
}

SOCKET Client::get_m_client_socket() const {
    return m_client_socket;
}

void Client::set_m_client_socket(SOCKET new_client_socket) {
    m_client_socket = new_client_socket;
}

