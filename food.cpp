#include "food.h"

Food::Food(int amount, foodType type) {
    this->_foodAmount = amount;
    this->_type = type;
}

Food::Food()
{
    this->_foodAmount = 20;
    this->_type = foodType::softMeat;
}

int Food::getConsumed(unsigned int amount)
{
    if(amount > this->_foodAmount) {
        this->_foodAmount = 0;
        return this->_foodAmount;
    } else {
        this->_foodAmount -= amount;
        return amount;
    }
}

foodType Food::getFoodType() const {
    return this->_type;
}

int Food::getFoodAmount() const {
    return this->_foodAmount;
}
