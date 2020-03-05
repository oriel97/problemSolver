#include <iostream>
#include "server.h"
#include "SerialServer.h"
#include "nameSpace.h"

using namespace std;

int main(int args, char *argv[]) {
    // check if we get the port in argv
    int port ;
    if (argv[1] == nullptr){
        port =5600;
    }else {
        port = stoi(argv[1]);
    }
    nameSpace *runner = new nameSpace(port);
    runner->run();
    delete (runner);
    return 0;
}
