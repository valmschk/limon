#include "List.h"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\nМеню:\n";
    cout << "1. Загрузить список из файла\n";
    cout << "2. Добавить элементы в файл\n";
    cout << "3. Добавить элемент в начало\n";
    cout << "4. Добавить элемент в конец\n";
    cout << "5. Добавить элемент по индексу\n";
    cout << "6. Удалить из начала\n";
    cout << "7. Удалить из конца\n";
    cout << "8. Удалить по индексу\n";
    cout << "9. Очистить список\n";
    cout << "10. Сортировать по стоимости\n";
    cout << "11. Отобразить список\n";
    cout << "12. Сохранить в файл\n";
    cout << "0. Выход\n";
}

Tourism inputTourismData() {
    Tourism data;
    cout << "Введите стоимость: ";
    cin >> data.cost;
    cin.ignore();
    cout << "Введите название тура: ";
    getline(cin, data.name);
    cout << "Введите место: ";
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
        cout << "Введите выбор: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Введите название файла: ";
                cin >> filename;
                list.loadFromFile(filename);
                cout << "Список успешно загружен из файла.\n";
                break;
            case 2:
                cout << "Введите имя файла: ";
                cin >> filename;
                list.addToFile(filename);
                cout << "Элементы успешно добавлены в файл.\n";
                break;
            case 3:
                data = inputTourismData();
                list.addToBeginning(data);
                cout << "Элемент успешно добавлен в начало.\n";
                break;
            case 4:
                data = inputTourismData();
                list.addToEnd(data);
                cout << "Элемент успешно добавлен в конец.\n";
                break;
            case 5:
                data = inputTourismData();
                cout << "Введите индекс: ";
                cin >> index;
                list.addAtIndex(data, index);
                cout << "Элемент успешно добавлен по индексу " << index << ".\n";
                break;
            case 6:
                list.removeFromBeginning();
                cout << "Элемент успешно удалён с начала.\n";
                break;
            case 7:
                list.removeFromEnd();
                cout << "Элемент успешно удалён с конца.\n";
                break;
            case 8:
                cout << "Введите индекс: ";
                cin >> index;
                list.removeAtIndex(index);
                cout << "Элемент по индексу " << index << " успешно удалён.\n";
                break;
            case 9:
                list.clear();
                cout << "Список успешно очищен.\n";
                break;
            case 10:
                list.sortByCost();
                cout << "Список успешно отсортирован по стоимости.\n";
                break;
            case 11:
                cout << "\nТекущий список:\n";
                list.display();
                break;
            case 12:
                cout << "Введите имя файла: ";
                cin >> filename;
                list.saveToFile(filename);
                cout << "Список успешно сохранён в файл.\n";
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Повторите ввод.\n";
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
