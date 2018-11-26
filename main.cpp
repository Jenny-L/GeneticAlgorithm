/**
 * Figure out the travelling sales man problem by using a genetic algorythm.
 * Tries to find the shortest distance between a series of cities
 *
 * @author Jenny Ly
 * @version 1.0
 */

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
const int NUMBER_OF_PARENTS = 3;

/**
 * Calculate the air distance of two places by
 * First calculating the change in x and change in y
 * Then use pythagoras
 * @return
 */
double get_distance_between_cites(City a, City b) {
    double changeX = abs(a.getX() - b.getX());
    double changeY = abs(a.getY() - b.getY());
    double distance =  sqrt(pow(changeX, 2) + pow(changeY, 2));
    return distance;

}

/**
 * Determine fitness
 * @param distance double
 * @return double
 */
double determine_fitness(double distance) {
    double fitness = (1 / distance) * SCALAR;
    return fitness;
}

/**
 * Calculate the distance between 2 adjacent cities for a tour
 * @param t as vector<City>
 * @return total_distance as double
 */
double get_tour_distance(vector<City> t, double &total_distance) {
    int i;
    for(i = 0; i < t.size() - 1; ++i) {
        total_distance = total_distance + get_distance_between_cites(t[i], t[i+1]);
    }
    ++i;
    total_distance += get_distance_between_cites(t[i], t[0]);
    return total_distance;
}

/**
 * Select the parent tours
 * @param parents_random_indices as vector<int>
 * @param population as vector<Tour>
 * @return vector <Tour>
 */
vector<Tour> select_parent(vector<int> parents_random_indices, vector<Tour> population) {
    vector<Tour> parents;
    for(size_t i = 0; i < parents_random_indices.size(); i++) {
        size_t index = parents_random_indices.at(i);
        parents.push_back(population.at(index));
    }
    return parents;
}


/**
 * Finds the fittest parent within a population
 * @param parent_population vector<Tour>
 * @return Tour
 */
Tour get_fittest_parent(vector<Tour> parent_population) {
    double highest_fitness = 0;
    Tour fittest_parent;
    for (size_t i = 0; i < parent_population.size(); i++) {
        if (parent_population[i].get_fitness_rating() > highest_fitness) {
            fittest_parent = parent_population[i];
            highest_fitness = parent_population[i].get_fitness_rating();
        }
    }
    return fittest_parent;
}

/**
 * Add offspring to tour
 * @param parent Tour
 * @param child Tour
 * @param used_place_id as map<int, City>
 * @param k as int
 * @return void
 */
void add_offspring_tour(Tour parent, Tour &child, map<int, City> &used_place_id, int k) {
    auto parent_container = parent.getContainer();

    //generate a random number
    int rand_num_range = parent_container.size() - used_place_id.size();

    if(rand_num_range == 0) {
        return;
    }


    size_t random_index = (rand() % rand_num_range + 1);

    if (k == NUMBER_OF_PARENTS - 1) {
        random_index = rand_num_range;
    }

    vector<City> unique_container;
    for(size_t i = 0; i < parent_container.size(); i++) {
        int parent_id = parent_container[i].getId();

        if(used_place_id.count(parent_id) == 0) {
            unique_container.push_back(parent_container[i]);
        }
    }

    //copy map to child container up to a random index
    for(size_t i = 0; i < random_index; i++) {
        City c = unique_container[i];
        used_place_id.insert(pair<int, City> (c.getId(), c));

        //adding to child tour container
        child.getContainer().push_back(c);
    }

}

/**
 * Point of entry
 * @return int
 */
