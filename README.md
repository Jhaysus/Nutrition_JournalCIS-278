# Nutrition_Journal Project

## Student Information
- Jesus Longares

## Implementation details
- With the popularity of food delivery services like GrubHub, users may need help to keep a clear
record of their expenditures and food choices. This application seeks to fill that gap, providing a
dedicated space to maintain and review Grubhub order history. Built using C++, the GrubJournal
will incorporate object-oriented programming, file management, and basic data structures.

C++ concepts and constructs to be used:
-  Classes: Organizing distinct modules such as user, orders, restaurants, and menu items.
- Functions: Distinct operations like adding orders, viewing past orders, and expenditure
summary.
- Loops: For sifting through orders, summing totals, and displaying order lists.
- File handling: For persisting and fetching user data, order records, and restaurant details
- Data Structures: Using vectors to manage list of orders and restaurants.

Fucntionality: 
- User profile management: Personal profile setup with order history.
- Order logging: Manual entry of order details, comprising restaurants name, menu items,
and total expenses.
- Order archive: Fetch and showcase past orders with file operations.
- Expenditure Analysis: Calculates and presents month GrubHub spendings.
- Dietary Review: Demonstrates common orders or favored restaurants based on historical
data.

## Basic commands to compile and run
- compile
```she
g++ -std=c++17 -Wall -Wextra grubJournal.cpp -o grubJournal 
```
- run
```she
 ./grubJournal  
```