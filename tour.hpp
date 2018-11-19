//
// Created by Jenny Ly on 2018-11-19.
//

#ifndef CPPASSIGNMENT2_TOUR_HPP
#define CPPASSIGNMENT2_TOUR_HPP


#include "city.hpp"
#include <vector>

using namespace std;

class tour {
private:
    vector<city> container;
    double fitness_rating;
public:
    tour(vector<city> tour, double fitness = 0);
    void set_fitness_rating(double fitness);
    double get_fitness_rating() const;
    const vector<city> &getContainer() const;


};


#endif //CPPASSIGNMENT2_TOUR_HPP
