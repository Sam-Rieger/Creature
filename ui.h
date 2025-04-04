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

    /**
     * @brief Formats an action message as an event
     * 
     * @param message 
     */
    void printAction(char * const message) const;

    /**
     * @brief Displays an obituary for the creature pointed to by c
     * 
     * @param c the one who was lost
     */
    void printDeath(Creature * const & c) const;

    /**
     * @brief prints the prompt as a prompt
     * 
     * @param prompt 
     */
    void printPrompt(char * const prompt) const;

    private:
    // colors
    static char constexpr _default[] = "\033[0m";
    static char constexpr _red[] = "\033[31m";
    static char constexpr _green[] = "\033[32m";
    static char constexpr _blue[] = "\033[34m";
    static char constexpr _yellow[] = "\033[33m";

};


#endif