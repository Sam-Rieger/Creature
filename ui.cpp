#include "ui.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;


UI::UI() {
    // nothing to construct, really.  This framework could be used for custom UI options ins the future.
}

void UI::printAction(char * const message) const
{
    cout << _yellow << "Action: " << _default << message << endl;
}

void UI::printDeath(Creature * const & c) const
{

    cout << _red << "Creature of species " << _blue << " [SPECIES HERE] " << _red << " has died in " << _green << " [LOCATION HERE] "
    << _red << " at age " << _green << c->getAge() << endl;

}

void UI::printPrompt(char * const prompt, char (& output)[MAX_INPUT_LENGTH + 1]) const
{
    cout << _magenta << prompt << ": " << _default;

    char input[MAX_INPUT_LENGTH + 1];

    cin >> input;

    strncpy(output, input, MAX_INPUT_LENGTH);
}
