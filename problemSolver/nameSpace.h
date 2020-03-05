//
// Created by tomer on 20/01/2020.
//

#ifndef EVENDEREH2_NAMESPACE_H
#define EVENDEREH2_NAMESPACE_H

#include "AStar.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "Cell.h"
#include "DFS.h"
#include "Matrix.h"

#include "OA.h"
#include "PriorityQueue.h"
#include "Searcheable.h"
#include "Solver.h"
#include "Searcher.h"
#include "State.h"

class nameSpace {
private:
    int port;
public:
    nameSpace(int port) {
        this->port = port;
    }

    void run();
};


#endif //EVENDEREH2_NAMESPACE_H
