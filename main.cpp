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
 * Select the parent tours
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

Tour get_fittest_parent(vector<Tour> parent_population) {
    sort(parent_population.begin(), parent_population.end());
    return *parent_population.begin();
}

/**
 *
 * @param parent
 * @param index
 * @return
 */
void add_offspring_tour(Tour parent, Tour &child, vector<int> &used_place_id, size_t parent_number) {
   //map<int, City> m;
    auto parent_container = parent.getContainer();


//
//    //put parent tour in a map of cities
//    for(size_t i = 0; i < parent_container.size(); ++i) {
//        m.insert(pair<int, City>(parent_container.at(i).getId(), parent_container.at(i)));
//        cout << "parent tour ID in map " << parent_container.at(i).getId() << endl;
//    }
//
//    //delete cities in map where id matches that of used_place_id
//    for(size_t i = 0; i < used_place_id.size(); ++i) {
//        m.erase(used_place_id.at(i));
//        cout << "city Id erased from used_place_id " << used_place_id.at(i) << endl;
//    }

//print out parent container id
    for(size_t i = 0; i < parent_container.size(); ++i) {
        {
            cout << "parent_container[ " << i << "] " << parent_container[i].getId() << endl;

        }
    }

// print out values in used_place_id
    for(size_t i = 0; i < used_place_id.size(); ++i) {
        {
            cout << "used_place_id[ " << i << "] " << used_place_id[i] << endl;

        }
    }
    //delete cities in tour where id matches that of used_place_id
    for(size_t i = 0; i < parent_container.size(); ++i) {
        for(size_t j = 0; j < used_place_id.size(); ++j) {
            if(parent_container[i].getId() == used_place_id[j]) {
                cout << "deleted parents with IDs ";
                cout << parent_container[i].getId() << endl;
                parent_container.erase(parent_container.begin() + i);
            }
        }
    }

    //check if the parent_container with that id is deleted from the parent container
    for(size_t j = 0; j < parent_container.size(); ++j) {
        cout << "parent container at index[" << j << "] " << parent_container.at(j).getId() << endl;
    }

    size_t size= parent_container.size();
    cout << "parent container size: " << size;

    //find size of modified map
    //size_t size = m.size();
    //cout << "size of modified map " << size << endl;
    size_t random_index = (rand() % size);
    cout << "random index " << random_index << endl;
    cout << endl;

    //if its the last parent random_index will be the full size of parent
    if (parent_number == NUMBER_OF_PARENTS - 1) {
        random_index = parent_container.size();
    }

    //copy map to child container up to a random index
    City c = *next(parent_container.begin(), random_index);
    //m.erase(used_place_id.at(i));
    used_place_id.push_back(c.getId());
    cout << "city Id added to used_place_id " << c.getId() << endl;
    child.getContainer().push_back(c);

    cout << endl;

    //printing new child container for testing
    cout << "Printing the IDs in new child container" << endl;
    for(size_t i = 0; i < child.getContainer().size(); ++i) {
        cout << "city container id: " << child.getContainer().at(i).getId() << endl;
    }


}

int main() {
    const int CITIES_IN_TOUR = 5; //orginally 32
    const int POPULATION_SIZE = 5; //number or tours in  a population 32
    const int SHUFFLES = 5; //64
    const int ITERATIONS = 10; //1000
    const int MAP_BOUNDARY = 1000; //1000
    const int NUMBER_OF_ELITES = 1; //1
    const int PARENT_POOL_SIZE = 5;
    const double MUTATION_RATE = 0.15;
    //const int NUMBER_OF_PARENTS = 3;
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
        double x = unif(re);
        double y = unif(re);
        City c{x, y, i};
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
            cout << "x: " << c.getX() << " c.getY() " << c.getY() << "c.id" << c.getId() << endl;
        }
        cout << endl;
        //shuffle_cities(Tour);
        get_tour_distance(tour_container, total_distance);
        double fitness = determine_fitness(total_distance);

//        //determine base_fitness
//        if (fitness > base_fitness) {
//            base_fitness = fitness;
//        }

        //add shuffled tour to population
        Tour shuffled_tour{tour_container, fitness};
        population.push_back(shuffled_tour);
        cout << "added to population index: " << i << endl;
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

    cout << "base_fitness" << base_fitness << endl;
    base_fitness;

    best_fitness = base_fitness;

    //Current fittest tour in population


    //while (best_fitness / base_fitness > improvement_factor) {
    size_t population_index = 0;

    //CROSSOVER: swapping every other tour with a parent
    for(auto it = population.begin(); it != population.end(); ++it) {

        Tour fittest_parent;
        vector<Tour> fit_parent_population;

        //Get the parents to swap to produce a child
        for(size_t j = 0; j < NUMBER_OF_PARENTS; ++j) {


            vector<int> parents_random_indices;
            vector<Tour> parent_population;
            //Get index of 5 tours to choose fittest parent from
            cout << endl;
            cout << "5 random index choosen: " << endl;
            for (size_t i = 0; i < PARENT_POOL_SIZE; ++i) {
                parents_random_indices.push_back(rand() % POPULATION_SIZE);
                cout << "index " << i << rand() % POPULATION_SIZE << endl;
            }
            parent_population = select_parent(parents_random_indices, population);

            fittest_parent = get_fittest_parent(parent_population);

            fit_parent_population.push_back(fittest_parent);
            cout << endl;
            cout << "fit_parent_population's size" << fit_parent_population.size() << endl;
            //Tour current_tour = *it;

            //swapping parent and current tour
            //swap_ranges(current_tour.getContainer().begin() + index_to_swap, current_tour.getContainer().end(), fittest_parent.getContainer().begin() + index_to_swap);

            //cout << "length of current_tour" << current_tour.getContainer().size();
            //population.at(population_index) = current_tour;
            //++population_index;
        }

        //crossing the parents
        Tour child_tour;
        vector<int> used_place_id;
        for(size_t k = 0; k < NUMBER_OF_PARENTS; ++k) {
            cout << endl;
            cout << "NUMBER OF PARENTS" << k << endl;
            int index_to_swap = rand() % CITIES_IN_TOUR;
            Tour first = fit_parent_population.at(k);
            //Tour second = fit_parent_population.at(k + 1);

            //Tour child
            add_offspring_tour(first, child_tour, used_place_id, k);

        }

        cout << "THERE SHOULD ONLY BE ONE CHILD" << endl;
        if (it != population.end() - 1) {
            ++it;
        }
    }

    for (auto it = population.begin(); it != population.end(); ++it) {
        cout << "fitness2: " << it->get_fitness_rating() << endl;
    }



//
//        sort(population.begin(), population.end());
//        double lowest_in_current_population = population.begin()->get_fitness_rating();
//        if (lowest_in_current_population < best_fitness) {
//            best_fitness = lowest_in_current_population;
//            cout << "best_fitness" << best_fitness << endl;
//        }
    //}


    //if (population.end + 1)

    //while best_fitness / base_fitness > improvement factor
    return 0;
}
