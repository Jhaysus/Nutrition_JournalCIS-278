#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include "menuItems.hpp"
#include "order.hpp"
#include "user.hpp"

struct UserInfo
{
    std::string userName;
    std::string password;
    std::vector<Order> userVector;
};

const int MAX_USERS = 20;
UserInfo users[MAX_USERS];

int totalUsers = 0; // Keeps track of the number of users

// prints menu for the user to enter into the swtich statement

void printMenu()
{
    std::cout << "|----------------------------------------------|" << std::endl;
    std::cout << "|          Display Menu:                       |" << std::endl;
    std::cout << "|      1: Register/Login to profile            |" << std::endl;
    std::cout << "|      2: Log new Order                        |" << std::endl;
    std::cout << "|      3: Review order history                 |" << std::endl;
    std::cout << "|      4: Financial Analysis                   |" << std::endl;
    std::cout << "|      5: Dietary Review                       |" << std::endl;
    std::cout << "|      6: Delete Order                         |" << std::endl;
    std::cout << "|      7: Exit                                 |" << std::endl;
    std::cout << "|----------------------------------------------|" << std::endl;
}

// Registers new User
void registerUser()
{
    if (totalUsers >= MAX_USERS)
    {
        std::cout << "User limit reached! Can't register more users." << std::endl;
        return;
    }

    // create new user
    UserInfo newUser;

    std::cout << "Enter new username: ";
    std::cin >> newUser.userName;

    // Check if username already exists
    for (int i = 0; i < totalUsers; i++)
    {
        if (users[i].userName == newUser.userName)
        {
            std::cout << "Username already exists! Please choose another." << std::endl;
            return;
        }
    }

    std::cout << "Enter password: ";
    std::cin >> newUser.password;

    users[totalUsers] = newUser;
    totalUsers++;

    std::cout << "Registration successful!" << std::endl;
}

// Login existing user
int loginUser()
{

    // create loginUser using struct
    UserInfo loginUser;

    std::cout << "Enter username: ";
    std::cin >> loginUser.userName;

    std::cout << "Enter password: ";
    std::cin >> loginUser.password;

    // Check if the user exists and the password matches
    for (int i = 0; i < totalUsers; i++)
    {
        if (users[i].userName == loginUser.userName && users[i].password == loginUser.password)
        {
            std::cout << "Login successful!" << std::endl;
            return i;
        }
    }

    std::cout << "Incorrect username or password!" << std::endl;
    return -1;
}

void logNewOrder(int userIndex)
{
    if (userIndex == -1)
    {
        std::cout << "Please login first!" << std::endl;
        return;
    }

    std::string restaurantName;
    std::cout << "Enter the restaurant's name: ";
    std::cin.ignore();                      // Clear any input
    std::getline(std::cin, restaurantName); // multi-word input

    Order newOrder;
    newOrder.setRestaurantName(restaurantName);

    while (true)
    {
        std::cout << "Do you want to add a menu item to this order? (y/n) ";
        char choice;
        std::cin >> choice;
        if (choice == 'n' || choice == 'N')
        {
            break;
        }

        std::string dishName;
        double price;
        double cal;

        std::cout << "Enter the dish name: ";
        std::cin.ignore();
        std::getline(std::cin, dishName);

        std::cout << "Enter the dish price: ";
        std::cin >> price;

        std::cout << "Enter the dish calories: ";
        std::cin >> cal;

        MenuItem item(dishName, price, cal);
        newOrder.addMenuItem(item);
    }

    users[userIndex].userVector.push_back(newOrder);
    std::cout << "Order added successfully!" << std::endl;
}

void userHistory(int userIndex)
{
    if (userIndex == -1)
    {
        std::cout << "Please login first!" << std::endl;
        return;
    }

    std::vector<Order> orders = users[userIndex].userVector;
    if (orders.empty())
    {
        std::cout << "You have no orders in your history." << std::endl;
        return;
    }

    for (const Order &order : orders)
    {
        std::cout << "\nRestaurant: " << order.getRestaurantName() << std::endl;

        std::vector<MenuItem> items = order.getMenuItem();
        std::cout << "Items:" << std::endl;
        for (const MenuItem &item : items)
        {
            std::cout << "- " << item.getDishName() << std::endl;
        }
    }
}

// first checks user for their existence. List entire cost of food
void userFinacialHistory(int userIndex)
{
    if (userIndex == -1)
    {
        std::cout << "Please login first!" << std::endl;
        return;
    }

    std::vector<Order> orders = users[userIndex].userVector;

    if (orders.empty())
    {
        std::cout << "You have no orders in your history." << std::endl;
        return;
    }

    // goes through dietary Journal of food ordered
    std::cout << "Order History:" << std::endl;

    for (const Order &order : orders)
    {
        std::cout << "\nRestaurant: " << order.getRestaurantName() << std::endl;
        std::cout << "Total Cost: $" << order.getOrderCost() << std::endl;

        std::vector<MenuItem> items = order.getMenuItem();
        std::cout << "Items:" << std::endl;
        for (const MenuItem &item : items)
        {
            std::cout << "- " << item.getDishName() << ": $" << item.getPrice() << std::endl;
        }
    }
}

