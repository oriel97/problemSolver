//
// Created by tomer on 16/01/2020.
//
#include <stdio.h>
#include <netinet/in.h>
#include "ClientHandler.h"

#ifndef EVENDEREH2_SERVER_H
#define EVENDEREH2_SERVER_H

using namespace std;

class server {
public :
    virtual void open(int port , ClientHandler *cH) = 0 ;
    virtual void stop() = 0 ;
    virtual void start(int socketfd ,sockaddr_in address ,ClientHandler *cH, bool stop) = 0 ;
};

#endif //EVENDEREH2_SERVER_H
