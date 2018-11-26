//
// Created by Jenny Ly on 2018-11-19.
//

#include "City.hpp"

/**
 * Constructor
 * @param x  double
 * @param y double
 * @param id int
 */
City::City(double x, double y, int id): x(x), y(y), id(id){}

/**
 * Getter for x
 * @return x double
 */
double City::getX() const {
    return x;
}

/**
 * Getter for y
 * @return y double
 */
double City::getY() const {
    return y;
};

/**
 * Getter for id
 * @return id as int
 */
int City::getId() const {
    return id;
}

/**
 * Overload =operator
 * @param c City
 * @return City
 */
City& City::operator=(const City &c) {
    this->x = c.x;
    this->y = c.y;
    this->id = c.id;
    return *this;
}
