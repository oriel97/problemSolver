//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_OA_H
#define PROJECT2_OA_H

#include <stdio.h>
#include <string>
#include "Searcheable.h"
#include "Searcher.h"
#include "Matrix.h"
#include "State.h"
#include "Cell.h"
#include <algorithm>
#include <vector>
#include "Solver.h"
#include "BestFirstSearch.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "AStar.h"

template<class T, class Solution>
class OA : public Solver<vector<string>, Solution> {
private:
    Searcher<T> *searcher;
public:
    OA* clone() const{
        return new OA(*this);
    }
    OA(OA const &a){
        this->searcher = a.searcher->clone();
    }
    OA(Searcher<T> *searcher1) {
        this->searcher = searcher1;
    }
/**
 * solving the problem i got and return the solution.
 * this function is getting the vectot of the path
 * and by him running on the path and writing a string
 * of how to go from the start to the end ppoint.
 */
    Solution solve(vector<string> v) {
        int val=0;
        double temp=0;
        int flag = 0;
        int num = 0;
        Matrix *matrix = new Matrix;
        matrix->makeMatrix(v);
        cout<<matrix ;
        // getting the vector of the path agter running the algoritem.
        vector<State<T> *> myVector = this->searcher->solution(matrix);
        string path = "";
        string theResult = "";
        for (int i = 0; i < myVector.size(); i++) {
            if (i + 1 == myVector.size()) {
                theResult = path.substr(0, path.size() - 1);
                break;
            }
            State<Cell> *first;
            State<Cell> *secoend;
            first = myVector[i];
            secoend = myVector[i + 1];

            if (secoend->getShortestPath() == 0) {
                if (flag == 0) {
                    num = first->getShortestPath() + first->getCost() + secoend->getCost();
                    secoend->setShortestPath(num);
                    flag = 1;
                }
                else {
                    num = first->getShortestPath() + secoend->getCost();
                    secoend->setShortestPath(num);
                }
            }
            temp = secoend->getShortestPath();
            val = (int)temp;
            string shortPath = to_string(val);
            //making the string from the vector of the solution path:
            // making it by checking how i went from start to end.
            //right
            if (first->getState().getRow() == secoend->getState().getRow() &&
                first->getState().getColm() + 1 == secoend->getState().getColm()) {
                path = path + "right (" + shortPath + "),";
                //left
            } else if (first->getState().getRow() == secoend->getState().getRow() &&
                       first->getState().getColm() - 1 == secoend->getState().getColm()) {
                path = path + "left (" + shortPath + "),";
                //up
            } else if (first->getState().getColm() == secoend->getState().getColm() &&
                       first->getState().getRow() - 1 == secoend->getState().getRow()) {
                path = path + "up (" + shortPath + "),";
                //down
            } else {
                path = path + "down (" + shortPath + "),";
            }
        }
        return theResult;
    }
};


#endif //PROJECT2_OA_H
