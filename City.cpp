//
// Created by Jenny Ly on 2018-11-19.
//

#include "City.hpp"

City::City(double x, double y, int id): x(x), y(y), id(id){}

double City::getX() const {
    return x;
}

double City::getY() const {
    return y;
};

double City::getId() const {
    return id;
}