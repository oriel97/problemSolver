//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H


#include "Searcher.h"
#include "Searcheable.h"
#include "PriorityQueue.h"
#include <unordered_map>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

template<class T>
class BestFirstSearch : public Searcher<T> {

    PriorityQueue<T> *openList;
    int nodesEvaluated = 0;
    vector<State<T> *> path;
public:
    BestFirstSearch(BestFirstSearch const &) {

    }

    BestFirstSearch *clone() const {
        return new BestFirstSearch(*this);
    }

    virtual int getNumberOfNodesEvaluated() {
        return this->nodesEvaluated;
    }

/**
 * search for the shortest and return the shortest
 * way from the start to the end in vector.
 */
    virtual vector<State<T> *> solution(Searcheable<T> *searchable) {
        path.clear();
        this->openList = new PriorityQueue<T>();
        State<T> *start = searchable->getInitialeState();
        this->openList->addToPqueue(start);
        start->setShortestPath(start->getCost());

        unordered_set<State<T> *> closed;
        typename unordered_set<State<T> *>::iterator itOnClosed;
        State<T> *goal = searchable->getGallState();

        while (!this->openList->empty()) {

            State<T> *current = this->openList->popOutFromthePqueue();
            closed.insert(current);
            if (current == goal) {
                path.push_back(goal);
                while (goal->getParent() != NULL) {
                    State<T> *dadOfCurrent = goal->getParent();
                    path.push_back(dadOfCurrent);
                    goal = dadOfCurrent;
                }
                reverse(path.begin(), path.end());

                State<T> *bb = path.back();

                return path;
            }
            nodesEvaluated += 1;

            vector<State<T> *> successors = searchable->getAllPossibleState(current);
            typename vector<State<T> *>::iterator iteratorOfSuccessors;
            iteratorOfSuccessors = successors.begin();

            for (iteratorOfSuccessors; iteratorOfSuccessors != successors.end(); ++iteratorOfSuccessors) {
                State<T> *it = (*iteratorOfSuccessors);

                double currentPath = current->getShortestPath() + it->getCost();
                itOnClosed = closed.find(it);

                if (itOnClosed == closed.end() && !this->openList->isPqueueContains(it)) {
                    it->setParent(current);
                    it->setShortestPath(currentPath);
                    this->openList->addToPqueue(it);
                } else if (currentPath < it->getCost()) {
                    if (!this->openList->isPqueueContains(it)) {
                        this->openList->addToPqueue(it);
                    } else {
                        this->openList->updatePqueuePriority(it, current);
                    }
                }
            }
        }
        path.push_back(goal);
        while (goal->getParent() != NULL) {
            State<T> *dadOfCurrent = goal->getParent();
            path.push_back(dadOfCurrent);
            goal = dadOfCurrent;
        }

        if (goal->getParent() == NULL) {
            vector<State<T> *> returnVal;
            return returnVal;
        }

        reverse(path.begin(), path.end());
        return path;
    }

};

#endif //PROJECT2_BESTFIRSTSEARCH_H