int main() {
    const int CITIES_IN_TOUR = 32;
    const int POPULATION_SIZE = 32;
    const int SHUFFLES = 64;
    const int ITERATIONS = 1000;
    const int MAP_BOUNDARY = 1000;
    const int NUMBER_OF_ELITES = 1;
    const int PARENT_POOL_SIZE = 5;
    const double MUTATION_RATE = 0.15;
    int distance;

    double base_fitness = DBL_MIN;
    double best_fitness = DBL_MIN;
    const double improvement_factor = 0.3;

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

    uniform_real_distribution<double> unif2(lowerBound, 1);
    default_random_engine re2;

    //Int random number generator
    srand(time(NULL));

    //Generate a list of cites and place in one Tour
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        double x = unif(re);
        double y = unif(re);
        City c{x, y, i};
        tour.getContainer().push_back(c);
    }
    vector<City> tour_container = tour.getContainer();


    //Shuffle the cities in the Tour so it begins at a random state
    for (int i = 0; i < SHUFFLES; ++i) {
        shuffle(tour_container.begin(), tour_container.end(), g);
    }

    //Create a list of shuffle cities and put in population
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        double total_distance = 0;

        shuffle(tour_container.begin(), tour_container.end(), g);

        //shuffle_cities(Tour);
        get_tour_distance(tour_container, total_distance);
        double fitness = determine_fitness(total_distance);

        //add shuffled tour to population
        Tour shuffled_tour{tour_container, fitness};
        population.push_back(shuffled_tour);
    }

    for (auto it = population.begin(); it != population.end(); ++it) {
        cout << "fitness1: " << it->get_fitness_rating() << endl;
    }

    Tour fittest_tour;
    // determine the best_fitness in first population
    for (auto it = population.begin(); it != population.end(); ++it) {
        if (it->get_fitness_rating() > base_fitness) {
            base_fitness = it->get_fitness_rating();
            fittest_tour = *it;

        }
    }

    base_fitness;

    best_fitness = base_fitness;

    //Current fittest tour in population
    int counter = 0;

    while (best_fitness / base_fitness > improvement_factor && counter < ITERATIONS) {
        vector<Tour> child_population;
        vector<Tour> new_population;

        //CROSSOVER: swapping every other tour with a parent
        for (size_t i = 0; i < POPULATION_SIZE / 2; i++) {

            Tour fittest_parent;
            vector<Tour> fit_parent_population;

            //Get the parents to swap to produce a child
            for (size_t j = 0; j < NUMBER_OF_PARENTS; ++j) {

                vector<int> parents_random_indices;
                vector<Tour> parent_population;
                //Get index of 5 tours to choose fittest parent from
                for (size_t i = 0; i < PARENT_POOL_SIZE; i++) {
                    int random_number = rand() % POPULATION_SIZE;
                    parents_random_indices.push_back(random_number);
                }
                parent_population = select_parent(parents_random_indices, population);

                fittest_parent = get_fittest_parent(parent_population);

                fit_parent_population.push_back(fittest_parent);
            }

            for (size_t k = 0; k < NUMBER_OF_PARENTS; ++k) {
                int index_to_swap = rand() % CITIES_IN_TOUR;
                Tour first = fit_parent_population.at(k);
            }
            //crossing the parents
            Tour child_tour;
            map<int, City> used_place_id;
            for (size_t k = 0; k < NUMBER_OF_PARENTS; ++k) {
                Tour first = fit_parent_population.at(k);

                //Tour child
                add_offspring_tour(first, child_tour, used_place_id, k);

                double child_tour_distance = 0;
                get_tour_distance(child_tour.getContainer(), child_tour_distance);
                double fitness = determine_fitness(child_tour_distance);
                child_tour.set_fitness_rating(fitness);

            }

            child_population.push_back(child_tour);

            used_place_id.clear();

        }

        double currentMax = 0;
        for (auto it = population.begin(); it != population.end(); ++it) {
            if (it->get_fitness_rating() > currentMax) {
                fittest_tour = *it;
            }
        }

        //Building the new population with every other one being a child
        for (size_t i = 0; i < POPULATION_SIZE; i++) {
            if (i % 2 == 0) {
                new_population.push_back(child_population.at(i / 2));
            } else {
                new_population.push_back(population.at(i));
            }
        }

        new_population.at(POPULATION_SIZE - 1) = fittest_tour;

        //point population to new population
        population = new_population;

        for (auto it = population.begin(); it != population.end(); ++it) {
            cout << "FITNESS 2: " << counter << " " << it->get_fitness_rating() << endl;
        }


        //Mutation
        vector<int> random_indices;
        for (size_t i = 0; i < PARENT_POOL_SIZE; i++) {
            int random_number = rand() % (POPULATION_SIZE - 1);
            Tour t = population.at(random_number);

            for(size_t j = 0; j < t.getContainer().size(); j++) {
                double mutation_rate = unif2(re2);
                if (mutation_rate < MUTATION_RATE) {
                    City temp = t.getContainer().at(j);
                    //swap city with adjacent one
                    if (j < t.getContainer().size() - 1) {
                        t.getContainer().at(j) = t.getContainer().at(j + 1);
                        t.getContainer().at(j + 1) = temp;
                    } else {
                        t.getContainer().at(j) = t.getContainer().at(0);
                        t.getContainer().at(0) = temp;
                    }
                }
                double mutated_tour_distance = 0;
                get_tour_distance(t.getContainer(), mutated_tour_distance);
                double fitness = determine_fitness(mutated_tour_distance);
                t.set_fitness_rating(fitness);
            }
        }

        // determine the best_fitness in first population
        for (auto it = population.begin(); it != population.end(); ++it) {
            if (it->get_fitness_rating() > currentMax) {
                currentMax = it->get_fitness_rating();
            }
        }

        best_fitness = currentMax;

        counter++;

    }

    return 0;
}
