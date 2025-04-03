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
    Environment(std::vector<foodType> const & foodTypes, double abundance);

    /**
     * @brief Makes E1 and E2 connected
     * 
     * @param E 
     */
    static void setNeighbors(Environment * E1, Environment * E2);

    /**
     * @brief Updates the environment's local list of creatures from the universal one.
     * 
     * @param creatures 
     */
    void updateCreatureList(std::vector<Creature*> creatures);

    /**
     * @brief Get the connected environments
     * 
     * @return std::vector<Environment*> 
     */
    std::vector<Environment*> getConnections();

    

    private:
    std::vector<Environment*> _connections; // environemnts connected to this one
    std::vector<Creature*> _creatures; // who is living here
    std::vector<foodType> _foodTypes; // what food grows here
    double _foodFactor; // abundance of food (growth rate per turn)


};

#endif