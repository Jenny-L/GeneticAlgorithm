#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <cfloat>

#include "city.hpp"
#include "tour.hpp"

const double SCALAR = 5;
using namespace std;

/**
 * Shuffles a cities in a tour
 */
vector<city> shuffle_cities(vector<city>tour, mt19937 &g) {
    shuffle(tour.begin(), tour.end(), g);
    copy(tour.begin(), tour.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return tour;
}

/**
 * Calculate the air distance of two places by
 * First calculating the change in x and change in y
 * Then use pythagoras
 * @return
 */
double get_distance_between_cites(city a, city b) {
    double changeX = abs(a.getX() - b.getX());
    double changeY = abs(a.getY() - b.getY());
    return sqrt(pow(changeX, 2) + pow(changeY, 2));

}

double calculate_fitness(double distance) {
    return (1 / distance) * SCALAR;
}

/**
 * Calculate the distance between 2 adjacent cities for a tour
 * @param t
 * @return
 */
double get_tour_distance(vector<city> t) {
    double distance = 0;
    for(int i = 0; i < t.size() - 1; ++i) {
        distance = distance + get_distance_between_cites(t[i], t[i+1]);
    }
    return distance;
}

double determine_fitness() {

}

/**
 * Select the parents for a new tour
 */
void select_parent() {

}

/**
 * Creates a new tour from a given set of parent tours
 */
void crossover() {

}

/**
 * May mutate a tour
 */
void mutate() {

}

/**
 * Check if a tour contains a city
 */
bool contains_city() {

}

/**
 * Generates a random number between 00.000 and 1000.000
 * @return double unif
 */
uniform_real_distribution<double> &initaliseUniformDist() {
    double lowerBound = 0;
    double upperBound = 1000;
    uniform_real_distribution<double> unif(lowerBound, upperBound);
    return unif;
}




int main() {
    const int CITIES_IN_TOUR = 32;
    const int POPULATION_SIZE = 32; //number or tours in  a population
    const int SHUFFLES = 64;
    const int ITERATIONS = 1000;
    const int MAP_BOUNDARY = 1000;
    const int NUMBER_OF_ELITES = 1;
    int distance;


    double base_distance = DBL_MIN;

    vector<city> tour_container;
    map<double, vector<city>> population;

    //Shuffling tours device
    random_device rd;
    mt19937 g(rd());


    //Random number generator
    uniform_real_distribution<double> unif = initaliseUniformDist();
    default_random_engine re;

    //Generate a list of cites and place in tour_container
    for(int i = 0; i < CITIES_IN_TOUR; ++i) {
        int city_id = 0;
        double x = unif(re);
        double y = unif(re);
        city c{x,y, city_id};
        ++city_id;
        tour_container.push_back(c);
    }

    //Shuffle the cities in the tour_container so it begins at a random state
    for(int i = 0; i < SHUFFLES; ++i) {
        shuffle_cities(tour_container, g);

    }

    //Create a list of shuffle cities and put in population
    for(int i = 0; i < POPULATION_SIZE; ++i) {
        shuffle_cities(tour_container, g);
        double distance = get_tour_distance(tour_container);
        double fitness = calculate_fitness(distance);
        population.insert(pair<double, vector<city>>(fitness, tour_container));
    }

    //while best_distance / base_distance > improvement factor
    return 0;
}

