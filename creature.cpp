#include "creature.h"
#include "environment.h"
#include <cstring>


Environment * Creature::getLocation()
{
    return this->_location;
}

Creature::Creature(unsigned int totalDurability, unsigned int strength, unsigned int defense, unsigned int stomachCapacity, 
unsigned int fatCapacity, char const *name, unsigned int oldAge, unsigned int speed, std::vector<foodType> edibleFoods) {

    this->_totalDurability = totalDurability;
    this->_strength = strength;
    this->_defense = defense;
    this->_stomachCapacity = stomachCapacity;
    this->_fatCapacity = fatCapacity;
    strncpy(this->_speciesName, name, MAX_CREATURE_NAME_LENGTH);
    this->_old = oldAge;
    this->_speed = speed;


}

Creature::Creature(Creature &species) {

    this->_totalDurability = species._totalDurability;
    this->_strength = species._strength;
    this->_defense = species._defense;
    this->_stomachCapacity = species._stomachCapacity;
    this->_fatCapacity = species._fatCapacity;
    strncpy(this->_speciesName, species._speciesName, MAX_CREATURE_NAME_LENGTH);
    this->_old = species._old;
    this->_speed = species._speed;

    // set progenitor species
    this->_species = &species;

}

Creature &Creature::operator=(Creature const &CREATURE)
{
    this->_totalDurability = CREATURE._totalDurability;
    this->_strength = CREATURE._strength;
    this->_defense = CREATURE._defense;
    this->_stomachCapacity = CREATURE._stomachCapacity;
    this->_fatCapacity = CREATURE._fatCapacity;
    strncpy(this->_speciesName, CREATURE._speciesName, MAX_CREATURE_NAME_LENGTH);
    this->_old = CREATURE._old;
    this->_speed = CREATURE._speed;
}

Creature::~Creature(){
    // no other implementation needed, just satisfying big 3
}
