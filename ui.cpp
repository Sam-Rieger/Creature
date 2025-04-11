#include "ui.h"
#include "creature.h"
#include "environment.h"
#include "food.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::cin;


UI::UI() {
    // nothing to construct, really.  This framework could be used for custom UI options ins the future.
}

void UI::printCreatureInformation(Creature * const c) const {
    cout << "Creature information here" << endl;
}

void UI::printAction(Creature * c, char const * message) const {

    char name[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};
    c->getName(name);

    cout << _yellow << "ACTION: " << _default << "Creature of species " << _blue << name << _default << " " << message << _default << endl;
}

void UI::printEatingAction(Creature * c, Food * food) {

    static char const foods[][MAX_CREATURE_NAME_LENGTH] = {"Tough Meat", "Soft Meat", "Veggie 1", "Veggie 2", "Veggie 3"};

    char name[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};
    c->getName(name);

    char locationName[MAX_ENVIRONMENT_NAME_LENGTH] = {'\0'};
    c->getLocation()->getName(locationName);

    cout << _yellow << "ACTION: " << _default << "Creature of species " << _blue << name << _default << " Eats a food of type " << _green << foods[(int) food->getFoodType()] 
    << _default << " in " << _green << locationName << _default << endl;

}

void UI::printFightingAction(Creature * c1, Creature * c2) {

    char name1[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};
    c1->getName(name1);

    char name2[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};
    c2->getName(name2);

    char locationName[MAX_ENVIRONMENT_NAME_LENGTH] = {'\0'};
    c1->getLocation()->getName(locationName);


    cout << _yellow << "ACTION: " << _default << "Creature of species " << _blue << name1 << _default << " hunts creature of species " << _blue << name2 << _default 
    << " in " << _green << locationName << _default << endl;
}

void UI::printDeath(Creature * const c) const {

    char name[MAX_CREATURE_NAME_LENGTH + 1] = {'\0'};
    c->getName(name);

    char locationName[MAX_ENVIRONMENT_NAME_LENGTH] = {'\0'};
    c->getLocation()->getName(locationName);

    cout << _red << "DEATH:" << _default << " Creature of species " << _blue << name << _default << " has died in " << _green << locationName
    << _default << " at age " << _green << c->getAge() << endl;

}

void UI::printPrompt(char const * prompt, char (& output)[MAX_INPUT_LENGTH + 1]) const
{
    cout << _magenta << "PROMPT: " << _default << prompt << ": " << _default;

    char input[MAX_INPUT_LENGTH + 1];

    cin >> input;

    strncpy(output, input, MAX_INPUT_LENGTH);
}

void UI::printTimeTick(unsigned int tick) {

    cout << _green << "YEAR: " << _default << " it is currently year " << _blue << tick << _default << endl;

}
