#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

struct Tourism { 
    float cost;
    string name;
    string location;
};

struct Node { 
    Tourism data; 
    Node* prev; 
    Node* next; 
};

class DoublyLink { 
private:
    Node* head;
    Node* tail; 
    int size; 

public:
    DoublyLink();
    ~DoublyLink();

    void loadFromFile(const string& filename); 
    void addToFile(const string& filename); 
    void addToBeginning(const Tourism& data); 
    void addToEnd(const Tourism& data);
    void addAtIndex(const Tourism& data, int index); 
    void removeFromBeginning();
    void removeFromEnd();
    void removeAtIndex(int index);
    void clear(); 
    void sortByCost(); 
   void display() const;
    void saveToFile(const string& filename) const;
    int getSize() const;
};
