//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

#include "Cell.h"

template<class T>
class State {
private:
    T state;
    State<T> *parent;
    bool isVisited;
    double cost;
    double minPath;
public:
    State(T state1, double cost1, double minPath1) {
        this->state = state1;
        this->cost = cost1;
        this->parent = nullptr;
        this->minPath = minPath1;
        this->isVisited = false;
    }

    T getState() const {
        return state;
    }

    void setState(T state) {
        this->state = state;
    }

    State<T> *getParent() const {
        return parent;
    }

    void setParent(State<T> *parent) {
        this->parent = parent;
    }

    bool isVisited1() const {
        return isVisited;
    }

    void setIsVisited(bool isVisited) {
        this->isVisited = isVisited;
    }

    double getCost() const {
        return cost;
    }

    void setCost(double cost) {
        this->cost = cost;
    }

    double getShortestPath() const {
        return this->minPath;
    }

    void setShortestPath(double shortestPath) {
        this->minPath = shortestPath;
    }

    bool Equal(State *state2) {
        return (this->state == state2->state);
    }

    bool operator<(const State<T> *b) {
        return minPath < b->getShortestPath();
    }

    bool operator>(State<T> b) const {
        return minPath > b.getShortestPath();
    }

    bool operator==(State<T> *b) {
        return minPath == b->getShortestPath();
    }
};


#endif //PROJECT2_STATE_H
