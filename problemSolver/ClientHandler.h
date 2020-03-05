//
// Created by tomer on 16/01/2020.
//

#ifndef EVENDEREH2_CLIENTHANDLER_H
#define EVENDEREH2_CLIENTHANDLER_H

#include <string.h>
#include <string>

using namespace std;

class ClientHandler {
public:
    virtual void  handleClient(int input,int output)=0;
    virtual ClientHandler* clone()=0;
};


#endif //EVENDEREH2_CLIENTHANDLER_H
