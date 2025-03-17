#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class HashTable 
{
private:
    struct Element 
    {
        string key;
        string data;
        bool occupied;

        Element() 
        {
            key = "";              
            data = "";              
            occupied = false;       
        }
    };

    vector<Element> table;
    int size;
    int capacity;

    int hash(const string&) const;
    int probe(int, int) const;
    void rehash(int);

public:
    HashTable(int capacity = 17);
    void insert(const string&, const string&);
    void remove(const string&);
    string search(const string&) const;
    void update(const string&, const string&);
    string retrieve(const string&) const;
    void print() const;
    void printToFile(const string&) const;
    int getSize() const;
};

#endif
