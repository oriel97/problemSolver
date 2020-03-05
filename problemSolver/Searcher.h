//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H


#include "Searcheable.h"

template<class T>
class Searcher {
public:
    virtual vector<State<T> *> solution(Searcheable<T> *searcheable) = 0;
    virtual Searcher* clone() const = 0;

    virtual int getNumberOfNodesEvaluated() = 0;
};


#endif //PROJECT2_SEARCHER_H
