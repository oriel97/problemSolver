//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_BFS_H
#define PROJECT2_BFS_H

#include <stdio.h>
#include <string>
#include "Searcheable.h"
#include "Searcher.h"
#include "Matrix.h"
#include "State.h"
#include "Cell.h"
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template<class T>
class BFS : public Searcher<T> {
private:
    int counter = 0;
public:
    BFS(BFS const &){

    }
    BFS* clone() const{
        return new BFS(*this);
    }
    int getCounter() const {
        return counter;
    }

    void setCounter(int counter) {
        this->counter = counter;
    }
/**
 * search for the shortest and return the shortest
 * way from the start to the end in vector.
 */
    vector<State<T> *> solution(Searcheable<T> *searcheable) override {
        State<T> *end = searcheable->getGallState();
        queue<State<T> *> queue;
        vector<State<T> *> theReturnVector;
        // tell that this cell benn visited
        searcheable->getInitialeState()->setIsVisited(true);
        // insert the cell in to the queue
        queue.push(searcheable->getInitialeState());

        while (!queue.empty()) {
            State<T> *current = queue.front();
            if (current->getState() == end->getState()) {
                break;
            }
            queue.pop();
            this->counter++;
            vector<State<T> *> adjusment = searcheable->getAllPossibleState(current);
            for (typename vector<State<T> *>::iterator it = adjusment.begin(); it != adjusment.end(); ++it) {
                State<T> *neigbher = (*it);
                if (!(neigbher->isVisited1())) {
                    neigbher->setIsVisited(true);
                    neigbher->setParent(current);
                    queue.push(neigbher);
                }
            }


        }
        if (end->getParent() == NULL) {
            return theReturnVector;
        }
        // making the solution vector
        while (!end->Equal(searcheable->getInitialeState())) {
            theReturnVector.push_back(end);
            end = end->getParent();
        }
        theReturnVector.push_back(searcheable->getInitialeState());

        reverse(theReturnVector.begin(), theReturnVector.end());

        return theReturnVector;
    }

    int getNumberOfNodesEvaluated() override {
        return counter;
    }
};


#endif //PROJECT2_BFS_H