// returns the whole calories
void userDiet(int userIndex)
{
    if (userIndex == -1)
    {
        std::cout << "Please login first!" << std::endl;
        return;
    }

    std::vector<Order> orders = users[userIndex].userVector;

    if (orders.empty())
    {
        std::cout << "You have no orders in your history." << std::endl;
        return;
    }

    // goes through dietary Journal of food ordered
    std::cout << "Order Calorie History:" << std::endl;
    for (const Order &order : orders)
    {
        std::cout << "\nRestaurant: " << order.getRestaurantName() << std::endl;
        std::cout << "Total Calories: " << order.totalCalories() << std::endl;

        std::vector<MenuItem> items = order.getMenuItem();
        std::cout << "Items:" << std::endl;
        for (const MenuItem &item : items)
        {
            std::cout << "- " << item.getDishName() << ": " << item.getCalories() << " cal" << std::endl;
        }
    }
}

// delete an order
void deleteOrder(int userIndex)
{
    if (userIndex == -1)
    {
        std::cout << "Please login first!" << std::endl;
        return;
    }

    std::vector<Order> orders = users[userIndex].userVector;

    if (orders.empty())
    {
        std::cout << "You have no orders in your history." << std::endl;
        return;
    }
    // first shows the orders in number order
    std::cout << "Your orders:" << std::endl;
    for (size_t index = 0; index < orders.size(); index++)
    {
        std::cout << index + 1 << ". " << orders[index].getRestaurantName() << std::endl;
    }

    // let user decied which they want to delete
    int choice;
    std::cout << "Enter the number of the order you wish to remove" << std::endl;
    std::cin >> choice;

    if (choice > 0 && static_cast<size_t>(choice) <= orders.size())
    {
        users[userIndex].userVector.erase(users[userIndex].userVector.begin() + choice - 1);
        std::cout << "Order Deleted" << std::endl;
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
    }
}

void menu()
{
    User user; // An instance of the User class
    int choice;
    int userIndex = -1;

    do
    {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            int subChoice;
            std::cout << "Enter your choice:" << std::endl;
            std::cout << "1. Register" << std::endl;
            std::cout << "2. Login" << std::endl;
            std::cin >> subChoice;

            if (subChoice == 1)
            {
                registerUser();
            }
            else if (subChoice == 2)
            {
                userIndex = loginUser();
                if (userIndex != -1)
                {
                    std::cout << "Logged in successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Login failed." << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid option!" << std::endl;
            }
            break;

        case 2:
            logNewOrder(userIndex);
            break;

        case 3:
            // review order history

            userHistory(userIndex);
            break;

        case 4:
            // for financial analysis
            userFinacialHistory(userIndex);
            break;

        case 5:
            // for dietary review
            userDiet(userIndex);
            break;

        case 6:
            // deletes an order
            deleteOrder(userIndex);
            break;

        case 7:
            std::cout << "\n\n************************************" << std::endl;
            std::cout << "   Exiting the program. Goodbye!" << std::endl;
            std::cout << "************************************\n\n"
                      << std::endl;

            break;

        default:
            std::cout << "\n\n*********************************************" << std::endl;

            std::cout << "Invalid choice! Please select a valid option." << std::endl;

            std::cout << "*********************************************\n\n"
                      << std::endl;

            break;
        }
    } while (choice != 7);
}

void saveUserData()
{
    std::ofstream outFile("userData.txt");

    if (!outFile)
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    outFile << totalUsers << std::endl;
    for (int i = 0; i < totalUsers; i++)
    {
        outFile << users[i].userName << " " << users[i].password << std::endl;

        // Save orders for this user
        const std::vector<Order> &orders = users[i].userVector; // Get user's orders as a constant reference
        outFile << orders.size() << std::endl;                  // Save the number of orders
        for (const Order &order : orders)
        {
            outFile << order.getRestaurantName() << " " << order.getOrderCost() << std::endl;

            // Save menu items for this order
            const std::vector<MenuItem> &menuItems = order.getMenuItem(); // Get order's menu items as a constant reference
            outFile << menuItems.size() << std::endl;                     // Save the number of menu items
            for (const MenuItem &item : menuItems)
            {
                outFile << item.getDishName() << " " << item.getPrice() << " " << item.getCalories() << std::endl;
            }
        }
    }

    outFile.close();
}

void loadUserData()
{
    std::ifstream inFile("userData.txt");

    if (!inFile)
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    inFile >> totalUsers;
    for (int i = 0; i < totalUsers; i++)
    {
        inFile >> users[i].userName >> users[i].password;

        // Load orders for this user
        int orderCount;
        inFile >> orderCount;
        for (int j = 0; j < orderCount; j++)
        {
            Order order;
            std::string restaurantName;
            double orderCost;

            inFile >> restaurantName >> orderCost;
            order.setRestaurantName(restaurantName);
            order.setOrderCost(orderCost);

            // Load menu items for this order
            int menuItemCount;
            inFile >> menuItemCount;
            for (int k = 0; k < menuItemCount; k++)
            {
                MenuItem item;
                std::string dishName;
                double price, calories;

                inFile >> dishName >> price >> calories;
                item.setDishName(dishName);
                item.setPrice(price);
                item.setCalories(calories);

                order.addMenuItem(item);
            }

            users[i].userVector.push_back(order);
        }
    }

    inFile.close();
}

int main()
{
    // loads data from file
    loadUserData();

    // dislpays menu and user operations
    menu();

    // saves data
    saveUserData();

    return 0;
}
