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
    const int ESC=27;
    const int BUFFER_SIZE = 256;
    const int ERROR_SIZE = 256;
    std::cout << "Hello! Welcome to SecureNetChat, this application provides real time encryption\nby"
                 " encrypting user input then sending it across OSI 7 layer model.\n and decrypting"
                 " it at the side of the receiver.\n" << std::endl;

    //networking attempts
    const std::string IP_ADDRESS = "192.168.192.1";
    const int PORT = 12345;

    if (argc >= 2 && std::string(argv[1]) == "-server") {

        Server server(PORT,IP_ADDRESS.c_str());
        server.client_accept();
    } else {
        Client client(IP_ADDRESS,PORT);

    }
    //chat loop
    bool running=true;
    try{
        while(running){
            if(_kbhit()){
                char in_key=_getch();

                if(in_key=='i'||in_key=='I'){
                    std::cout<<"Insertion Mode"<<std::endl;
                    std::string message;
                    std::getline(std::cin, message);

                    if (argc >= 3 && std::string(argv[2]) == "-server"){
                        server.send_message(message);
                    }else{
                        client.send_message(message);
                    }
                }else if(in_key==ESC){
                    std::cout<<"you hit escape";
                    if (argc >= 3 && std::string(argv[2]) == "-server")
                    {
                        server.disconnect();
                    }
                    else
                    {
                        client.disconnect();
                    }

                    running=false;
                }


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
