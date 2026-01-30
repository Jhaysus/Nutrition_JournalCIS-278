#ifndef ORDER_H
#define ORDER_H
#include "menuItems.hpp"
#include <string>
#include <iostream> 
#include <vector>

/*
    Order definition holds the resturants name, menu items, and cost of the order
*/
class Order
{
public:
    //constructors
    Order():restaurantName("Default"), orderCost(0.0){}

    Order(const std::string& restaurantName, const std::vector<MenuItem>& menuItems,  double& orderCost){
        this->restaurantName = restaurantName;
        this->menuItems = menuItems;
        this->orderCost = orderCost;

    }

    //accessors
    std:: string getRestaurantName() const{
        return restaurantName;
    }
   
    double getOrderCost() const{
        return orderCost;
    }


    std:: vector<MenuItem> getMenuItem() const{
        return menuItems;
    }

    //mutators

    void setRestaurantName(const  std::string& newName){
        restaurantName = newName;
    }

    void setOrderCost( const double& newCost){
        orderCost = newCost;
    }

    void setMenuItem( const std:: vector<MenuItem>& item)
    {
        menuItems = item;

    }
   
   
    //adds a menu Item into the vector
    void addMenuItem(const  MenuItem& item)
    {
        menuItems.push_back(item);
        //adds cost of item

        orderCost += item.getPrice();

    }

    double totalCalories() const{
        double total = 0.0;
        for(  const MenuItem& item : menuItems ){
            total += item.getCalories();
        }

        return total;
    }

    

private:
    std::string restaurantName;
    std::vector<MenuItem> menuItems;
    double orderCost;

};
/*
void Order :: removeMenuItem(const MenuItem & item)
{
    for( std :: vector <MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
    {
        if( *it == item){
            orderCost -= it->getPrice();
            menuItems.erase(it);
            break;
        }
    }
}
*/






#endif 