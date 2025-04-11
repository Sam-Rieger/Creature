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
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>


using std::cout;
using std::endl;

int main() {

    // All of the following is extensible, just limited to this specific world to avoid scope creep.

    // =================================================== SETUP UI ===========================================================

    UI ui = UI();
    
    // =============================================== SETUP ENVIRONMENT ======================================================

    
    // create locations
    Environment Forest1(std::vector<foodType>(veggie1, veggie2), 32);
    Environment Forest2(std::vector<foodType>(veggie1, veggie2), 30);

    Environment Mountains(std::vector<foodType>(veggie3, veggie2), 17);

    Environment Desert(std::vector<foodType>(veggie3), 10);

    Environment Grassland1(std::vector<foodType>(veggie1, veggie2), 40);
    Environment Grassland2(std::vector<foodType>(veggie1, veggie2), 48);

    Environment Oasis({veggie1, veggie2, veggie3}, 55);

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

    // load species file
    std::ifstream fin;
    fin.open("./data/speciesData.spdx");

    if( fin.fail() ) {
        std::cerr << "Datafile couldn't be opened" << endl;
        return EXIT_FAILURE;
    }

    int n;

    fin >> n;

    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    

    for(int i = 0; i < n; ++i) {

        char creatureData[MAX_DATA_MEMBER_LENGTH + 1][11];

        for(int j = 0; j < 11; ++j) {
            fin.getline(creatureData[j], MAX_DATA_MEMBER_LENGTH);
            //cout << j << " " <<creatureData[j] << endl;
        }

        // TODO: replace with the actually edible food
        std::vector<foodType> edible = {foodType::veggie1, foodType::veggie2, foodType::veggie3, foodType::softMeat};

        
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





    
    // ====================================================== DYNAMIC STUFF HERE ========================================================

    // holds every living creature
    std::vector<Creature *> creatures;

    /** @todo: for each species, let the user input initial population and location */

    // ========================================================= RUN SIMULATION ========================================================



    while(true) {

        // resort creatures based on their speed/age

        makeCreatureInitiativeOrder(creatures);                 


        // essentially a for loop, but allows for reindexing
        auto iterator = creatures.begin();        

        while (iterator != creatures.end()) {

            Creature * c = (*iterator);

            // creature actions, one at a time (and print)




                // TODO: grab the MEAT after hunting





            // end of turn metabolism (leading cause of death)
            c->metabolize();

            // deletes those which are dead
            if(c->checkDead()) {
                ui.printDeath(c);
                delete *iterator; 
                iterator = creatures.erase(iterator);
            } else {
                ++iterator;
            }
            
           
            
        }

        // TODO: add details options

        char input[MAX_INPUT_LENGTH + 1] = {'\0'};

        ui.printPrompt("Type \"DETAILS\" to view specific creature information, or anything else to skip.", input);

        if(strncmp("DETAILS", input, 9)) {
            for(Creature *&c : species) {
                ui.printCreatureInformation(c);
            }
        }

        // +1 because of null terminator; the actual max input length is 64, but we need the 65th.  personal preference for notation (anyone editing the macros does not need to consider terminators)
        


        input[0] = '\0'; // works because string
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