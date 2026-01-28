#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    int id;
    string lastName;
    string firstName;
    int age;
    string position;

    Employee() : id(0), age(0) {}
};

const int MAX_EMPLOYEES = 100;
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;
int nextId = 1;

//Функция для сохранения всех сотрудников в файл
void saveToFile(string filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка! Не могу создать файл: " << filename << endl;
        return;
    }

    file << employeeCount << endl;

    //Сохраняем каждого сотрудника
    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].id << endl;
        file << employees[i].lastName << endl;
        file << employees[i].firstName << endl;
        file << employees[i].age << endl;
        file << employees[i].position << endl;
    }

    file.close();
    cout << "Данные сохранены в файл: " << filename << endl;
}

//Функция для загрузки сотрудников из файла
void loadFromFile(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка! Не могу открыть файл: " << filename << endl;
        return;
    }

    int count;
    file >> count;

    if (count > MAX_EMPLOYEES) {
        cout << "В файле слишком много сотрудников!" << endl;
        return;
    }

    employeeCount = 0;
    for (int i = 0; i < count; i++) {
        file >> employees[employeeCount].id;
        file >> employees[employeeCount].lastName;
        file >> employees[employeeCount].firstName;
        file >> employees[employeeCount].age;
        file >> employees[employeeCount].position;
        employeeCount++;

        //обновляем nextId чтобы не было одинаковых ID
        if (employees[employeeCount - 1].id >= nextId) {
            nextId = employees[employeeCount - 1].id + 1;
        }
    }

    file.close();
    cout << "Загружено " << count << " сотрудников из файла: " << filename << endl;
}

// Функция для добавления сотрудника
void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Не могу добавить! База переполнена." << endl;
        return;
    }

    cout << "\nДобавление сотрудника" << endl;

    employees[employeeCount].id = nextId++;

    cout << "Фамилия: ";
    cin >> employees[employeeCount].lastName;

    cout << "Имя: ";
    cin >> employees[employeeCount].firstName;

    cout << "Возраст: ";
    cin >> employees[employeeCount].age;

    cout << "Должность: ";
    cin >> employees[employeeCount].position;

    employeeCount++;
    cout << "Сотрудник добавлен! ID: " << employees[employeeCount - 1].id << endl;
}

//Функция для редактирования сотрудника
void editEmployee() {
    int id;
    cout << "Введите ID сотрудника для редактирования: ";
    cin >> id;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            cout << "Найден сотрудник: " << employees[i].lastName << " " << employees[i].firstName << endl;

            cout << "Новая фамилия: ";
            cin >> employees[i].lastName;

            cout << "Новое имя: ";
            cin >> employees[i].firstName;

            cout << "Новый возраст: ";
            cin >> employees[i].age;

            cout << "Новая должность: ";
            cin >> employees[i].position;

            cout << "Данные обновлены!" << endl;
            return;
        }
    }

    cout << "Сотрудник с ID " << id << " не найден!" << endl;
}

//Функция для удаления сотрудника
void deleteEmployee() {
    int id;
    cout << "Введите ID сотрудника для удаления: ";
    cin >> id;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employeeCount--;
            cout << "Сотрудник удален!" << endl;
            return;
        }
    }

    cout << "Сотрудник с ID " << id << " не найден!" << endl;
}

//Функция для поиска по фамилии
void searchByLastName() {
    string lastName;
    cout << "Введите фамилию для поиска: ";
    cin >> lastName;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].lastName == lastName) {
            if (!found) {
                cout << "\nНайденные сотрудники" << endl;
                found = true;
            }
            cout << "ID: " << employees[i].id << endl;
            cout << "ФИО: " << employees[i].lastName << " " << employees[i].firstName << endl;
            cout << "Возраст: " << employees[i].age << endl;
            cout << "Должность: " << employees[i].position << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!found) {
        cout << "Сотрудники с фамилией '" << lastName << "' не найдены!" << endl;
    }
    else {
        //Предложение сохранить результаты
        cout << "Сохранить результаты в файл? (1-да, 0-нет): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ofstream file(filename);
            if (file.is_open()) {
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i].lastName == lastName) {
                        file << employees[i].id << " "
                            << employees[i].lastName << " "
                            << employees[i].firstName << " "
                            << employees[i].age << " "
                            << employees[i].position << endl;
                    }
                }
                file.close();
                cout << "Результаты сохранены в " << filename << endl;
            }
        }
    }
}

