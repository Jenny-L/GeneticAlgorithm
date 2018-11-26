/**
 * City.hpp
 *
 * @author Jenny Ly
 * @version 1.0
 */

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
