//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_SEARCHEABLE_H
#define PROJECT2_SEARCHEABLE_H

#include "State.h"
#include "list"
#include "vector"

using namespace std;

template<class T>
class Searcheable {
public:
    virtual State<T> *getInitialeState() = 0;

    virtual State<T> *getGallState() = 0;

    virtual vector<State<T> *> getAllPossibleState(State<T> *state) = 0;

};


#endif //PROJECT2_SEARCHEABLE_H
