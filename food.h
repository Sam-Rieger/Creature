#ifndef __FOOD_H__
#define __FOOD_H__

/**
 * @brief type of food
 * 
 */
enum foodType {
    meat = 1,
    veggie = 0
};

class Food {
    public:

    private:
    foodType _type;
    unsigned int _foodAmount;
    
};

#endif