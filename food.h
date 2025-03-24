#ifndef __FOOD_H__
#define __FOOD_H__

/**
 * @brief type of food
 * 
 */
enum foodType {
    toughMeat,
    softMeat,
    veggie1,
    veggie2,
    veggie3

};

class Food {
    public:

    private:
    foodType _type;
    unsigned int _foodAmount;
    
};

#endif