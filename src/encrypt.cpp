//
// Created by drew on 2023-10-16.
//

#include "../include/encrypt.h"

Encrypt::Encrypt() {

}
std::string Encrypt::encrypt_message(const std::string& message) {
     // Create a copy of the original message
    char curr;
// Copy trial_string to buffer
    std::strcpy(m_buffer, message.c_str());

    for (int i = 0; m_buffer[i] != '\0'; i++) {
        curr = m_buffer[i];
// Perform operations on buffer[i] here
        if (curr >= 'a' && curr <= 'z') {
            curr = curr + m_ceaser_key;
            if (curr > 'z') {
                curr = curr - 'z' + 'a' - 1;
            }
        }
        m_buffer[i] = curr;
    }
    std::string encrypted_message(m_buffer);
    return encrypted_message;  // Return the modified copy
}
std::string Encrypt::decrypt_message(const std::string& message){
    // Decrypt Trial
    std::strcpy(m_buffer, message.c_str());
    std::cout<<"Message Received: "<<m_buffer;
    char curr;
    for (int i = 0; m_buffer[i] != '\0'; ++i) {
        curr = m_buffer[i];
        if (curr >= 'a' && curr <= 'z') {
            curr = curr - m_ceaser_key;
            if (curr < 'a') {
                curr = curr + 26;
            }
        }
        m_buffer[i] = curr;
    }

    // Convert m_buffer to std::string
    std::string decryptedString(m_buffer);

    return decryptedString;
}
