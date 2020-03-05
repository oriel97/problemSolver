#include "nameSpace.h"
#include "SerialServer.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
#include "CachManager.h"

//
// Created by tomer on 20/01/2020.
//

void nameSpace::run() {
        auto *server = new MyParallelServer();
        auto *chachManager = new CachManager<string, string> (3);
        auto *Astar = new AStar<Cell>;
        auto *solver = new OA<Cell, string>(Astar);
        auto *handelClient = new MyClientHandler(chachManager, solver);
        server->open(this->port, handelClient);
}






