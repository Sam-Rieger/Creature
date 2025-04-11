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

    Environment Grassland1(std::vector<foodType>(veggie1, veggie2), 40, "The Nation of Africa");
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
        strncat(prompt, "\033[35m would you like to start with?", MAX_PROMPT_LENGTH);

        ui.printPrompt(prompt, input);

        for(int i = 0; i < atoi(input); ++i)    {
            creatures.push_back(new Creature(*s));
            creatures.back()->setLocation(locations[randomLocation(mt)]);
        }
    }

    // ========================================================= RUN SIMULATION ========================================================

    int tick = 0;

    while(true) {

        ui.printTimeTick(++tick);

        // resort creatures based on their speed/age

        makeCreatureInitiativeOrder(creatures);                 


        // essentially a for loop, but allows for reindexing
        auto iterator = creatures.begin();        

        while (iterator != creatures.end()) {

            Creature * c = (*iterator);

            // creature actions, one at a time based on speed/age, but only if alive

            //c->die();

            if(!c->checkDead()) {
                c->makeDecision(&ui, creatures);
                c->metabolize();
            }





            // end of turn metabolism (leading cause of death)
            
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

        
        input[0] = '\0'; // works because string is null-terminated
        ui.printPrompt("Type \"DETAILS\" to view specific creature information, or anything else to skip.", input);

        if(strncmp("DETAILS", input, 9) == 0) {
            for(Creature * c : creatures) {
                ui.printCreatureInformation(c);
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