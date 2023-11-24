//
// Created by drew on 2023-10-04.
//

#include "../include/server.h"

Server::Server(): m_port(0), m_ip_address(""), m_listen_socket(INVALID_SOCKET) {

}


// Setter for m_port
void Server::set_port(int new_port) {
    if (new_port <= 0) {
        // Handle invalid m_port value (throw exception, print error, etc.)
        // For now, just set m_port to 0 (invalid m_port)
        m_port = 0;
    } else {
        this->m_port = new_port;
    }
}

// Getter for m_port
int Server::get_port() const {
    return m_port;
}

// Setter for m_ip_address
void Server::set_ip_address(std::string new_ip_address) {
    m_ip_address =new_ip_address;
}

// Getter for m_ip_address
const std::string &Server::get_ip_address() const {
    return m_ip_address;
}
bool Server::initialize_server() {
    if (m_port <= 0 && m_ip_address == "") {
        // Handle invalid m_port and IP address (throw exception, print error, etc.)
        // For now, just return false indicating initialization failure
        return false;
    } else {
        WSADATA wsa_data;
        int i_result;

        // Initialize Winsock
        i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (i_result != 0) {
            printf("WSAStartup failed: %d\n", i_result);
            return false;
        }

        // Convert portNum to string
        std::stringstream ss;
        ss << m_port;
        std::string port_string = ss.str();

        struct addrinfo *result = nullptr;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and m_port to be used by the server
        i_result = getaddrinfo(m_ip_address.c_str(), port_string.c_str(), &hints, &result);
        if (i_result != 0) {
            printf("getaddrinfo failed: %d\n", i_result);
            WSACleanup();
            return false;
        }


        // Create a SOCKET for the server to listen for client connections
        m_listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (m_listen_socket == INVALID_SOCKET) {
            printf("socket failed: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return false;
        }

        // Bind the socket to the local address and port
        i_result = bind(m_listen_socket, result->ai_addr, static_cast<int>(result->ai_addrlen));
        if (i_result == SOCKET_ERROR) {
            printf("bind failed: %d\n", WSAGetLastError());
            closesocket(m_listen_socket);
            freeaddrinfo(result);
            WSACleanup();
            return false;
        }

        // Free the addrinfo structure
        freeaddrinfo(result);

        return true;
    }
}

void Server::start_listening() {
    // Starts the listener and displays a message for better UX
    std::cout << "Server Started Waiting For Client Connection:" << std::endl;
    listen(m_listen_socket, SOMAXCONN);

    client_accept();

}

void Server::client_accept() {
    // Accept client connections in a loop for use in program
    while (true) {
        m_client_socket = accept(m_listen_socket, nullptr, nullptr);
        if (m_client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            closesocket(m_listen_socket);
            WSACleanup();
            return;
        }
        std::cout << "Connection established with client" << std::endl;
        m_has_client=true;
        break;
    }
}


void Server::send_message(const std::string& message) {
    // Check if the message is empty
    if (message.empty()) {
        std::cerr << "Empty message provided for sending." << std::endl;
        return;
    }

    // Encrypt the message
    std::string encrypted_message = m_encrypt_tool.encrypt_message(message);

    // Send the encrypted message to the client
    int result = send(m_client_socket, encrypted_message.c_str(), encrypted_message.size(), 0);

    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(m_client_socket);
        closesocket(m_listen_socket);
        WSACleanup();
    } else {
        std::cout << "Message sent successfully: " << std::endl;
    }
}

void Server::start_thread() {
    // Start a detached thread for receiving messages
    m_receiving = true;
    m_receive_thread = std::thread(&Server::start_receiving, this);
    m_receive_thread.detach();
}

void Server::start_receiving() {
    while (m_receiving) {
        receive_message();
        // Add a delay or other logic here if needed
    }
}

void Server::receive_message() {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(m_client_socket, buffer, BUFFER_SIZE, 0);

    if (bytes_received == SOCKET_ERROR) {
        throw std::runtime_error("Corresponding app closed");
    } else if (bytes_received == 0) {
        std::cout << "Connection closed by server." << std::endl;
        // Handle the case where the connection is closed by the client
    } else {
        buffer[bytes_received] = '\0';
        std::string to_decrypt(buffer);
        std::string decrypted=m_encrypt_tool.decrypt_message(to_decrypt);
        std::cout << "\nDecrypted: " << decrypted << std::endl;
    }
}

void Server::disconnect() {
    // Close the client socket and the listener socket
    closesocket(m_client_socket);
    closesocket(m_listen_socket);
    WSACleanup();

    std::cout << "Disconnected from client" << std::endl;
}

bool Server::has_client() {
    return m_has_client;
}

SOCKET Server::get_m_client_socket() const {
    return m_client_socket;
}

void Server::set_m_client_socket(SOCKET new_client_socket) {
    m_client_socket = new_client_socket;
}