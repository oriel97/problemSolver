//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_MATRIX_H
#define PROJECT2_MATRIX_H

#include <vector>
#include "Searcheable.h"
#include "Cell.h"
#include "string"
#include <algorithm>
#include "State.h"

using namespace std;

class Matrix : public Searcheable<Cell> {
private:
    State<Cell> *end;
    State<Cell> *start;
    vector<vector<State<Cell> *>> matrix;
public:
    vector<vector<State<Cell> *>> makeMatrix(vector<string>);

    State<Cell> *getInitialeState() override;

    State<Cell> *getGallState() override;

    vector<State<Cell> *> getAllPossibleState(State<Cell> *state) override;

    State<Cell> *getEnd() const;

    void setEnd(State<Cell> *end);

    State<Cell> *getStart() const;

    void setStart(State<Cell> *start);

    void setMatrix(vector<vector<State<Cell> *>> mat);

    const vector<vector<State<Cell> *>> getMatrix() const;


};


#endif //PROJECT2_MATRIX_H
