//
// Created by tomer on 20/01/2020.
//

#include <thread>
#include "MyParallelServer.h"


void MyParallelServer::open(int port, ClientHandler *client_handler) {
    bool stop = false;
    ClientHandler *cH = client_handler ;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }

    //bind socket to IP address new
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
    } else {
        std::cout << "Server is now listening ..." << std::endl;
        //reading from client
    }
    thread myThread(&MyParallelServer::start,this, socketfd, address ,cH , stop);
    myThread.join();
}

void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *cH, bool stop) {
    cout << "Parallel server waiting for clients.." << endl;
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
        //open new tread to every client
        thread myThread(&MyParallelServer::handleForThread,this,client_socket,socketfd,cH);
        myThread.detach();
    }
}
void MyParallelServer::stop() {}

void MyParallelServer::handleForThread(int client_socket ,int socketfd , ClientHandler *cH) {
    // make a deep clone of client handler to every client
    ClientHandler* clone = cH->clone();
    clone->handleClient(socketfd, client_socket);
}