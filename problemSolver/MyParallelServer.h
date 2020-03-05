//
// Created by tomer on 20/01/2020.
//

#ifndef EVENDEREH2_MYPARALLELSERVER_H
#define EVENDEREH2_MYPARALLELSERVER_H

#include "server.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

class MyParallelServer : server{
public:
    void open(int port, ClientHandler *cH) ;
    void start(int socketfd, sockaddr_in address, ClientHandler *client_handler, bool stop) ;
    void stop() ;
    void handleForThread(int client_socket ,int socketfd , ClientHandler *cH) ;
};


#endif //EVENDEREH2_MYPARALLELSERVER_H
