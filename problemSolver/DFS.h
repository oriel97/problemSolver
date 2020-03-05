//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include <stdio.h>
#include <string>
#include "Searcheable.h"
#include "Searcher.h"
#include "Matrix.h"
#include "State.h"
#include "Cell.h"
#include <stack>

using namespace std;

template<class T>
class DFS : public Searcher<T> {
private:
    int counter = 0;
public:
    DFS(DFS const &){

    }
    DFS* clone() const{
        return new DFS(*this);
    }

    int getCounter() const {
        return counter;
    }

    void setCounter(int counter) {
        this->counter = counter;
    }

    vector<State<T> *> solution(Searcheable<T> *searcheable) override {
        State<T> *end = searcheable->getGallState();
        stack<State<T> *> stack;
        vector<State<T> *> theReturnVector;
        // tell that this cell benn visited
        searcheable->getInitialeState()->setIsVisited(true);
        // insert the cell in to the queue
        stack.push(searcheable->getInitialeState());

        while (!stack.empty()) {
            State<T> *current = stack.top();
            if (current->getState() == end->getState()) {
                break;
            }
            stack.pop();
            this->counter++;
            vector<State<T> *> adjusment = searcheable->getAllPossibleState(current);
            for (typename vector<State<T> *>::iterator it = adjusment.begin(); it != adjusment.end(); ++it) {
                State<T> *neigbher = (*it);
                if (!(neigbher->isVisited1())) {
                    neigbher->setIsVisited(true);
                    neigbher->setParent(current);
                    stack.push(neigbher);
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


#endif //PROJECT2_DFS_H
