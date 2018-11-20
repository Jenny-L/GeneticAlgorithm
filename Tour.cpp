//
// Created by Jenny Ly on 2018-11-19.
//

#include "Tour.hpp"
#include <vector>

Tour::Tour(){};

Tour::Tour(City c, double fitness):fitness_rating(fitness){
    container.push_back(c);
};

Tour::Tour(vector<City> tour, double fitness):container(tour), fitness_rating(fitness){
};

void Tour::set_fitness_rating(double fitness_rating) {
    this->fitness_rating = fitness_rating;
}

double Tour::get_fitness_rating() const {
    return fitness_rating;
}

vector<City> &Tour::getContainer(){
    return container;
}

void Tour::setContainer(const vector<City> &container) {
    Tour::container = container;
}

bool Tour::operator <(const Tour& t) const{
    if(this->fitness_rating > t.fitness_rating) {
        return true;
    }
    return false;
}
