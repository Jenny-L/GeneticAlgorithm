#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <cfloat>

#include "City.hpp"
#include "Tour.hpp"

const double SCALAR = 10000;
using namespace std;

///**
// * Shuffles a cities in a Tour
// */
//vector<City> shuffle_cities(vector<City>Tour, mt19937 &g) {
//    shuffle(Tour.begin(), Tour.end(), g);
//    for (City c: Tour) {
//        cout << "x: " << c.getX() << " c.getY() " << c.getY() << endl;
//    }
//    cout << endl;
//    return Tour;
//}

/**
 * Calculate the air distance of two places by
 * First calculating the change in x and change in y
 * Then use pythagoras
 * @return
 */
double get_distance_between_cites(City a, City b) {
    double changeX = abs(a.getX() - b.getX());
    cout << "changex: " << changeX << endl;
    double changeY = abs(a.getY() - b.getY());
    cout << "changey: " << changeY << endl;
    double distance =  sqrt(pow(changeX, 2) + pow(changeY, 2));
    cout << "distance" << distance << endl;
    return distance;

}

double determine_fitness(double distance) {
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
double get_tour_distance(vector<City> t, double &total_distance) {
    for(int i = 0; i < t.size(); ++i) {
        total_distance = total_distance + get_distance_between_cites(t[i], t[i+1]);
    }
    return total_distance;
}

/**
 * Select the parents for a new tour
 */
void select_parent(multimap<double, vector<City>> population) {

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
    const double MUTATION_RATE = 0.15;
    const int NUMBER_OF_PARENTS = 2;
    int distance;
    bool isFirstRun = true;


    double base_fitness = DBL_MIN;
    double best_fitness = DBL_MIN;
    double improvement_factor = 0.5;

    //vector<City> Tour;
    vector<Tour> population;
    Tour tour;

    //Shuffling tours device
    random_device rd;
    mt19937 g(rd());


    //Double random number generator
    double lowerBound = 0;
    uniform_real_distribution<double> unif(lowerBound, MAP_BOUNDARY);
    default_random_engine re;

    //Int random number generator
    srand(time(NULL));
    //NUMBER_OF_PARENTS = rand() % PARENT_POOL_SIZE + 1;

    //Generate a list of cites and place in one Tour
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        int city_id = 0;
        double x = unif(re);
        double y = unif(re);
        City c{x, y, city_id};
        ++city_id;
        tour.getContainer().push_back(c);
    }
    vector<City> tour_container = tour.getContainer();


    //Shuffle the cities in the Tour so it begins at a random state
    for (int i = 0; i < SHUFFLES; ++i) {
        //shuffle_cities(Tour, g);
        shuffle(tour_container.begin(), tour_container.end(), g);
    }

    //Create a list of shuffle cities and put in population

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        double total_distance = 0;

        shuffle(tour_container.begin(), tour_container.end(), g);
        for (City c: tour_container) {
            cout << "x: " << c.getX() << " c.getY() " << c.getY() << endl;
        }
        cout << endl;
        //shuffle_cities(Tour);
        get_tour_distance(tour_container, total_distance);
        double fitness = determine_fitness(total_distance);
        Tour shuffled_tour{tour_container, fitness};
        population.push_back(shuffled_tour);
        cout << "added to population index: " << i << endl;
    }

    sort(population.begin(), population.end());
    for (auto it = population.begin(); it != population.end(); ++it) {
        cout << "fitness1: " << it->get_fitness_rating() << endl;
    }

    // determine the lowest in first population
    best_fitness = population.begin()->get_fitness_rating();
    cout << "base_fitness" << base_fitness << endl;

    base_fitness = best_fitness;

//    while (best_fitness / base_fitness > improvement_factor) {
//
//        vector<City> parents;
//        vector<City> best_tour = population.rbegin()->second;
//
//        for(size_t i= 0; i < NUMBER_OF_PARENTS; ++i) {
//            int random_index = rand() % POPULATION_SIZE;
//
//        }
//
//
//        double lowest_in_current_population = population.rbegin()->first;
//        if (lowest_in_current_population < best_fitness) {
//            best_fitness = lowest_in_current_population;
//            cout << "best_fitness" << best_fitness << endl;
//        }
//    }


    //if (population.end + 1)

    //while best_fitness / base_fitness > improvement factor
    return 0;
}
