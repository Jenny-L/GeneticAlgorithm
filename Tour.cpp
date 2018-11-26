/**
 * Tour.cpp
 *
 * @author Jenny Ly
 * @version 1.0
 */

#include "Tour.hpp"
#include <vector>

/**
 * Default Constructor.
 */
Tour::Tour(){};

/**
 * Constructor with one param
 * @param c City
 * @param fitness double
 */
Tour::Tour(City c, double fitness):fitness_rating(fitness){
    container.push_back(c);
};

/**
 * Constructor with 2 param
 * @param tour vector<City>
 * @param fitness double
 */
Tour::Tour(vector<City> tour, double fitness):container(tour), fitness_rating(fitness){
};

/**
 * Setter for fitness rating
 * @param fitness_rating double
 */
void Tour::set_fitness_rating(double fitness_rating) {
    this->fitness_rating = fitness_rating;
}

/**
 * Getter for fitness rating
 * @return double
 */
double Tour::get_fitness_rating() const {
    return fitness_rating;
}

/**
 * Getter for container
 * @return vector<City>
 */
vector<City> &Tour::getContainer(){
    return container;
}

/**
 * Setter for container
 * @param container vector<City>
 */
void Tour::setContainer(const vector<City> &container) {
    Tour::container = container;
}

/**
 * Overloaded method for < operator
 * @param Tour t
 * @return bool
 */
bool Tour::operator <(const Tour& t) const{
    if(this->fitness_rating > t.fitness_rating) {
        return true;
    }
    return false;
}

/**
 * Overloaded = operator
 * @param t Tour
 * @return Tour
 */
Tour& Tour::operator=(Tour t) {
    using std::swap;

    this->container.swap(t.container);
    this->fitness_rating = t.fitness_rating;

    return *this;
}
