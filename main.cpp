#include <iostream>
#include <vector>
#include <map>
#include <random>

#include "city.hpp"

using namespace std;

uniform_real_distribution<double> &initaliseUniformDist();
vector<city> shuffle_cities(vector<city>tour, mt19937 &g)

int main() {
    const int CITIES_IN_TOUR = 32;
    const int POPULATION_SIZE = 32;
    const int SHUFFLES = 64;
    const int ITERATIONS = 1000;
    const int MAP_BOUNDARY = 1000;
    const int NUMBER_OF_ELITES = 1;
    static int city_id = 0;

    vector<city> tour;
    multimap<double, vector<city>> population;

    //Shuffling tours device
    random_device rd;
    mt19937 g(rd());


    //Random number generator
    uniform_real_distribution<double> unif = initaliseUniformDist();
    default_random_engine re;

    //Generate a list of cites and place in tour
    for(int i = 0; i < CITIES_IN_TOUR; ++i) {
        double x = unif(re);
        double y = unif(re);
        city c{x,y, city_id};
        ++city_id;
        tour.push_back(c);
    }

    //Create a list of shuffle cities and put in population
    for(int i; i < POPULATION_SIZE; ++i) {
        shuffle_cities(tour, g);

    }

    //while best_distance / base_distance > improvement factor
    return 0;
}

/**
 * Shuffles a cities in a tour
 */
vector<city> shuffle_cities(vector<city>tour, mt19937 &g) {
    shuffle(tour.begin(), tour.end(), g);
    copy(tour.begin(), tour.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return tour;
}

double get_distance_between_cites() {

}

double get_tour_distance() {

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


