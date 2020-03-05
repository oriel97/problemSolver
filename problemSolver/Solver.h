//
// Created by oriel on 19/01/2020.
//

#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H


template<class P, class S>

class Solver {
public:
    //get a problem and return the solution
    virtual S solve(P) = 0;
    virtual Solver* clone() const = 0;
};


#endif //PROJECT2_SOLVER_H
