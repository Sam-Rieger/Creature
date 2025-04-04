#ifndef __UI_H__
#define __UI_H__

#include "creature.h"



class UI {
    public:

    /**
     * @brief Construct a new UI object
     * 
     */
    UI();

    /**
     * @brief Prints details about a particular creature
     * 
     * @param c 
     */
    void printCreatureInformation(Creature * const & c) const;

    void printAction(char * message) const;

    void printDeath(Creature * const & c) const;

    private:
    // colors
    static char constexpr _default[] = "\033[0m";
    static char constexpr _red[] = "\033[31m";
    static char constexpr _green[] = "\033[32m";
    static char constexpr _blue[] = "\033[34m";
};


#endif