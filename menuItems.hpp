#ifndef MENUITEM_H
#define MENUITEM_H
#include <string>
#include <iostream> 

/*
Menu Item class will hold Dish Name and Price of the item

*/
class MenuItem
{
public:
    //constructors
    MenuItem() : dishName("Default"), price(0.0), calories(0.0){}

    MenuItem(const std::string& dishName, double& price, double& calories)
    {
        this->dishName = dishName;
        this->price = price;
        this->calories = calories;
    }

    //Accessors
    std::string getDishName() const
    {
        return dishName;
    }

    double getPrice() const
    {
        return price;

    }

    double getCalories() const
    {
        return calories;
    }

    //Mutators
    void setDishName(std::string& newDishName)
    {
        dishName = newDishName;
    }

    void setPrice( double & newPrice)
    {
        price = newPrice;
    }

    void setCalories( double& newCalories)
    {
        calories = newCalories; 
    }

private:
    std::string dishName;

    double price;

    double calories;
    

};






#endif 