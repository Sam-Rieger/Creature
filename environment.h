#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <vector>
#include "food.h"

#define MAX_ENVIRONMENT_NAME_LENGTH (64)


// Forward declaration
class Creature;


class Environment {
    public:

    /**
     * @brief Construct a new Environment object
     * 
     * @param foodTypes what grows here
     * @param abundance how much of it does
     * @param name what this place is called
     */
    Environment(std::vector<foodType> const & foodTypes, int abundance, char const * name);

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
     * @brief Get the name of this location
     * 
     * @param output location to send the string
     * 
     */
    void getName(char (& output)[MAX_ENVIRONMENT_NAME_LENGTH]) const;

    private:
    std::vector<Environment*> _connections; // environemnts connected to this one
    //std::vector<Creature*> _creatures; // who is living here
    std::vector<foodType> _foodTypes; // what food grows here
    std::vector<Food *> _foods; // pointers to all the foods here
    int _foodFactor; // abundance of food (growth rate per turn)
    char _name[MAX_ENVIRONMENT_NAME_LENGTH]; // name

};

#endif