#ifndef __UI_H__
#define __UI_H__

#include "creature.h"



class UI {
    public:

    UI();

    void printCreatureInformation(Creature);

    void printAction();

    void printDeath();

    private:
    // colors
    static char constexpr _default[] = "\033[0m";
    static char constexpr _red[] = "\033[31m";
    static char constexpr _green[] = "\033[32m";
    static char constexpr _blue[] = "\033[34m";
};


#endif