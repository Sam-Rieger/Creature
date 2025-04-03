#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <vector>

class Environment {
    public:

    /**
     * @brief Updates the environment's local list of creatures from the universal one.
     * 
     * @param creatures 
     */
    void updateCreatureList(std::vector<Creature*> creatures);

    

    private:
    std::vector<Environment*> _connections; // environemnts connected to this one
    std::vector<Creature*> _creatures; // who is living here
    std::vector<Food> _foodTypes; // what food grows here
    unsigned double _foodFactor; // what food there is

};

#endif