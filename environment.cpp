#include "environment.h"

void Environment::updateCreatureList(std::vector<Creature *> creatures)
{
    this->_creatures.clear();
    for(Creature * c : creatures) {
        if(c->_location == this) {
            this->_creatures.push_back(c);
        }
    }
}
