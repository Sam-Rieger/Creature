#include "environment.h"
#include "creature.h"

void Environment::updateCreatureList(std::vector<Creature *> creatures)
{
    this->_creatures.clear();
    for(Creature * c : creatures) {
        if(c->getLocation() == this) {
            this->_creatures.push_back(c);
        }
    }
}
