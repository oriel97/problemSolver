//
// Created by oriel on 17/01/2020.
//

#include <iostream>
#include "Matrix.h"
/**
 * making the new matrix with the vector i get.
 */
vector<vector<State<Cell> *>> Matrix::makeMatrix(vector<string> myMatrix) {
    int flag = 0;
    Cell cellEnd;
    Cell cellStart;
    vector<vector<State<Cell> *>> newMatrix;
    vector<State<Cell> *> vec;
    char delimiter = ',';
    for (int k = 0; k < myMatrix.size(); k++) {
        string s = myMatrix[k];
        string value(s);
        vector<string> v;
        // check where is the first \n
        string line = value.substr(0, value.find_first_of('\n'));
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        //updating the line
        string::size_type i = 0;
        string::size_type j = line.find(delimiter);
        //split with ','
        while (j != string::npos) {
            v.push_back(line.substr(i, j - i));
            i = ++j;
            j = line.find(delimiter, j);

            if (j == string::npos)
                v.push_back(line.substr(i, line.length()));
        }
        //check if its not part of the matrix
        // checkk if is the end or the start.
        if (v.size() == 2) {
            if (flag == 0) {

                double colm = stod(v.front());
                double row = stod(v.back());
                cellStart.setColm(colm);
                cellStart.setRow(row);
                flag = 1;
            } else {
                double colm = stod(v.front());
                double row = stod(v.back());
                cellEnd.setColm(colm);
                cellEnd.setRow(row);
            }
            // insert in to the new matrix a state of cells.
        } else {

            for (int l = 0; l < v.size(); ++l) {
                double tempNum = stod(v[l]);
                Cell cell;
                cell.setColm(l);
                cell.setRow(k);
                State<Cell> *state2 = new State<Cell>(cell, tempNum, 0);
                vec.push_back(state2);
            }
            newMatrix.push_back(vec);
            vec.clear();
            s = "";
            v.clear();
            line = "";
        }
    }

    State<Cell> *start1 = newMatrix[cellStart.getRow()][cellStart.getColm()];
    State<Cell> *end1 = newMatrix[cellEnd.getRow()][cellEnd.getColm()];
    this->setStart(start1);
    this->setEnd(end1);
    this->setMatrix(newMatrix);
    return newMatrix;
}

State<Cell> *Matrix::getInitialeState() {
    return this->start;
}

State<Cell> *Matrix::getGallState() {
    return this->end;
}
/**
 * getting all the right passibale way to go. the neighbers
 */
vector<State<Cell> *> Matrix::getAllPossibleState(State<Cell> *state) {
    vector<State<Cell> *> allPossibleState;
    int size = this->matrix.front().size() - 1;
    //0,0
    if (state->getState().getRow() == 0 && state->getState().getColm() == 0) {
        allPossibleState.push_back(this->matrix[0][1]);
        allPossibleState.push_back(this->matrix[1][0]);
        int x = 0;
        //size,size
    } else if (state->getState().getRow() == size && state->getState().getColm() == size) {
        allPossibleState.push_back(this->matrix[size][size - 1]);
        allPossibleState.push_back(this->matrix[size - 1][size]);
        // 0,size
    } else if (state->getState().getRow() == 0 && state->getState().getColm() == size) {
        allPossibleState.push_back(this->matrix[0][size - 1]);
        allPossibleState.push_back(this->matrix[1][size]);
        //size,0
    } else if (state->getState().getRow() == size && state->getState().getColm() == 0) {
        allPossibleState.push_back(this->matrix[size - 1][0]);
        allPossibleState.push_back(this->matrix[size][1]);
    }
        // left side
    else if (state->getState().getColm() == 0) {
        allPossibleState.push_back(this->matrix[state->getState().getRow()][1]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() - 1][0]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() + 1][0]);
    }
        //down side
    else if (state->getState().getRow() == size) {
        allPossibleState.push_back(this->matrix[size][state->getState().getColm() + 1]);
        allPossibleState.push_back(this->matrix[size][state->getState().getColm() - 1]);
        allPossibleState.push_back(this->matrix[size - 1][state->getState().getColm()]);
    }
        // right side
    else if (state->getState().getColm() == size) {
        allPossibleState.push_back(this->matrix[state->getState().getRow()][size - 1]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() - 1][size]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() + 1][size]);
    }
        //up side
    else if (state->getState().getRow() == 0) {
        allPossibleState.push_back(this->matrix[1][state->getState().getColm()]);
        allPossibleState.push_back(this->matrix[0][state->getState().getColm() + 1]);
        allPossibleState.push_back(this->matrix[0][state->getState().getColm() - 1]);

    }
        //middle
    else {
        allPossibleState.push_back(this->matrix[state->getState().getRow()][state->getState().getColm() + 1]);
        allPossibleState.push_back(this->matrix[state->getState().getRow()][state->getState().getColm() - 1]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() + 1][state->getState().getColm()]);
        allPossibleState.push_back(this->matrix[state->getState().getRow() - 1][state->getState().getColm()]);
    }
    for (int i = 0; i < allPossibleState.size(); i++) {
        if (allPossibleState[i]->getCost() == -1) {
            allPossibleState.erase(allPossibleState.begin() + i);
            i--;
        }
    }
    return allPossibleState;
}

State<Cell> *Matrix::getEnd() const {
    return end;
}

void Matrix::setEnd(State<Cell> *end) {
    this->end = end;
}

State<Cell> *Matrix::getStart() const {
    return start;
}

void Matrix::setStart(State<Cell> *start) {
    this->start = start;
}

void Matrix::setMatrix(vector<vector<State<Cell> *>> mat) {
    this->matrix = mat;
}

const vector<vector<State<Cell> *>> Matrix::getMatrix() const {
    return matrix;
}


