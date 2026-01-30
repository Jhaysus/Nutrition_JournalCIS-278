#ifndef USER_H
#define USER_H
#include <string>
#include <iostream> 
#include "menuItems.hpp"
#include "order.hpp"


/*
This is the user profile for the orders. It will keep track of:
    -username
*/
class User
{
public:
    //constuctor
    User(){}
    User(const std::string& userName)
    {
        this->userName = userName;
    }
    //Accessors
    std:: string getUserName() const
    {
        return userName;
    }

    std:: vector<Order> getOrders() const{
        return Orders;
    }

    //Mutators
    void setUserName(const  std::string& newUserName){
        userName = newUserName;
    }
    void setOrder( const std:: vector<Order>& item)
    {
        Orders = item;

    }



    //other methods
    void addOrder(const Order& order){
        Orders.push_back(order);
    }

    void removeOrder( int index);

    double totalSpent()const;


private:
    std::string userName;
    std::vector<Order>Orders;
    

};

void User::removeOrder(int index)
{
    if( static_cast<size_t>(index) < Orders.size())
    {
        Orders.erase(Orders.begin() + index );
    }

}

double User :: totalSpent()const{
    double total = 0.0;

    for(const auto & order : Orders){
        total+= order.getOrderCost();
    }

    return total;
}






#endif 
