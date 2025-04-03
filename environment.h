#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <vector>
#include "food.h"

// Forward declaration
class Creature;

class Environment {
    public:

    /**
     * @brief Construct a new Environment object
     * 
     * @param foodTypes what grows here
     * @param abundance how much
     */
    Environment(std::vector<foodType> const & foodTypes, int abundance);

    /**
     * @brief Makes E1 and E2 connected
     * 
     * @param E 
     */
    static void setNeighbors(Environment * E1, Environment * E2);

    /**
     * @brief Updates the environment's creatures (dead/moved)
     * 
     */
    void updateCreatureList();

    /**
     * @brief gets rid of eaten food from the environment, grows more.
     * 
     */
    void updateFoodList();

    /**
     * @brief Get the connected environments
     * 
     * @return std::vector<Environment*> 
     */
    std::vector<Environment*> getConnections();

    /**
     * @brief Get the Food pointers in this environment
     * 
     * @return std::vector<Food *> the food
     */
    std::vector<Food *> getFood();

    /**
     * @brief birth, as it says, a creature
     * 
     * @param species the species to enbirthinate
     */
    void birthACreature(Creature * species);

    

    private:
    std::vector<Environment*> _connections; // environemnts connected to this one
    //std::vector<Creature*> _creatures; // who is living here
    std::vector<foodType> _foodTypes; // what food grows here
    std::vector<Food *> _foods; // pointers to all the foods here
    int _foodFactor; // abundance of food (growth rate per turn)


};

#endif