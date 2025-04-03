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
    /**
     * @brief Construct a new Food object
     * 
     * @param amount amount of food this food has
     * @param type type of food
     */
    Food(int amount, foodType type);

    
    private:
    foodType _type;
    unsigned int _foodAmount;
    
};

#endif