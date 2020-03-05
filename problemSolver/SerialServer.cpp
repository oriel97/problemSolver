//
// Created by tomer on 16/01/2020.
//
#include "SerialServer.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>

static bool stopMain = true;

void SerialServer::open(int port, ClientHandler *cH) {
    bool stop = false ;
    sockaddr_in address ;
    thread myThread(&SerialServer::start,this, port, address , cH , stop);
    while (stopMain) {}
    myThread.detach() ;
}

  void SerialServer::start(int port ,sockaddr_in address1 ,ClientHandler *cH, bool stop){
      int socketfd = socket(AF_INET, SOCK_STREAM, 0);
      if (socketfd == -1) {
          //error
          std::cerr << "Could not create a socket" << std::endl;
          //throw ("Could not create a socket");
      }

      //bind socket to IP address
      // we first need to create the sockaddr obj.
      sockaddr_in address; //in means IP4
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
      address.sin_port = htons(port);
      //we need to convert our number
      // to a number that the network understands.

      //the actual bind command
      if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
          std::cerr << "Could not bind the socket to an IP" << std::endl;
          //throw ("Could not bind the socket to an IP" );
      }

      //making socket listen to the port
      if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
          std::cerr << "Error during listening command" << std::endl;
          //throw("Error during listening command");
      } else {
          std::cout << "Server is now listening ..." << std::endl;
          //reading from client
      }
        while (!stop) {
            int result;
            int client_socket = 0;
            struct timeval tv;
            fd_set rfds;
            FD_ZERO(&rfds);
            FD_SET(socketfd, &rfds);
            //limit the time we wait to client to 2 minuets
            tv.tv_sec = 120;
            tv.tv_usec = 100;
            int addrlen = sizeof(address);
            result = select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
            if (result > 0) {
                client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
                cout << "client connected" << endl;
            } else {
                cout << "timeout, server shut down." << endl;
                return;
            }
            if (client_socket == -1) {
                std::cerr << "can't accept client" << std::endl;
                return;
            }

            cH->handleClient(socketfd, client_socket);
            stopMain = false ;
        }
      close(socketfd); //closing the listening socket
    }

void SerialServer::stop() {}
