//
// Created by oriel on 20/01/2020.
//

#ifndef PROJECT2_PRIORITYQUEUE_H
#define PROJECT2_PRIORITYQUEUE_H


#include <queue>
#include <iostream>
#include "State.h"

using namespace std;


template<class T>
class compOfPqueue {
public:
    bool operator()(State<T> *left, State<T> *right) {
        return left->getShortestPath() > right->getShortestPath();
    }
};

template<class T>
class PriorityQueue {
    priority_queue<State<T> *, vector<State<T> *>, compOfPqueue<T>> pq;
public:
    //check if its empty
    bool empty() {
        return this->pq.empty();
    }

/**
 * pop out from the queue
 */
    State<T> *popOutFromthePqueue() {
        State<T> *topVal = this->pq.top();
        this->pq.pop();
        return topVal;
    }

/**
 * add to the queue
 * @param addVal
 */
    void addToPqueue(State<T> *addVal) {
        this->pq.push(addVal);
    }

/**
 * check if it in the queue
 * and return true if it in the queue
 */
    bool isPqueueContains(State<T> *checkVal) {
        bool returnVal = false;
        vector<State<T> *> temp;
        while (!this->pq.empty()) {
            State<T> *val = this->popOutFromthePqueue();
            temp.push_back(val);
            if (val->Equal(checkVal)) {
                returnVal = true;
                break;
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            this->addToPqueue(temp[i]);
        }
        return returnVal;
    }

/**
 * update the queue according to the priority-what need to be first..
 */
    void updatePqueuePriority(State<T> *curVal, State<T> *newVal) {
        double newPath;
        vector<State<T> *> temp;
        while (!this->pq.empty()) {
            State<T> *topVal = this->popOutFromthePqueue();
            temp.push_back(topVal);
            if (curVal->Equal(topVal)) {
                topVal->setParent(newVal);
                newPath = newVal->getShortestPath() + curVal->getShortestPath();
                topVal->setShortestPath(newPath);
                break;
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            this->pq.push(temp[i]);
        }
    }

};


#endif //PROJECT2_PRIORITYQUEUE_H
