#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class HashTable {
    int capacity;
    list<string>* table;

public:
    HashTable(int V);
    void InsertItem(int key, string data);
    void FindByCarNumber(int key, string CarNumber);
    void DeleteItem(int key, string CarNumber);
    void deleteItem(int key);

    // какая то хуйня закомменчена..
    /*int checkPrime(int n)
    {
        int i;
        if (n == 1 || n == 0)
        {
            return 0;
        }
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }

    int getPrime(int n)
    {
        if (n % 2 == 0)
        {
            n++;
        }
        while (!checkPrime(n))
        {
            n += 2;
        }
        return n;
    }*/

    // Хэш функция
    int hashFunction(int key) {
        return (key % 1000);
    }

    void DisplayHashes();
    
};

// Удаление элемента
void HashTable::DeleteItem(int key, string CarNumber) {
    int index = hashFunction(key);
    int IndexOfElement = 0;
    if (table[index].size() == 1) {
        table[index].pop_back();
    }
    /*else {
        
        for (auto x : table[index]) {
            char* str = const_cast<char*>(x.c_str());
            char* substr = const_cast<char*>(CarNumber.c_str());
            int count = 0;
            for (int i = 0; i < 9; i++) {
                if (str[i] != substr[i])
                    break;
                else {
                    count++;
                }
            }
            if (count == 9) {
                list<int>::iterator it = table[index].begin();
                advance(it, IndexOfElement); // <-- advance итерирует переданный итератор на k позиций
                if (it != table[index].end())
                {
                    return table[index].erase(it); // <--- Вернет итератор на k+1 элемент, перед it нет *
                }
         
                break;
            }
            IndexOfElement++;
        }
    }*/
    
}

// Поиск элемента по номеру авто
void HashTable::FindByCarNumber(int key, string CarNumber) {
    int index = hashFunction(key);  
    if (table[index].size() == 1){
        for (auto x : table[index])
            cout << "[" << x << "]";
    }
    else {
        for (auto x : table[index]) {
            char* str = const_cast<char*>(x.c_str());
            char* substr = const_cast<char*>(CarNumber.c_str());
            int count = 0;
            for (int i = 0; i < 9; i++) {
                if (str[i] != substr[i])
                    break;
                else {
                    count++;
                }
            }
            if (count == 9) {
                cout << "[" << x << "]" ;
                break;
            }
        }
    }
}

// Поиск по фамилии
void HashTable::FindByLastName(string LastName)

// Функция создания хэш таблицы
HashTable::HashTable(int c) {
    int size = c;
    this->capacity = size;
    table = new list<string>[capacity];
}

// Функция добавления элемента в таблицу
void HashTable::InsertItem(int key, string data) {
    int index = hashFunction(key);
    table[index].push_back(data);
}

// !!!!!!НУЖНО НОРМАЛЬНО НАПИСАТЬ ФУНКЦИЮ УДАЛЕНИЯ ЭЛЕМЕНТА, ТУТ ОНА В ИЗНАЧАЛЬНоМ ВИДЕ СО СПИЗЖЕННОГО ВАРИАНТА!!!!!!
void HashTable::deleteItem(int key)
{
    int index = hashFunction(key);

    list<string>::iterator i;
    /*for (int i = table[index].begin(); i < table[index].end(); i++)
    {
        if (*i == key)
            break;
    }*/

    if (i != table[index].end())
        table[index].erase(i);
}

// Функция вывода заполненных полей таблицы 
// с ключами, разрешенными коллизиями
void HashTable::DisplayHashes() {
    for (int i = 0; i < capacity; i++) {
        if (!table[i].empty()) {
            cout << "key[" << i << "]";
            for (auto x : table[i])
                cout << " --> " << "[" << x << "]";
            cout << endl;
        }
    }
}

// Старая функция для вывода всей таблицы (нам не нужна)
/*void HashTable::displayHash() {
    for (int i = 0; i < capacity; i++) {
        cout << "table[" << i << "]";
        for (auto x : table[i])
            cout << " --> " << "[" << x << "]";
        cout << endl;
    }
}*/

