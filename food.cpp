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
