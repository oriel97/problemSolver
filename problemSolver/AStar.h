//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include "Searcher.h"
#include "algorithm"

using namespace std;

template<class T>
class AStar : public Searcher<T> {
    int nodeThatEleveted = 0;
    vector<State<T> *> open1;
public:
    AStar(){

    }
    AStar(AStar const &){

    }
    AStar* clone() const{
        return new AStar(*this);
    }
    virtual int getNumberOfNodesEvaluated() {
        return this->nodeThatEleveted;
    }

/**
 * search for the shortest and return the shortest
 * way from the start to the end in vector.
 */
    vector<State<T> *> solution(Searcheable<T> *searchable) {
        open1.clear();
        nodeThatEleveted = 0;
        vector<State<T> *> close;
        State<T> *goal = searchable->getGallState();
        State<T> *start = searchable->getInitialeState();

        double f = abs(start->getState().getRow() - goal->getState().getRow())
                   + abs(start->getState().getColm() - goal->getState().getColm());

        start->setShortestPath(start->getCost());
        this->open1.push_back(start);


        while (!this->open1.empty()) {
            State<T> *current = this->minimalVal(goal);
            current->setIsVisited(true);
            close.push_back(current);


            if (current->Equal(goal)) {
                break;
            }
            this->nodeThatEleveted++;

            vector<State<T> *> adj = searchable->getAllPossibleState(current);
            while (!adj.empty()) {
                State<T> *temp = adj.back();
                adj.pop_back();
                if (temp->isVisited1()) {
                    continue;
                }

                double pathFromCurrent = current->getShortestPath() + temp->getCost();
                if (find(this->open1.begin(), this->open1.end(), temp) != this->open1.end()) {
                    if (temp->getShortestPath() < pathFromCurrent) {
                        continue;
                    }
                } else if (find(close.begin(), close.end(), temp) != close.end()) {
                    if (temp->getShortestPath() < pathFromCurrent) {
                        continue;
                    }
                    //this->popFrom(temp,&close);
                    //open1.push_back(temp);
                } else {
                    this->open1.push_back(temp);
                }
                temp->setShortestPath(pathFromCurrent);
                temp->setParent(current);
            }


        }


        vector<State<T> *> returnVal;
        State<T> *currentState = searchable->getGallState();
        State<T> *beginState = searchable->getInitialeState();
        if (currentState->getParent() == NULL) {
            return returnVal;
        }
        //loop that create the path
        while (!beginState->Equal(currentState)) {
            returnVal.push_back(currentState);
            currentState = currentState->getParent();
        }
        returnVal.push_back(searchable->getInitialeState());

        std::reverse(returnVal.begin(), returnVal.end());

        return returnVal;
    }

    /**
     * the priority queue
     * using to caculate the path
     */
    State<T> *minimalVal(State<T> *goal) {
        vector<State<T> *> temp;

        State<T> *lowest = open1.back();
        open1.pop_back();


        double huristic = abs(lowest->getState().getRow() - goal->getState().getRow())
                          + abs(lowest->getState().getColm() - goal->getState().getColm());
        double first = huristic + lowest->getShortestPath();

        while (!this->open1.empty()) {
            State<T> *state = open1.back();
            open1.pop_back();


            huristic = abs(state->getState().getRow() - goal->getState().getRow())
                       + abs(state->getState().getColm() - goal->getState().getColm());
            double newCost = huristic + state->getShortestPath();

            if (newCost < first) {
                first = newCost;
                temp.push_back(lowest);
                lowest = state;
                continue;
            }
            temp.push_back(state);

        }

        for (int i = 0; i < temp.size(); i++) {
            this->open1.push_back(temp[i]);
        }

        return lowest;
    }
};

#endif //PROJECT2_ASTAR_H
