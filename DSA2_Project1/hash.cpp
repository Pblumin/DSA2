#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "hash.h"
#include <fstream>
using namespace std;


unsigned int hashTable::getPrime(int size){
    // Return a prime number at least as large as size.
    // Uses a precomputed sequence of selected prime numbers.
    if (size < 50000){
        return 100003;
    } else if (size < 150000){
        return 300017;
    } else if (size < 250000) {
        return 500009;
    } else if (size < 350000) {
        return 700001;
    } else if  (size < 500000) {
        return 1000003;
    } else if (size < 1000000) {
        return 2000003;
    } else {
        cout << "The dictionary is too large";
        return 0;
    }
}

hashTable::hashTable(int size){
    size = getPrime(size);
    data.resize(size);
    capacity = size;
};

int hashTable::insert(const std::string &key, void *pv = nullptr){
    // Insert the specified key into the hash table.
    // If an optional pointer is provided,
    // associate that pointer with the key.
    // Returns 0 on success,
    // 1 if key already exists in hash table,
    // 2 if rehash fails.
    int index = hash(key); 

    //Need to somehow push the data in maybe use this ??? - data[index].push_back(key); ASK THEO
    if (contains(key)) {
        return 1;
    }
    
    if (!rehash()) {
        return 2;
    }

    ++filled;
    data[index].isOccupied = true;
    data[index].isDeleted = false;
    data[index].key = key;
    data[index].pv = pv;

    return 0;
}

bool hashTable::contains(const std::string &key){
    // Check if the specified key is in the hash table.
    // If so, return true; otherwise, return false.
    if (findPos(key) == -1){
        return false;
    } else {
        return true;
    }
}

void *hashTable::getPointer(const std::string &key, bool *b = nullptr){
    // Get the pointer associated with the specified key.
    // If the key does not exist in the hash table, return nullptr.
    // If an optional pointer to a bool is provided,
    // set the bool to true if the key is in the hash table,
    // and set the bool to false otherwise.
    int position;
    *b = false;
    position = findPos(key);
    if (position = -1){
        return nullptr;
    } else {
        *b = true;
        return data[position].pv;
    }
}

int hashTable::setPointer(const std::string &key, void *pv){
    // Set the pointer associated with the specified key.
    // Returns 0 on success,
    // 1 if the key does not exist in the hash table.
    int position;
    position = findPos(key);
    if (position = -1){
        return 1;
    } else {
        data[position].pv = pv;
        return 0;
    }
}

bool hashTable::remove(const std::string &key){
    // Delete the item with the specified key.
    // Returns true on success,
    // false if the specified key is not in the hash table.
    int position;
    position = findPos(key);
    //int* ptr = data[position];
    if (position = -1){
        return false;
    } else {
        //delete(ptr); //ASK THEO
        data[position].isDeleted = true;
        --filled;
        return true;
    }
}

int hashTable::hash(const std::string &key){
    // The hash function.
    unsigned int hashVal = 0;
    for (char ch : key){
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % capacity;
}

int hashTable::findPos(const std::string &key){
    // Search for an item with the specified key.
    // Return the position if found, -1 otherwise.
    int index = hash(key);
    while(data[index].isOccupied) {
        //ASK THEO FOR HELP
        if(data[index].key == key){
            return index;
        }
    }
    return -1;
}

bool hashTable::rehash(){
    // The rehash function; makes the hash table bigger.
    // Returns true on success, false if memory allocation fails.
    int size;
    size = getPrime(size);
    data.clear();
    data.resize(size);
    //ASK THEO IDK WTF TO DO HERE
}






