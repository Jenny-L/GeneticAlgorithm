//
// Created by Jenny Ly on 2018-11-19.
//

#ifndef CPPASSIGNMENT2_CITY_HPP
#define CPPASSIGNMENT2_CITY_HPP


class City {
private:
    double x;
    double y;
    int id;
public:
    City(double x, double y, int id);
    double getX() const;
    double getY() const;
    int getId() const;
    City& operator=(const City &c);

};


#endif //CPPASSIGNMENT2_CITY_HPP
