/**
 * @file main.cpp
 * @author Sam Rieger
 * @brief A tool to simulate an ecosystem.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "creature.h"
#include "food.h"
#include "environment.h"
#include "ui.h"
#include <random>
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>


int main() {

    

    // =================================================== SETUP UI ===========================================================

    UI ui = UI();


    // serves as the input string for UI operations.
    char input[MAX_INPUT_LENGTH + 1] = {'\0'};
    
    // =============================================== SETUP ENVIRONMENT ======================================================

    // All of the following is extensible/configurable, just limited to this specific world to avoid scope creep.
    // the eventual implementation would probably include a file load system for worlds, as well as a world/creature editor.

    
    // create locations
    Environment Forest1(std::vector<foodType>(veggie1, veggie2), 32, "The Temperate Forest");
    Environment Forest2(std::vector<foodType>(veggie1, veggie2), 30, "The Alpine Forest");

    Environment Mountains(std::vector<foodType>(veggie3, veggie2), 17, "The Craggy Peaks");

    Environment Desert(std::vector<foodType>(veggie3), 10, "Arizona");

    Environment Grassland1(std::vector<foodType>(veggie1, veggie2), 40, "The Savannah");
    Environment Grassland2(std::vector<foodType>(veggie1, veggie2), 48, "The Sprawling Prarie");

    Environment Oasis({veggie1, veggie2, veggie3}, 55, "The Oasis");

    // connect terrain
    Environment::setNeighbors(&Forest1, &Forest2);
    Environment::setNeighbors(&Forest1, &Mountains);
    Environment::setNeighbors(&Desert, &Forest2);
    Environment::setNeighbors(&Forest1, &Grassland1);
    Environment::setNeighbors(&Desert, &Grassland2);
    Environment::setNeighbors(&Grassland2, &Grassland1);
    Environment::setNeighbors(&Desert, &Grassland1);
    Environment::setNeighbors(&Oasis, &Grassland1);
    Environment::setNeighbors(&Oasis, &Forest2);

    // make a convenient array for processing environment
    Environment* const locations[] = {
        &Forest1,
        &Forest2,
        &Mountains,
        &Desert,
        &Grassland1,
        &Grassland2,
        &Oasis
        };

    // ====================================================== SETUP SPECIES =====================================================

    // holds each species template
    std::vector<Creature *> species;

    //species.reserve((size_t) (sizeof(Creature*) * MAX_NUMBER_CREATURES));

    // load species file
    std::ifstream fin;
    fin.open("./data/speciesData.spdx");

    if( fin.fail() ) {
        std::cerr << "Datafile couldn't be opened" << std::endl;
        return EXIT_FAILURE;
    }

    int n;

    fin >> n;

    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    

    for(int i = 0; i < n; ++i) {

        char creatureData[MAX_DATA_MEMBER_LENGTH + 1][11];

        for(int j = 0; j < 11; ++j) {
            fin.getline(creatureData[j], MAX_DATA_MEMBER_LENGTH);
        }

        std::vector<foodType> edible = {/*foodType::veggie1, foodType::veggie2, foodType::veggie3, foodType::softMeat*/};

        for(char c : creatureData[9]) {
            // adds enum types to edible foods
            //std::cout << c << std::endl;
            if(c >= '0' && c <= '9') {

                edible.push_back((foodType) (c - '0'));
            }
        }

        
        // constructs a species based on loaded data
        species.push_back(new Creature {
            (unsigned) atoi(creatureData[1]),
            (unsigned) atoi(creatureData[2]),
            (unsigned) atoi(creatureData[3]),
            (unsigned) atoi(creatureData[4]),
            (unsigned) atoi(creatureData[5]),
            creatureData[6],
            (unsigned) atoi(creatureData[7]),
            (unsigned) atoi(creatureData[8]),
            edible, 
            (unsigned) atoi(creatureData[10])

        });

    }


    // ================================================= SETUP RANDOM ==========================================================

    // used almost entirely in dynamic setup, this simulation is nearly entirely determinist. 

    std::random_device rd;
    std::mt19937 mt(rd());

    // chooses random locations!
    std::uniform_int_distribution<int>randomLocation(0, (int) ((sizeof(locations) / sizeof(locations[0]) - 1)) );
    
    // ====================================================== DYNAMIC SETUP ========================================================

    // holds every living creature
    std::vector<Creature *> creatures;

    char name[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};

    for(Creature *& s : species) {
        input[0] = '\0'; // works because string is null-terminated

        for(int i = 0; i < 33; ++i) {
            name[i] = '\0';
        }

        s->getName(name);



        char prompt[MAX_PROMPT_LENGTH + 1] = "How many creatures of type \033[34m";

        strncat(prompt, name, MAX_PROMPT_LENGTH);
        strncat(prompt, "\033[0m would you like to start with?", MAX_PROMPT_LENGTH);

        ui.printPrompt(prompt, input);

        for(int i = 0; i < atoi(input); ++i)    {
            creatures.push_back(new Creature(*s));
            creatures.back()->setLocation(locations[randomLocation(mt)]);
        }
    }

    // ========================================================= RUN SIMULATION ========================================================

    int tick = 0;

    while(true) {
        // pointer to species of creatures to be hatched
        std::vector<Creature*> creatureQueue = {};

        // pointer to location of creatures to be hatched
        std::vector<Environment*> locationQueue = {};

        ui.printTimeTick(++tick);

        // resort creatures based on their speed/age

        makeCreatureInitiativeOrder(creatures);              

        // grow more food

        for(Environment * e : locations) {
            e->updateFoodList();
        }   


        // essentially a for loop, but allows for reindexing
        auto iterator = creatures.begin();        

        while (iterator != creatures.end()) {

            Creature * c = (*iterator);

            // creature actions, one at a time based on speed/age, but only if alive

            if(!c->checkDead()) {
                switch(c->makeDecision(&ui, creatures)) {
                    case 1:
                        creatureQueue.push_back(c->getParent());
                        locationQueue.push_back(c->getLocation());
                        break;
                    case 3:
                        break;
                }



                // end of turn metabolism (leading cause of death)
                c->metabolize();
            }           
            
            // deletes those which are dead
            if(c->checkDead()) {
                ui.printDeath(c);
                delete *iterator; 
                iterator = creatures.erase(iterator);
            } else {
                ++iterator;
            }
            
           
            
        }

        for(int i = 0; i < (int) creatureQueue.size(); ++i) {
            creatures.push_back(new Creature(*creatureQueue.at(i)));
            creatures.back()->setLocation(locationQueue.at(i));
        }

        

        // allow user to do UI things (look at data)
        input[0] = '\0'; // works because string is null-terminated
        ui.printPrompt("Type \"DETAILS\" to view specific information, or anything else to skip.", input);
        
        if(strncmp("DETAILS", input, 9) == 0) {
            while(true) {
                input[0] = '\0'; // works because string is null-terminated
                ui.printPrompt("\"POP\" for population data, \"IND\" for individual data, or anything else to exit details mode", input);
                if(strncmp("POP", input, 4) == 0) {

                    for(Creature * s : species) {
                        unsigned int count = 0;
                        for(Creature * c : creatures) {
                            if(c->getParent() == s) {
                                ++count;
                            }
                        }

                        ui.printPopulation(s, count);
                    }
                    
                } else if(strncmp("IND", input, 4) == 0) {
                    for(Creature * c : creatures) {
                        ui.printCreatureInformation(c);
                    }

                } else {
                    break;
                }
            }

            
        }



        // +1 because of null terminator; the actual max input length is 64, but we need the 65th.  personal preference for notation (anyone editing the macros does not need to consider terminators)
        
        input[0] = '\0'; // works because string is null-terminated
        ui.printPrompt("Type anything else to execute another timestep, or type \"HALT\" to end it.", input);

        if(strncmp(input, "HALT", 5) == 0) {
            break;
        }
    }



    // ============================================================ END =============================================================


    for(Creature *&c : species) {
        if(c != nullptr) {
            delete c;
        }
    }

    for(Creature *&c : creatures) {
        if(c != nullptr) {
            delete c;
        }
    }




    return EXIT_SUCCESS;

}