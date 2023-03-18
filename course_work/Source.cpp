#include <iostream>
#include <list>
#include <string>

using namespace std;

class HashTable {
    int capacity;
    list<string>* table;

public:
    HashTable(int V);
    void InsertItem(int key, string data);
    void DeleteItem(int key, string CarNumber);
    void DisplayHashes();
    void ClearAll();
    void FindByCarNumber(int key, string CarNumber);
    void FindByLastName(string LastName);

    // Hash function
    int hashFunction(int key) {
        return (key % 1000);
    }
};

int Menu();
int RightCarNumber(string CarNumber);
int DigitsFromCarNumber(string CarNumber);

int main()
{
    setlocale(LC_ALL, "rus");
    HashTable h(1000);

    // Main information variables
    string CarNumber;
    string CarMark;
    string Fio;
    string LastName;  // Var for searching by last name
    string Value; // String variable that is the result of the collected information 
                  // in 1 menu item, added as 1 row to the hash table
    int key;    

    // Working on menu items
    while (1) {
        switch (Menu())
        {
        case 1:
            system("cls");          
            while (true) {
                cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра," << endl;
                cout << "A – буква(латиница, прописные) из множества : А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
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

        case 2: 
            system("cls");
            cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра," << endl;
            cout << "A – буква(латиница, прописные) из множества : А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
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
            h.ClearAll();
            break;

        case 5:
            system("cls");
            while (true) {
                cout << "\nВведите номер авто (строка формата «ANNNAANNN», где N-цифра," << endl;
                cout << "A – буква(латиница, прописные) из множества : А, В, Е, К, М, Н, О, Р, С, Т, Y, Х): " << endl;
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
            cout << "Введите фамилию: " << endl;
            cout << "::: ";
            cin >> LastName;
            h.FindByLastName(LastName);
            break; 

        case 7: system("cls"); return 0;
            Menu(); break;
        }
    } 
}

// Hash table creation function
HashTable::HashTable(int c) {
    int size = c;
    this->capacity = size;
    table = new list<string>[capacity];
}

// Main menu function
int Menu()
{
    int x;
    cout << "\n1. Добавить элемент в таблицу" << endl;  // +
    cout << "2. Удалить элемент из таблицы" << endl;
    cout << "3. Показать таблицу" << endl;  // +
    cout << "4. Очистить таблицу" << endl;
    cout << "5. Поиск по номеру авто" << endl;  // +
    cout << "6. Поиск по фамилии" << endl;  // +
    cout << "7. Выход" << endl;
    cout << "::: ";
    cin >> x;
    if (x >= 1 && x <= 7)
    {
        return x;
    }
    else
    {
        cout << "Повторите ввод!" << endl;
    }
    
};

// Function of adding an element to the table
void HashTable::InsertItem(int key, string data) {
    int index = hashFunction(key);
    table[index].push_back(data);
}

// Deleting an element
void HashTable::DeleteItem(int key, string CarNumber) {
    int index = hashFunction(key);
    int IndexOfElement = 0;
    if (table[index].size() == 1) {
        table[index].pop_back();
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
                list<string>::iterator it = table[index].begin();
                // 'advance' iterates the passed iterator by k positions
                advance(it, IndexOfElement);  
                if (it != table[index].end())
                {
                    table[index].erase(it); 
                    return;
                }
                break;
            }
            IndexOfElement++;
        }
    }
}

// Function for displaying filled table fields
// with keys resolved by collisions
void HashTable::DisplayHashes() {
    bool flag = false;
    for (int i = 0; i < capacity; i++) {
        if (!table[i].empty()) {
            flag = true;
            break;
        }
    }
    if (flag == true)
    {
        for (int i = 0; i < capacity; i++) {
            if (!table[i].empty()) {
                cout << "key[" << i << "]";
                for (auto x : table[i])
                    cout << " --> " << "[" << x << "]";
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Таблица пуста!" << endl;
    }

}

// Clearing the entire table
void HashTable::ClearAll() {
    for (int i = 0; i < 1000; i++) {
        if (!table[i].empty()) {
            table[i].clear();
        }
    }
}

// Search for an item by car number
void HashTable::FindByCarNumber(int key, string CarNumber) {
    int index = hashFunction(key);
    string BufferStr = "";
    if (table[index].size() == 1) {
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
                BufferStr += x;
                break;
            }
            
        }
        if (!BufferStr.empty())
        {
            cout << BufferStr << "\n";
        }
        else
        {
            cout << "Элемента с таким номером нет!" << endl;
        }
    }
}

// Search by last name
void HashTable::FindByLastName(string LastName) {
    int n = 0;
    string BufferStr = "";
    for (int i = 0; i < 1000; i++) {
        if (!table[i].empty()) {
            for (auto x : table[i]) {
                int counter = 0;
                int k = 0;
                int count = 0;
                char* str = const_cast<char*>(x.c_str());
                char* substr = const_cast<char*>(LastName.c_str());
                for (int i = 0; i < strlen(str); i++) {
                    if (counter == 2) {
                        break;
                    }
                    else {
                        if (x[i] == 58) {
                            counter++;
                        }
                        k++;
                    }
                }
                k++;
                int i = 0;
                int j = k;
                for (k; k <= j + strlen(substr); k++) {
                    if (str[k] != substr[i])
                        break;
                    else {
                        count++;
                    }
                    i++;
                }
                if (count == strlen(substr)) {
                    if (str[j + strlen(substr)] == 32) {
                        BufferStr += x;
                        BufferStr += "\n";
                    }
                }
               
            }
            if (!BufferStr.empty())
            {
                cout << BufferStr << "\n";
            }
            else
            {
                cout << "Элемента с такой фамилией нет!" << endl;
            }
        }
    };
}

// Function for checking the correctness
// of the entered car number (Latin)
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

// The function of extracting the main digits from the car number
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
    num_int = atoi(num.c_str());  
    return num_int;
}