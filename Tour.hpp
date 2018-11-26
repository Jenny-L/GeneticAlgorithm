/**
 * Tour.hpp
 *
 * @version 1.0
 * @author Jenny Ly
 */

#ifndef CPPASSIGNMENT2_TOUR_HPP
#define CPPASSIGNMENT2_TOUR_HPP


#include "City.hpp"
#include <vector>

using namespace std;

class Tour {
private:
    vector<City> container;
    double fitness_rating;
public:
    Tour();
    Tour(City c, double fitness = 0);
    Tour(vector<City> tour, double fitness);
    void set_fitness_rating(double fitness);
    double get_fitness_rating() const;
    vector<City> &getContainer();
    void setContainer(const vector<City> &container);
    bool operator <(const Tour& t) const;
    Tour& operator =(Tour t);

};


#endif //CPPASSIGNMENT2_TOUR_HPP
