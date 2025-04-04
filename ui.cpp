#include "ui.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;


UI::UI() {
    // nothing to construct, really.  This framework could be used for custom UI options ins the future.
}

void UI::printAction(Creature *& c, char * const message) const
{

    char name[MAX_CREATURE_NAME_LENGTH] = {};
    c->getName(name);

    cout << _yellow << "ACTION: Creature of species " << _blue << name << _yellow << " " << message << _default << endl;
}

void UI::printDeath(Creature * const & c) const
{

    char name[MAX_CREATURE_NAME_LENGTH] = {};
    c->getName(name);

    cout << _red << "DEATH: Creature of species " << _blue << name << _red << " has died in " << _green << " [LOCATION HERE] "
    << _red << " at age " << _green << c->getAge() << endl;

}

void UI::printPrompt(char * const prompt, char (& output)[MAX_INPUT_LENGTH + 1]) const
{
    cout << _magenta << "PROMPT: " << prompt << ": " << _default;

    char input[MAX_INPUT_LENGTH + 1];

    cin >> input;

    strncpy(output, input, MAX_INPUT_LENGTH);
}
