#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <cfloat>

#include "city.hpp"
#include "tour.hpp"

const double SCALAR = 10000;
using namespace std;

///**
// * Shuffles a cities in a tour
// */
//vector<city> shuffle_cities(vector<city>tour, mt19937 &g) {
//    shuffle(tour.begin(), tour.end(), g);
//    for (city c: tour) {
//        cout << "x: " << c.getX() << " c.getY() " << c.getY() << endl;
//    }
//    cout << endl;
//    return tour;
//}

/**
 * Calculate the air distance of two places by
 * First calculating the change in x and change in y
 * Then use pythagoras
 * @return
 */
double get_distance_between_cites(city a, city b) {
    double changeX = abs(a.getX() - b.getX());
    //cout << "changex: " << changeX << endl;
    double changeY = abs(a.getY() - b.getY());
    //cout << "changey: " << changeY << endl;
    double distance =  sqrt(pow(changeX, 2) + pow(changeY, 2));
    //cout << "distance" << distance << endl;
    return distance;

}

double calculate_fitness(double distance) {
    double fitness = (1 / distance) * SCALAR;
    //cout << "fitness " << fitness << endl;
    //cout << endl;
    return fitness;
}

/**
 * Calculate the distance between 2 adjacent cities for a tour
 * @param t
 * @return
 */
double get_tour_distance(vector<city> t, double &total_distance) {
    for(int i = 0; i < t.size(); ++i) {
        total_distance = total_distance + get_distance_between_cites(t[i], t[i+1]);
    }
    return total_distance;
}

//double determine_fitness() {
//
//}
//
///**
// * Select the parents for a new tour
// */
//void select_parent() {
//
//}
//
///**
// * Creates a new tour from a given set of parent tours
// */
//void crossover() {
//
//}
//
///**
// * May mutate a tour
// */
//void mutate() {
//
//}
//
///**
// * Check if a tour contains a city
// */
//bool contains_city() {
//
//}

int main() {
    const int CITIES_IN_TOUR = 5; //orginally 32
    const int POPULATION_SIZE = 5; //number or tours in  a population 32
    const int SHUFFLES = 5; //64
    const int ITERATIONS = 10; //1000
    const int MAP_BOUNDARY = 1000; //1000
    const int NUMBER_OF_ELITES = 1; //1
    const int PARENT_POOL_SIZE = 5;
    const int MUTATION_RATE = 0.15;
    int distance;
    bool isFirstRun = true;


    double base_fitness;
    double best_fitness = DBL_MIN;
    double improvement_factor = 0.5;

    vector<city> tour;
    multimap<double, vector<city>> population;

    //Shuffling tours device
    random_device rd;
    mt19937 g(rd());


    //Double random number generator
    double lowerBound = 0;
    uniform_real_distribution<double> unif(lowerBound, MAP_BOUNDARY);
    default_random_engine re;

    //Int random number generator
    srand(time(NULL));
    PARENT_POOL_SIZE = rand() % POPULATION_SIZE + 1;


    //Generate a list of cites and place in tour
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        int city_id = 0;
        double x = unif(re);
        double y = unif(re);
        city c{x, y, city_id};
        ++city_id;
        tour.push_back(c);
    }
//
    //Shuffle the cities in the tour so it begins at a random state
    for (int i = 0; i < SHUFFLES; ++i) {
        //shuffle_cities(tour, g);
        shuffle(tour.begin(), tour.end(), g);

    }

    //Create a list of shuffle cities and put in population

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        double total_distance = 0;
        shuffle(tour.begin(), tour.end(), g);
        //shuffle_cities(tour);
        get_tour_distance(tour, total_distance);
        double fitness = calculate_fitness(total_distance);
        population.insert(pair<double, vector<city>>(fitness, tour));
        cout << "added to population index: " << i << endl;
    }
    for (auto it = population.begin(); it != population.end(); ++it) {
        cout << "fitness1: " << it->first << endl;
    }

    // determine the lowest in first population
    base_fitness = population.rbegin()->first;
    cout << "base_fitness" << base_fitness << endl;

    base_fitness = best_fitness;

    while (best_fitness / base_fitness > improvement_factor) {
        vector<city> best_tour;

        for(auto it = population.begin(); it != population.end(); ++it) {
            if (it->first != best_fitness) {

            }
        }


        double lowest_in_current_population = population.rbegin()->first;
        if (lowest_in_current_population < best_fitness) {
            best_fitness = lowest_in_current_population;
            cout << "best_fitness" << best_fitness << endl;
        }
    }


    //if (population.end + 1)

    //while best_fitness / base_fitness > improvement factor
    return 0;
}
