//
// Created by Jenny Ly on 2018-11-19.
//

#ifndef CPPASSIGNMENT2_CITY_HPP
#define CPPASSIGNMENT2_CITY_HPP


class city {
private:
    double x;
    double y;
    int id;
public:
    city(double x, double y, int id);
    double getX() const;
    double getY() const;

};


#endif //CPPASSIGNMENT2_CITY_HPP
