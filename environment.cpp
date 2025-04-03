#include "environment.h"
#include "creature.h"

Environment::Environment(std::vector<foodType> const &foodTypes, int abundance) {
    this->_foodTypes = foodTypes;
    this->_foodFactor = abundance;
}

void Environment::setNeighbors(Environment *E1, Environment *E2)
{
    E1->_connections.push_back(E2);
    E2->_connections.push_back(E1);
}
/*
void Environment::updateCreatureList(std::vector<Creature *> creatures)
{
    this->_creatures.clear();
    for(Creature * c : creatures) {
        if(c->getLocation() == this) {
            this->_creatures.push_back(c);
        }
    }
}
*/


std::vector<Environment *> Environment::getConnections() {
    return this->_connections;

}

std::vector<Food *> Environment::getFood() {
    return this->_foods;
}

/*
void Environment::birthACreature(Creature *species) {
    this->_creatures.push_back(new Creature(*species));
}*/
