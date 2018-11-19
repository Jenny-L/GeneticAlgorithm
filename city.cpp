//
// Created by Jenny Ly on 2018-11-19.
//

#include "city.hpp"

city::city(double x, double y, int id): x(x), y(y), id(id){}

double city::getX() const {
    return x;
}

double city::getY() const {
    return y;
};