// Функция для вывода всех сотрудников
void showAllEmployees() {
    if (employeeCount == 0) {
        cout << "База данных пуста!" << endl;
        return;
    }

    cout << "\nВсе сотрудники" << endl;
    cout << "Всего: " << employeeCount << " человек" << endl;

    for (int i = 0; i < employeeCount; i++) {
        cout << "ID: " << employees[i].id << endl;
        cout << "ФИО: " << employees[i].lastName << " " << employees[i].firstName << endl;
        cout << "Возраст: " << employees[i].age << endl;
        cout << "Должность: " << employees[i].position << endl;
        cout << "------------------------" << endl;
    }
}

//Функция для вывода сотрудников указанного возраста
void showByAge() {
    int age;
    cout << "Введите возраст: ";
    cin >> age;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].age == age) {
            if (!found) {
                cout << "\nСотрудники возраста" << age << " ===" << endl;
                found = true;
            }
            cout << "ID: " << employees[i].id << endl;
            cout << "ФИО: " << employees[i].lastName << " " << employees[i].firstName << endl;
            cout << "Должность: " << employees[i].position << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!found) {
        cout << "Сотрудников возраста " << age << " не найдено!" << endl;
    }
    else {
        //Предложение сохранить результаты
        cout << "Сохранить результаты в файл? (1-да, 0-нет): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ofstream file(filename);
            if (file.is_open()) {
                for (int i = 0; i < employeeCount; i++) {
                    if (employees[i].age == age) {
                        file << employees[i].id << " "
                            << employees[i].lastName << " "
                            << employees[i].firstName << " "
                            << employees[i].position << endl;
                    }
                }
                file.close();
                cout << "Результаты сохранены в " << filename << endl;
            }
        }
    }
}

//Функция для вывода сотрудников по первой букве фамилии
void showByFirstLetter() {
    char letter;
    cout << "Введите первую букву фамилии: ";
    cin >> letter;

    bool found = false;
    for (int i = 0; i < employeeCount; i++) {
        if (!employees[i].lastName.empty() && employees[i].lastName[0] == letter) {
            if (!found) {
                cout << "\nСотрудники с фамилией на букву '" << letter << "' ===" << endl;
                found = true;
            }
            cout << "ID: " << employees[i].id << endl;
            cout << "ФИО: " << employees[i].lastName << " " << employees[i].firstName << endl;
            cout << "Возраст: " << employees[i].age << endl;
            cout << "Должность: " << employees[i].position << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!found) {
        cout << "Сотрудников с фамилией на букву '" << letter << "' не найдено!" << endl;
    }
    else {
        //Предложение сохранить результаты
        cout << "Сохранить результаты в файл? (1-да, 0-нет): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;

            ofstream file(filename);
            if (file.is_open()) {
                for (int i = 0; i < employeeCount; i++) {
                    if (!employees[i].lastName.empty() && employees[i].lastName[0] == letter) {
                        file << employees[i].id << " "
                            << employees[i].lastName << " "
                            << employees[i].firstName << " "
                            << employees[i].age << " "
                            << employees[i].position << endl;
                    }
                }
                file.close();
                cout << "Результаты сохранены в " << filename << endl;
            }
        }
    }
}

//меню
void showMenu() {
    cout << "\n=== ИНФОРМАЦИОННАЯ СИСТЕМА 'СОТРУДНИКИ' ===" << endl;
    cout << "1. Добавить сотрудника" << endl;
    cout << "2. Редактировать сотрудника" << endl;
    cout << "3. Удалить сотрудника" << endl;
    cout << "4. Поиск по фамилии" << endl;
    cout << "5. Показать всех сотрудников" << endl;
    cout << "6. Показать сотрудников указанного возраста" << endl;
    cout << "7. Показать сотрудников по первой букве фамилии" << endl;
    cout << "8. Сохранить данные в файл" << endl;
    cout << "9. Загрузить данные из файла" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "ru");

    string startupFile;
    cout << "Введите имя файла для загрузки (или нажмите Enter для пропуска): ";
    getline(cin, startupFile);

    if (!startupFile.empty()) {
        loadFromFile(startupFile);
    }

    //Главный цикл программы
    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            editEmployee();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            searchByLastName();
            break;
        case 5:
            showAllEmployees();
            break;
        case 6:
            showByAge();
            break;
        case 7:
            showByFirstLetter();
            break;
        case 8:
        {
            string filename;
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            saveToFile(filename);
        }
        break;
        case 9:
        {
            string filename;
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            loadFromFile(filename);
        }
        break;
        case 0:
            // Автомат. сохранение при выходе
            if (!startupFile.empty()) {
                cout << "Автоматически сохраняю данные в " << startupFile << "..." << endl;
                saveToFile(startupFile);
            }
            cout << "До свидания!" << endl;
            return 0;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    }

    return 0;
}
