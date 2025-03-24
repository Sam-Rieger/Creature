#ifndef __CREATURE_H__
#define __CREATURE_H__


#include <vector>
#include "food.h"
#include "environment.h"


class Creature {


    // ==================================================== PUBLIC MEMBERS ===========================================================
    public:

    /**
     * @brief Construct a new Creature object; parameterized constructor, only used to create a species model
     * 
     * @param totalDurability creature's durability
     * @param strength creature's ability to fight
     * @param defense creature's ability to avoid being hurt
     * @param stomachCapacity amount of food creature can hold in stomach
     * @param fatCapacity amount of food creature can store in reserves
     */
    Creature(unsigned int totalDurability, unsigned int strength, unsigned int defense, unsigned int stomachCapacity, unsigned int fatCapacity);


    /**
     * @brief Construct a new Creature object; copy constructor, used to instantiate members of the species
     * 
     * @param species copied object
     */
    Creature(Creature & species);

    /**
     * @brief Copy operator; set all parameters of LHS to RHS's
     * 
     * @param CREATURE copy
     * @return Creature& 
     */
    Creature & operator = (const Creature& CREATURE);

    /**
     * @brief Deconstruct the Creature object
     * 
     */
    ~Creature();

    // ==================================================== PRIVATE MEMBERS ===========================================================
    private:

    Creature * _species; // pointer to the creature's species model object


    unsigned int _totalDurability; // equivalent to " max health"
    unsigned int _durability; // equivalent to "health"
    unsigned int _strength; // how good creature is at killing
    unsigned int _defense; // how good creature is at surviving


    vector<Food> _edibleFoods;

    Food _stomachFood; // food currently eating
    unsigned int _stomachCapacity; // how large the stomach is
    unsigned int _stomachFillAmount; // how full the creature is
    unsigned int _fat; // fat in creature
    unsigned int _fatCapacity; // total possible fat



    Environment * _location; // pointer to current location
    


};

#endif // #ifndef __CREATURE_H__