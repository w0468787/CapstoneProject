#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    const int BUFFER_SIZE = 256;
    const int ERROR_SIZE = 256;
    std::cout << "Hello! Welcome to SecureNetChat, this application provides real time encryption by"
                 "encrypting user input then sending it across OSI 7 layer model. and decrypting"
                 "it at the client side of the receiver.\n" << std::endl;

    //networking attempts

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
