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
    int i;
    for(i = 0; i < t.size(); ++i) {
        total_distance = total_distance + get_distance_between_cites(t[i], t[i+1]);
    }
    total_distance += get_distance_between_cites(t[i], t[0]);
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
    double highest_fitness = 0;
    Tour fittest_parent;
    for (size_t i = 0; i < parent_population.size(); i++) {
        if (parent_population[i].get_fitness_rating() > highest_fitness) {
            fittest_parent = parent_population[i];
            highest_fitness = parent_population[i].get_fitness_rating();
        }
    }
    //sort(parent_population.begin(), parent_population.end());
    return fittest_parent;
}

/**
 *
 * @param parent
 * @param index
 * @return
 */
void add_offspring_tour(Tour parent, Tour &child, map<int, City> &used_place_id, int k) {
    auto parent_container = parent.getContainer();
    //vector <City> list_of_city_choices;
    //map<int, City> m_used_place;

    //generate a random number

    int rand_num_range = parent_container.size() - used_place_id.size();
    cout << "rand_num_range: " << rand_num_range;

    if(rand_num_range == 0) {
        return;
    }


    size_t random_index = (rand() % rand_num_range + 1);
    cout << "random index " << random_index << endl;
    cout << endl;

    if (k == NUMBER_OF_PARENTS - 1) {
        random_index = rand_num_range;
    }

//print out parent container id
    for(size_t i = 0; i < parent_container.size(); i++) {
        {
            cout << "parent_container[ " << i << "] " << parent_container[i].getId() << endl;

        }
    }

// print out values in used_place_id
//    for(size_t i = 0; i < used_place_id.size(); ++i) {
//        {
//            cout << "used_place_id[ " << i << "] " << used_place_id[i] << endl;
//
//        }
//    }


//    City c{0,0, 2};
//    City c1{0, 0, 3};
//    City c2{0, 0, 1};
//    City c3{0, 0, 4};
//    City c4{0, 0, 0};
//    vector<City> PC = {c, c1, c2, c3, c4};
//
//    map<int, City> newMap;
//    newMap.insert(pair<int,City>(1,c2));
//    newMap.insert(pair<int,City>(3,c1));
//    newMap.insert(pair<int,City>(2,c));
//    cout << endl;
    //swap cities in tour for up to the rand_num_range so that numbers up tp rand_num_range in parent_container are uniqu
    int current_dup_streak;
    vector<City> unique_container;
    //copy(parent_container.begin(), parent_container.end(), back_inserter(temp_container));
    //int parent_id;
    for(size_t i = 0; i < parent_container.size(); i++) {
        int parent_id = parent_container[i].getId();

        if(used_place_id.count(parent_id) == 0) {
            unique_container.push_back(parent_container[i]);
        }

//        while (used_place_id.count(parent_id) == 1) {
//            temp = parent_container[i];
//            parent_container[i] = parent_container[i + current_dup_streak + 1];
//            parent_container[i + current_dup_streak + 1] = temp;
//            parent_id = parent_container[i].getId();
//            cout << "id to swap : " << parent_container[i].getId() << " " << parent_container[i + current_dup_streak + 1].getId()<< endl;
//            current_dup_streak++;
//        }

    }

    //copy map to child container up to a random index
    for(size_t i = 0; i < random_index; i++) {
        City c = unique_container[i];
        //m.erase(used_place_id.at(i));
        used_place_id.insert(pair<int, City> (c.getId(), c));
        //adding to child tour container
        child.getContainer().push_back(c);
        cout << "city Id added to used_place_id " << c.getId() << endl;
    }

//        for(size_t j = 0; j < used_place_id.size(); ++j) {
//            if(parent_container[i].getId() != used_place_id[j]) {
//                cout << "deleted parents with IDs ";
//                cout << parent_container[i].getId() << endl;
//                auto it = parent_container.begin() + i;
//                list_of_city_choices.push_back(*it);
//                //parent_container.erase(parent_container.begin() + i);
//
//            }
//        }


    //check if the parent_container with that id is deleted from the parent container
//    for(auto it = used_place_id.begin(); it != used_place_id.end(); ++it) {
//        cout << "used_place_id" <<  it->first << endl;
//    }


    //find size of modified map
    //size_t size = m.size();
    //cout << "size of modified map " << size << endl;
//    if (parent_container.size() == 0) {
//        return;
//    }


    //if its the last parent random_index will be the full size of parent
//    if (parent_number == NUMBER_OF_PARENTS - 1) {
//        random_index = parent_container.size();
//    }



    //printing new child container for testing
    cout << "Printing the IDs in new child container" << endl;
    for(size_t i = 0; i < child.getContainer().size(); ++i) {
        cout << "city container id: " << child.getContainer().at(i).getId() << endl;
    }


}

//void swap_neighbouring_cities(&Tour t, int index) {
//
//}

int main() {
    const int CITIES_IN_TOUR = 32; //orginally 32
    const int POPULATION_SIZE = 32; //number or tours in  a population 32
    const int SHUFFLES = 64; //64
    const int ITERATIONS = 1000; //1000
    const int MAP_BOUNDARY = 1000; //1000
    const int NUMBER_OF_ELITES = 1; //1
    const int PARENT_POOL_SIZE = 5;
    const double MUTATION_RATE = 0.15;
    //const int NUMBER_OF_PARENTS = 3;
    int distance;

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

    uniform_real_distribution<double> unif2(lowerBound, 1);
    default_random_engine re2;

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

    int counter = 0;
   // while (best_fitness / base_fitness > improvement_factor) {
    while (best_fitness / base_fitness > 0.3 && counter < ITERATIONS) {
        size_t population_index = 0;
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
//                cout << endl;
//                cout << "5 random index choosen: " << endl;
//                for (size_t i = 0; i < PARENT_POOL_SIZE; i++) {
//                    int random_number = rand() % POPULATION_SIZE;
//                    parents_random_indices.push_back(random_number);
//                    cout << "index " << i << " " << random_number << endl;
//                }
                parent_population = select_parent(parents_random_indices, population);

                fittest_parent = get_fittest_parent(parent_population);

                fit_parent_population.push_back(fittest_parent);
//                cout << endl;
//                cout << "fit_parent_population's size" << fit_parent_population.size() << endl;
            }

            for (size_t k = 0; k < NUMBER_OF_PARENTS; ++k) {
                cout << endl;
                cout << "number parent " << k << endl;
                int index_to_swap = rand() % CITIES_IN_TOUR;
                Tour first = fit_parent_population.at(k);

                //cout << first.get_fitness_rating() << endl;

            }
            //crossing the parents
            Tour child_tour;
            map<int, City> used_place_id;
            for (size_t k = 0; k < NUMBER_OF_PARENTS; ++k) {
                cout << endl;
                cout << "NUMBER OF PARENTS" << k << endl;
                //int index_to_swap = rand() % CITIES_IN_TOUR;
                Tour first = fit_parent_population.at(k);
                //Tour second = fit_parent_population.at(k + 1);


                //Tour child
                add_offspring_tour(first, child_tour, used_place_id, k);

                double child_tour_distance = 0;
                get_tour_distance(child_tour.getContainer(), child_tour_distance);
                double fitness = determine_fitness(child_tour_distance);
                child_tour.set_fitness_rating(fitness);

            }

            child_population.push_back(child_tour);


            cout << "MADE A CHILD FROM 3 PARENTS" << endl;
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
        cout << "5 random index choosen: " << endl;
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
            cout << "index " << i << " " << random_number << endl;
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
