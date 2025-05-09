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

    /**
     * @brief Default constructor
     * 
     */
    Food();

    /**
     * @brief Get the Consumed object
     * 
     * @param amount 
     */
    int getConsumed(unsigned int amount);

    foodType getFoodType() const;

    /**
     * @brief Get the amount of food left
     * 
     * @return int 
     */
    int getFoodAmount() const;


    private:
    foodType _type; // what kind of food this food is
    unsigned int _foodAmount; // how much there is
    
};

#endif