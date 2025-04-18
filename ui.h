#ifndef __UI_H__
#define __UI_H__

//#include "creature.h"

class Creature;
class Food;

// largest cin input allowed
#define MAX_INPUT_LENGTH (64)

// largest allowed length of text for prompt
#define MAX_PROMPT_LENGTH (512)

// max characters in a creature's name
#define MAX_CREATURE_NAME_LENGTH (32)


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
    void printCreatureInformation(Creature * const c) const;

    /**
     * @brief Formats an action message as an event
     * 
     * @param c creature doing ction
     * @param message what the creature is doing
     */
    void printAction(Creature * c, char const * message) const;

    /**
     * @brief prints that a creature is eating a food
     * 
     * @param c creature
     * @param food food
     */
    void printEatingAction(Creature * c, Food * food);

    /**
     * @brief prints that creature 1 is fighting creature 2
     * 
     * @param c1 
     * @param c2 
     */
    void printFightingAction(Creature * c1, Creature * c2);

    /**
     * @brief Displays an obituary for the creature pointed to by c
     * 
     * @param c the one who was lost
     */
    void printDeath(Creature * const  c) const;

    /**
     * @brief Prompts the user, fills in a referenced string with the response.
     * 
     * @param prompt what to prompt the user
     * @param output location for return string
     */
    void printPrompt(char const * prompt, char (& output)[MAX_INPUT_LENGTH + 1]) const;

    void printPopulation(Creature * const  c, int population);

    /**
     * @brief Prints current date
     * 
     */
    void printTimeTick(unsigned int tick);

    private:
    // colors
    static char constexpr _default[] = "\033[0m"; // normal text
    static char constexpr _red[] = "\033[31m"; // DEATH
    static char constexpr _green[] = "\033[32m"; // values of attributes/location names
    static char constexpr _blue[] = "\033[34m"; // species identifier
    static char constexpr _yellow[] = "\033[33m"; // for creature actions
    static char constexpr _magenta[] = "\033[35m"; // for user inputs
    


};


#endif