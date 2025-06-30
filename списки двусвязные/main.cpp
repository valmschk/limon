#include "List.h"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\n����:\n";
    cout << "1. ��������� ������ �� �����\n";
    cout << "2. �������� �������� � ����\n";
    cout << "3. �������� ������� � ������\n";
    cout << "4. �������� ������� � �����\n";
    cout << "5. �������� ������� �� �������\n";
    cout << "6. ������� �� ������\n";
    cout << "7. ������� �� �����\n";
    cout << "8. ������� �� �������\n";
    cout << "9. �������� ������\n";
    cout << "10. ����������� �� ���������\n";
    cout << "11. ���������� ������\n";
    cout << "12. ��������� � ����\n";
    cout << "0. �����\n";
}

Tourism inputTourismData() {
    Tourism data;
    cout << "������� ���������: ";
    cin >> data.cost;
    cin.ignore();
    cout << "������� �������� ����: ";
    getline(cin, data.name);
    cout << "������� �����: ";
    getline(cin, data.location);
    return data;
}

int main() {
    setlocale(LC_ALL, "rus");
    DoublyLink list;
    int choice;
    string filename;
    Tourism data;
    int index;

    do {
        displayMenu();
        cout << "������� �����: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "������� �������� �����: ";
                cin >> filename;
                list.loadFromFile(filename);
                cout << "������ ������� �������� �� �����.\n";
                break;
            case 2:
                cout << "������� ��� �����: ";
                cin >> filename;
                list.addToFile(filename);
                cout << "�������� ������� ��������� � ����.\n";
                break;
            case 3:
                data = inputTourismData();
                list.addToBeginning(data);
                cout << "������� ������� �������� � ������.\n";
                break;
            case 4:
                data = inputTourismData();
                list.addToEnd(data);
                cout << "������� ������� �������� � �����.\n";
                break;
            case 5:
                data = inputTourismData();
                cout << "������� ������: ";
                cin >> index;
                list.addAtIndex(data, index);
                cout << "������� ������� �������� �� ������� " << index << ".\n";
                break;
            case 6:
                list.removeFromBeginning();
                cout << "������� ������� ����� � ������.\n";
                break;
            case 7:
                list.removeFromEnd();
                cout << "������� ������� ����� � �����.\n";
                break;
            case 8:
                cout << "������� ������: ";
                cin >> index;
                list.removeAtIndex(index);
                cout << "������� �� ������� " << index << " ������� �����.\n";
                break;
            case 9:
                list.clear();
                cout << "������ ������� ������.\n";
                break;
            case 10:
                list.sortByCost();
                cout << "������ ������� ������������ �� ���������.\n";
                break;
            case 11:
                cout << "\n������� ������:\n";
                list.display();
                break;
            case 12:
                cout << "������� ��� �����: ";
                cin >> filename;
                list.saveToFile(filename);
                cout << "������ ������� ������� � ����.\n";
                break;
            case 0:
                cout << "����� �� ���������.\n";
                break;
            default:
                cout << "�������� �����. ��������� ����.\n";
            }
        }
        catch (const exception& e) {
            cerr << "������: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