// Функция для проверки корректности 
// введенного номера авто (латиница)
int RightCarNumber(string CarNumber) {
    int count = 0;
    char letters[] = "ABEKMHOPCTYX";
    if (CarNumber.length() == 9) {
        count++;
    }
    for (int i = 0; i < CarNumber.length(); i++) {
        if (i == 0 || i == 4 || i == 5) {
            int j = 0;
            while (j < 12) {
                if (CarNumber[i] == letters[j]) {
                    count++;
                }
                j++;
            }
        }
        else {
            if (CarNumber[i] >= '0' && CarNumber[i] <= '9') {
                count++;
            }
        }
    }
    if (count == 10) {
        return true;
    }
    else {
        return false;
    }
};

// Функция извлечения основных цифр из номера авто
int DigitsFromCarNumber(string CarNumber) {  
    string num;
    int num_int;
    int i = 0;
    while (i < 4) {
        if (CarNumber[i] >= '0' && CarNumber[i] <= '9') {
            num += CarNumber[i];
        }
        i++;
    }
    num_int = atoi(num.c_str());  // Перевод в int (из string)
    return num_int;
}

// Функция меню
int Menu()
{
    int x;
    cout << "\n1. Добавить элемент в таблицу" << endl;  // +
    cout << "2. Удалить элемент из таблицы" << endl;
    cout << "3. Показать таблицу" << endl;  // +
    cout << "4. Очистить таблицу" << endl;
    cout << "5. Поиск по номеру авто" << endl;  // +
    cout << "6. Поиск по фамилии" << endl;
    cout << "7. Выход" << endl;

    cout << "::: ";
    cin >> x;
    return x;
};

int main()
{
    setlocale(LC_ALL, "rus");
    HashTable h(1000);

    // Основные информационные переменные
    string CarNumber;
    string CarMark;
    string Fio;
    string Value; // Строковая переменная, являющаяся результатом собранной информации 
                //  в 1 пункте меню, добавляемая как 1 строка в хэш таблицу
    
    int key;    

    // Работа по пунктам меню
    while (1) {
        switch (Menu())
        {
        case 1:
            system("cls");          
            while (true) {
                cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра,\n\
                    A – буква (латиница, прописные) из множества: А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
                cout << "::: ";
                cin >> CarNumber;
                if (RightCarNumber(CarNumber)) {
                    break;
                }
                else {
                    cout << "Ошибка при вводе!" << endl;
                }
            }
            Value += CarNumber;
            Value += " : ";
            key = DigitsFromCarNumber(CarNumber);

            cout << "Введите марку авто:" << endl;
            cout << "::: ";
            cin.ignore();
            getline(cin, CarMark);
            Value += CarMark;
            Value += " : ";

            cout << "Введите ФИО владельца:" << endl;
            cout << "::: ";
            getline(cin, Fio);
            Value += Fio;

            h.InsertItem(key, Value);
            Value = "";

            break;

        case 2: // нихуя не работает если что, функция сама неправильная..
            system("cls");
            cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра,\n\
                    A – буква (латиница, прописные) из множества: А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
            cout << "::: ";
            cin >> CarNumber;
            key = DigitsFromCarNumber(CarNumber);
            h.DeleteItem(key, CarNumber);
            break;

        case 3:
            system("cls");
            h.DisplayHashes();
            break;

        case 4:
            system("cls");

            break;

        case 5:
            system("cls");
            while (true) {
                cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра,\n\
                    A – буква (латиница, прописные) из множества: А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
                cout << "::: ";
                cin >> CarNumber;
                if (RightCarNumber(CarNumber)) {
                    break;
                }
                else {
                    cout << "Ошибка при вводе!" << endl;
                }
            }
            key = DigitsFromCarNumber(CarNumber);
            h.FindByCarNumber(key, CarNumber);
            break;

        case 6:
            system("cls");

            break; 

        case 7: system("cls"); return 0;
            Menu(); break;

        }
    }
    
}

