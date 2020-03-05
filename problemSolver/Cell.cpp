//
// Created by oriel on 17/01/2020.
//
#include "Cell.h"

double Cell::getRow() const {
    return row;
}

void Cell::setRow(double row) {
    this->row = row;
}

double Cell::getColm() const {
    return colm;
}

void Cell::setColm(double colm) {
    this->colm = colm;
}

bool Cell::operator==(Cell indexsMat) {
    return row == indexsMat.getRow() && colm == indexsMat.getColm();
}

#include "Cell.h"
