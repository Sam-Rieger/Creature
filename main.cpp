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

int main() {

    // All of the following is extensible, just limited to this specific world to avoid scope creep.


    
    // =============================================== SETUP ENVIRONMENT ======================================================

    

    Environment Forest1(std::vector<foodType>(veggie1, veggie2), 1.);
    Environment Forest2(std::vector<foodType>(veggie1, veggie2), 0.8);

    Environment Mountains(std::vector<foodType>(veggie3, veggie2), 0.4);

    Environment Desert(std::vector<foodType>(veggie3), 0.1);

    Environment Grassland1(std::vector<foodType>(veggie1, veggie2), 1.4);
    Environment Grassland2(std::vector<foodType>(veggie1, veggie2), 1.3);

    Environment Oasis({veggie1, veggie2, veggie3}, 2);

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

    // ====================================================== SETUP SPECIES =====================================================
    

    // ===================================================== RUN SIMULATION =====================================================

}