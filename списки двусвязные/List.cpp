#include "List.h"

DoublyLink::DoublyLink() : head(nullptr), tail(nullptr), size(0) {} 

DoublyLink::~DoublyLink() { 
    clear();
}

void DoublyLink::loadFromFile(const string& filename) { 
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    clear();
    Tourism temp; 
    while (file >> temp.cost) { 
        file.ignore(); 
        getline(file, temp.name); 
        getline(file, temp.location); 
        addToEnd(temp);
    }

    file.close();
}

void DoublyLink::addToFile(const string& filename) { 
    ofstream file(filename, ios::app);
    if (!file.is_open()) {

        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->data.cost << endl;
        file << current->data.name << endl;
        file << current->data.location << endl;
        current = current->next;
    }

    file.close();
}

void DoublyLink::addToBeginning(const Tourism& data) {
    Node* newNode = new Node{ data, nullptr, head };
    if (head != nullptr) { 
        head->prev = newNode; 
    }
    else {
        tail = newNode;
    }

    head = newNode; 
    size++;
}

void DoublyLink::addToEnd(const Tourism& data) { 
    Node* newNode = new Node{ data, tail, nullptr };

    if (tail != nullptr) { 

        tail->next = newNode;

    }
    else {
        head = newNode;
    }

    tail = newNode;
    size++;
}

void DoublyLink::addAtIndex(const Tourism& data, int index) { 
    if (index < 0 || index > size) { 


        throw out_of_range("Индекс вне допустимого диапазона");
    }

    if (index == 0) { 
        addToBeginning(data);
    }
    else if (index == size) {
        addToEnd(data);
    }
    else {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        Node* newNode = new Node{ data, current->prev, current }; 
        current->prev->next = newNode; 
        current->prev = newNode;
        size++;
    }
}

void DoublyLink::removeFromBeginning() { 
    if (!head) {
        throw runtime_error("Список пуст");
    }

    Node* temp = head; 
    head = head->next;

    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr; 
    }

    delete temp;
    size--;
}

void DoublyLink::removeFromEnd() {
    if (!tail) {
        throw runtime_error("Список пуст"); }

    Node* temp = tail;  tail = tail->prev; 
    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }

    delete temp;
    size--;
}

void DoublyLink::removeAtIndex(int index) { 
    if (index < 0 || index >= size) { 
        throw out_of_range("Индекс вне допустимого диапазона");
    }

    if (index == 0) { 
        removeFromBeginning();
    }
    else if (index == size - 1) { 
        removeFromEnd();
    }
    else {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next; } 
        current->prev->next = current->next; 
        current->next->prev = current->prev;  delete current;
        size--;
    }
}

void DoublyLink::clear() { 
    while (head) {
        Node* temp = head; 
        head = head->next; 
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

void DoublyLink::sortByCost() { 
    if (size < 2) return; 

    bool swapped;
    do {
        swapped = false; 
        Node* current = head;

        while (current->next != nullptr) { 
            if (current->data.cost > current->next->data.cost) { 
                swap(current->data, current->next->data); 


                swapped = true; 
            }
            current = current->next;
        }
    } while (swapped);
}

void DoublyLink::display() const { 
    if (!head) { 
        cout << "Список пуст.\n";
        return;
    }

    Node* current = head; 
    while (current != nullptr) {
        cout << "Стоимость: " << current->data.cost << endl;
        cout << "Название: " << current->data.name << endl;
        cout << "Место: " << current->data.location << endl;
        cout << "- - - - - - - - - - -\n";
        current = current->next;
    }
}

void DoublyLink::saveToFile(const string& filename) const { 
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    Node* current = head; 
    while (current != nullptr) { 
        file << current->data.cost << endl;
        file << current->data.name << endl;
        file << current->data.location << endl;
        current = current->next;
    }

    file.close();
}

int DoublyLink::getSize() const { 
    return size;
}
