#ifndef __CREATURE_H__
#define __CREATURE_H__


#include <vector>
#include "food.h"

// max characters in a creature's name
#define MAX_CREATURE_NAME_LENGTH (256)

// Forward declaration
class Environment;

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
     * @param name species name
     * @param oldAge how old is old for this species?
     * @param speed how fast is the creature to act? (ranked by speed, then age for order of action.)
     */
    Creature(unsigned int totalDurability, unsigned int strength, unsigned int defense, unsigned int stomachCapacity, unsigned int fatCapacity, char const* name, unsigned int oldAge, unsigned int speed);

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

    /**
     * @brief Defines static cast from creature to food
     * 
     * @return Food 
     */
    explicit operator Food() const;

    /**
     * @brief puts food in the creature's stomach
     * 
     * @param food reference to the food being consumed
     */
    void eat(Food & food);

    /**
     * @brief Attack the enemy creature
     * 
     * @param enemy creature to attack
     */
    void fight(Creature & enemy);

    /**
     * @brief move to destination
     * 
     * @param destination 
     */
    void move(Environment & destination);

    /**
     * @brief Lay an egg
     * 
     */
    void egg();


    /**
     * @brief make a decision on what to do.
     * 
     */
    void makeDecision();


    /**
     * @brief Get the Location of the creature
     * 
     * @return Environment* 
     */
    Environment* getLocation();


    // ==================================================== PRIVATE MEMBERS ===========================================================
    private:

    Creature * _species; // pointer to the creature's species model object
    char const _speciesName[MAX_CREATURE_NAME_LENGTH]; // name of the creature


    unsigned int _totalDurability; // equivalent to " max health"
    unsigned int _durability; // equivalent to "health"
    unsigned int _strength; // how good creature is at killing
    unsigned int _defense; // how good creature is at surviving


    unsigned int _age; // number of turns the creature has been alive
    unsigned int _old; // how old is old for this species?
    unsigned int _speed; // how fast this creature is at making a decision (determines initiative)

    // what can the creature eat?
    std::vector<foodType> _edibleFoods;

    Food _stomachFood; // food currently eating
    unsigned int _stomachCapacity; // how large the stomach is
    unsigned int _stomachFillAmount; // how full the creature is
    unsigned int _fat; // fat in creature
    unsigned int _fatCapacity; // total possible fat



    Environment * _location; // pointer to current location
    


};

#endif // #ifndef __CREATURE_H__