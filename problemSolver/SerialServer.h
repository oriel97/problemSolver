//
// Created by tomer on 16/01/2020.
//

#ifndef EVENDEREH2_SERIALSERVER_H
#define EVENDEREH2_SERIALSERVER_H


#include <netinet/in.h>
#include "server.h"

class SerialServer : public server {
public :
    SerialServer() {}
    void open(int port, ClientHandler *cH) ;
    void start(int socketfd ,sockaddr_in address ,ClientHandler *cH, bool stop) ;
    void stop() ;
};


#endif //EVENDEREH2_SERIALSERVER_H
