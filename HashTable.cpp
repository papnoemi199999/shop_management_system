#include "HashTable.h"

// Initializes the hash table with a given capacity
HashTable::HashTable(int capacity) 
{
    size = 0;
    this->capacity = capacity;
    table.resize(capacity);
}

//  Generates a hash value for the given key
int HashTable::hash(const string &key) const 
{ 
    int hash_value = 0;
    for (int i = 0; i < key.length(); ++i) 
    {
        hash_value = (hash_value * 31 + key[i]) % capacity;
    }
    return hash_value;
}


// Uses quadratic probing to resolve collisions
int HashTable::probe(int index, int i) const 
{  
    return (index + i * i) % capacity;
}

// Resizes and rehashes all elements into a new table with a larger capacity
void HashTable::rehash(int new_capacity) 
{  
    vector<Element> old_table = table;  
    int old_capacity = capacity;

    capacity = new_capacity;
    table.clear();
    table.resize(capacity);
    size = 0;

    for (int i = 0; i < old_capacity; i++) 
    {
        if (old_table[i].occupied) 
        {
            insert(old_table[i].key, old_table[i].data);
        }
    }
}

// Inserts a key-data pair into the hash table, throws an error if the key already exists
void HashTable::insert(const string &key, const string &data) 
{  
    if (size >= capacity * 0.75) 
    {  
        rehash(capacity * 2);
    }

    int index = hash(key);
    int i = 0;

    while (table[index].occupied) 
    {
        if (table[index].key == key) 
        {
            throw "Key already exists.\nCannot add data!";
        }

        i++;
        index = probe(index, i);
    }

    table[index].key = key;
    table[index].data = data;
    table[index].occupied = true;
    size++;
}

// Removes the element associated with a given key
void HashTable::remove(const string &key) 
{  
    int index = hash(key);
    int i = 0;

    while (table[index].occupied) 
    {
        if (table[index].key == key) 
        {
            table[index].occupied = false;
            size--;

            if (size < capacity * 0.25 && capacity > 17) 
            {  
                rehash(capacity / 2);
            }

            return;
        }

        i++;
        index = probe(index, i);
    }

    throw "Key not found!\nUnable to delete.";
}

// Performs a linear search for a given data value and returns the associated key
string HashTable::search(const string &data) const 
{  
    for (int i = 0; i < table.size(); ++i) 
    {
        if (table[i].occupied && table[i].data == data) 
        {
            return table[i].key;
        }
    }
    throw "Data not found!\nUnable to retrieve.";
}

// Updates a key-data pair in the hash table, or throws an error if the key does not exist
void HashTable::update(const string &key, const string &data)
{
    int index = hash(key);
    int i = 0;

    while (table[index].occupied)
    {
        if (table[index].key == key)
        {
            table[index].data = data;
            return;
        }

        i++;
        index = probe(index, i);
    }

    throw "Key not found!\nUnable to update.";
}

// Retrieves the data associated with a given key
string HashTable::retrieve(const string &key) const 
{  
    int index = hash(key);
    int i = 0;

    while (table[index].occupied) 
    {
        if (table[index].key == key) 
        {
            return table[index].data;
        }

        i++;
        index = probe(index, i);
    }

    throw "Key not found!\nUnable to retrieve.";
}



// Prints all elements in the table to the console
void HashTable::print() const 
{  
    for (int i = 0; i < table.size(); ++i) 
    {
        if (table[i].occupied) 
        {
            cout << table[i].key << endl << table[i].data << endl;
        }
    }
}

// Writes all elements in the table to a specified file
void HashTable::printToFile(const string &file_name) const 
{  
    ofstream fout(file_name);
    for (int i = 0; i < table.size(); ++i) 
    {
        if (table[i].occupied) 
        {
            fout << table[i].key << endl << table[i].data << endl;
        }
    }
}

// Returns the current number of elements in the table
int HashTable::getSize() const 
{  
    return size;
}
