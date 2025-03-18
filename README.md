# shop_management_system

## Overview

This project is a simple Shop Management System implemented in C++ using a hash table. The system allows users to add products, sell products, check product details, display all products, and track total revenue. The hash table is implemented using quadratic probing to handle collisions and dynamically resizes as needed.

## Compilation

```
g++ main.cpp HashTable.h HashTable.cpp -o p

```
## Running the program
```
./p
```

## Usage
Upon running the program, you will be presented with a menu to:

1. Add a product
2. Sell a product
3. Check product quantity
4. Check product price
5. Display all products
6. Exit and save data to a file

Follow the on-screen prompts to perform the desired operations.

## Data Storage
Product data is stored in a hash table during runtime.
When the program exits, data is saved to products.txt.