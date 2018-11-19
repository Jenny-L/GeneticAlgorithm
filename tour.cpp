//
// Created by Jenny Ly on 2018-11-19.
//

#include "tour.hpp"

tour::tour(vector<city> tour, double fitness):container(tour), fitness_rating(fitness){};

void tour::set_fitness_rating(double fitness_rating) {
    this->fitness_rating = fitness_rating;
}

double tour::get_fitness_rating() const {
    return fitness_rating;
}

const vector<city> &tour::getContainer() const {
    return container;
}
