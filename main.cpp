#include "HashTable.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;
using namespace std::chrono;

// Function to print colored text
void printColoredText(const string &text, int color) 
{
    cout << "\033[" << color << "m" << text << "\033[0m";
}

int main() 
{
    HashTable shop(17);
    cout << endl;
    printColoredText(">>>>>  Welcome to the Shop Management System!  <<<<<", 35);
    cout << endl;

    auto startTime = system_clock::to_time_t(system_clock::now());
    printColoredText("Current date and time: ", 33);
    cout << put_time(localtime(&startTime), "%F %T") << endl << endl;

    double totalRevenue = 0.0;

    while (true) 
    {
        cout << endl;
        printColoredText("Choose an option: ", 31);
        cout<<endl;
        cout << "1. Add product" << endl;
        cout << "2. Sell product(s)" << endl;
        cout << "3. Check product quantity" << endl;
        cout << "4. Check product price" << endl;
        cout << "5. Display all products" << endl;
        cout << "6. Exit" << endl << endl;

        int choice;
        while (!(cin >> choice) || choice <= 0) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }
        cin.ignore();

        switch (choice) 
        {


            case 1: 
            {
                string name;
                cout << "Enter product name (or 'done' to go to the menu): ";
                getline(cin, name);

                while (name != "done") 
                {
                    int quantity;
                    double price;

                    cout << "Enter product quantity: ";
                    while (!(cin >> quantity) || quantity <= 0) 
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid quantity: ";
                    }

                    cout << "Enter product price: ";
                    while (!(cin >> price) || price <= 0) 
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid price: ";
                    }

                    try 
                    {
                        shop.insert(name, to_string(quantity) + "," + to_string(price));
                        cout << "Product added successfully!" << endl;
                    } 
                    catch (const char* msg) 
                    {
                        cout << msg << endl;
                    }

                    cin.ignore();
                    cout << "Enter product name (or 'done' to go to the menu): ";
                    getline(cin, name);
                }
                break;
            }


            case 2: 
            {
                vector<pair<string, pair<int, double>>> soldItems;
                string name;
                cout << "Enter product name to sell (or 'done' to finish): ";
                getline(cin, name);

                while (name != "done") 
                {
                    try 
                    {
                        string data = shop.retrieve(name);
                        auto delimiterPos = data.find(',');
                        string quantityStr = data.substr(0, delimiterPos);
                        string priceStr = data.substr(delimiterPos + 1);
                        int quantity = stoi(quantityStr);
                        double price = stod(priceStr);

                        int sellQuantity;
                        cout << "Enter quantity to sell: ";
                        while (!(cin >> sellQuantity) || sellQuantity <= 0) 
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid quantity to sell: ";
                        }
                        cin.ignore();

                        if (sellQuantity > quantity) 
                        {
                            cout << "Not enough stock. Available quantity: " << quantity << endl;
                        } 
                        else 
                        {
                            int newQuantity = quantity - sellQuantity;
                            if (newQuantity == 0) 
                            {
                                shop.remove(name);
                                cout << "Product sold out and removed from the inventory." << endl;
                            } 
                            else 
                            {
                                shop.update(name, to_string(newQuantity) + "," + priceStr);
                                cout << "Product sold. Remaining quantity: " << newQuantity << endl;
                            }
                            soldItems.push_back(make_pair(name, make_pair(sellQuantity, price)));
                        }
                    } 
                    catch (const char* msg) 
                    {
                        cout << msg << endl;
                    }

                    cout << "Enter product name to sell (or 'done' to finish): ";
                    getline(cin, name);
                }

                // Print receipt
                double totalAmount = 0;
                cout << endl << "------ Receipt ------" << endl;
                for (size_t i = 0; i < soldItems.size(); ++i) 
                {
                    const string& productName = soldItems[i].first;
                    int soldQuantity = soldItems[i].second.first;
                    double price = soldItems[i].second.second;
                    double amount = soldQuantity * price;
                    totalAmount += amount;
                    totalRevenue += amount;

                    cout << "Product: " << productName << ", Quantity: " << soldQuantity << ", Unit Price: " << price << ", Amount: " << amount << endl;
                }

                cout << "Total Amount: " << totalAmount << endl;
                cout << "---------------------" << endl;
                break;
            }
            case 3: 
            {
                string name;
                cout << "Enter product name to check quantity: ";
                getline(cin, name);

                try 
                {
                    string data = shop.retrieve(name);
                    auto delimiterPos = data.find(',');
                    string quantityStr = data.substr(0, delimiterPos);
                    cout << "Product quantity: " << quantityStr << endl;
                } 
                catch (const char* msg) 
                {
                    cout << msg << endl;
                }
                break;
            }
            case 4: 
            {
                string name;
                cout << "Enter product name to check price: ";
                getline(cin, name);

                try 
                {
                    string data = shop.retrieve(name);
                    auto delimiterPos = data.find(',');
                    string priceStr = data.substr(delimiterPos + 1);
                    cout << "Product price: " << priceStr << endl;
                } 
                catch (const char* msg) 
                {
                    cout << msg << endl;
                }
                break;
            }
            case 5: 
            {
                shop.print();
                break;
            }
            case 6: 
            {
                auto endTime = system_clock::to_time_t(system_clock::now());
                shop.printToFile("products.txt");
                cout << "Total revenue during the session: " << totalRevenue << " RON" << endl;
                cout << "Session ended at: " << put_time(localtime(&endTime), "%F %T") << endl;
                return 0;
            }
            default: 
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}
