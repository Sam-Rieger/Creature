#include "creature.h"
#include "environment.h"
#include "ui.h"
#include <cstring>
#include <algorithm>


Environment * Creature::getLocation()
{
    return this->_location;
}

void Creature::setLocation(Environment *location)
{
    this->_location = location;
}

void Creature::metabolize()
{

    if(this->_age > this->_old) {
        this->_durability -= (unsigned int) (this->_totalDurability * 0.25);
    }

    if(this->_durability <= 0) {
        this->die();
    }
    if((unsigned) this->_stomachFood.getFoodAmount() > this->_metabolism) {
        this->_fat += (this->_stomachFood.getFoodAmount() - this->_metabolism);
        if(this->_fat > this->_fatCapacity) {
            this->_fat = this->_fatCapacity;
        }
    } else if(this->_stomachFood.getFoodAmount() + this->_fat > this->_metabolism) {
        // yes, I do realize this is the same operation as above.  this is for expandability, more than anything
        this->_fat -= (this->_metabolism - this->_stomachFood.getFoodAmount()); 
    } else {
        this->die();
    }

    ++_age;
    
}

bool Creature::checkDead()
{
    return _dead;
}

void Creature::die()
{
    this->_dead = true;
}

int Creature::getSpeed() const {
    return this->_speed;
}

int Creature::getAge() const {
    return this->_age;
}

void Creature::getName(char (& output)[MAX_CREATURE_NAME_LENGTH + 1]) const
{
    strcpy(output, this->_speciesName);
}

bool Creature::operator < (Creature const &c)
{
    if(this->getSpeed() == c.getSpeed()) {
        return(this->getAge() > c.getAge());
    } else {
        return(this->getSpeed() < c.getSpeed());
    }
}

Creature::Creature(unsigned int totalDurability, unsigned int strength, unsigned int defense, unsigned int stomachCapacity, 
unsigned int fatCapacity, char const *name, unsigned int oldAge, unsigned int speed, std::vector<foodType> edibleFoods, unsigned int metabolism) {

    this->_speciesName[0] = '\0';

    this->_totalDurability = totalDurability;
    this->_strength = strength;
    this->_defense = defense;
    this->_stomachCapacity = stomachCapacity;
    this->_fatCapacity = fatCapacity;
    strncpy(this->_speciesName, name, MAX_CREATURE_NAME_LENGTH);
    this->_old = oldAge;
    this->_speed = speed;
    this->_edibleFoods = edibleFoods;
    this->_metabolism = metabolism;

    this->_age = 999;
    



}

Creature::Creature(Creature &species) {

    // set progenitor species
    this->_species = &species;


    this->_totalDurability = species._totalDurability;
    this->_strength = species._strength;
    this->_defense = species._defense;
    this->_stomachCapacity = species._stomachCapacity;
    this->_fatCapacity = species._fatCapacity;
    strcpy(this->_speciesName, species._speciesName);
    this->_old = species._old;
    this->_speed = species._speed;
    this->_edibleFoods = species._edibleFoods;

    
    // set up other values
    this->_durability = this->_totalDurability;
    this->_age = 0;
    this->_location = nullptr;

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

    return *this;
}

Creature::~Creature(){
    // no special implementation needed, just satisfying big 3 (no DMM, but did define copy constructor and I don't wanna fight for points)
}

Creature::operator Food() const
{
    return Food(this->_fat, foodType::softMeat);
}

void Creature::eat(Food * food)
{
    this->_stomachFood = Food(food->getConsumed(this->_stomachCapacity), food->getFoodType());
}

void Creature::hunt(Creature * enemy) {

    if(this->_strength > enemy->_defense) {
        enemy->die();
    } else {
        enemy->die();
        this->loseHealth(enemy->_defense - _strength);
    }


}

void Creature::loseHealth(unsigned int amount) {
    if(amount < this->_durability) {
        this->_durability -= amount;
    } else {
        this->die();
    }
}

void Creature::move(Environment &destination)
{
    if(this->_location == nullptr) {
        // the location is being set for the first time
    } else {
        // 10 is a placeholder, extended creatures could have different abilities to traverse terrain. keeping it simple for now.
        expendEnergy(10);
    }

    this->_location = &destination;

}

void Creature::expendEnergy(unsigned int energy)
{
    energy -= _stomachFood.getConsumed(energy);

    if(_fat < energy) {
        this->die();
    } else {
        _fat -= energy;
    }
}

void Creature::egg() {
    // laying eggs is hard.  this provides for death during childbirth, too.
    expendEnergy(35);
//    return Creature(*this->_species);

}

int Creature::makeDecision(UI * ui, std::vector<Creature*> & creatures) {

    // first, check if it can reproduce?

    if(_fat + _stomachFood.getFoodAmount() > 35 + _metabolism) {
        this->egg();
        ui->printAction(this, "Lays an egg");
        return 1;
    }
    // next, will look for food within this region
    for(foodType ft : _edibleFoods) {
       for(Food *&f : _location->getFood()) {
            if(ft == f->getFoodType()) {
                // can eat
                if(f->getFoodAmount() > this->_metabolism) {
                    // worth spending a turn eating
                    this->eat(f);
                    ui->printEatingAction(this, f);
                    return 0;
                }
            }
       }
    }

    if(std::find(_edibleFoods.begin(), _edibleFoods.end(), foodType::softMeat) != _edibleFoods.end()) {
        //predator!
        for(Creature * c : creatures) {
            if(c->getLocation() == this->_location) {
                this->hunt(c);
                ui->printFightingAction(this, c);
            }
        }
    }

    






    return 0;
}

void makeCreatureInitiativeOrder(std::vector<Creature *> &creatures)
{
    std::sort(creatures.begin(), creatures.end());
}
