//
// Created by oriel on 17/01/2020.
//

#ifndef PROJECT2_CELL_H
#define PROJECT2_CELL_H


class Cell {
private:
    double row;
    double colm;
public:
    double getRow() const;

    void setRow(double row);

    double getColm() const;

    void setColm(double colm);

    bool operator==(Cell indexsMat);

};


#endif //PROJECT2_CELL_H
