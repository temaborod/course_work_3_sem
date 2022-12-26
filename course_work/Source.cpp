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

    // ����� �� ����� ������������..
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

    // ��� �������
    int hashFunction(int key) {
        return (key % 1000);
    }

    void DisplayHashes();
    
};

// �������� ��������
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
                advance(it, IndexOfElement); // <-- advance ��������� ���������� �������� �� k �������
                if (it != table[index].end())
                {
                    return table[index].erase(it); // <--- ������ �������� �� k+1 �������, ����� it ��� *
                }
         
                break;
            }
            IndexOfElement++;
        }
    }*/
    
}

// ����� �������� �� ������ ����
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

// ����� �� �������
void HashTable::FindByLastName(string LastName)

// ������� �������� ��� �������
HashTable::HashTable(int c) {
    int size = c;
    this->capacity = size;
    table = new list<string>[capacity];
}

// ������� ���������� �������� � �������
void HashTable::InsertItem(int key, string data) {
    int index = hashFunction(key);
    table[index].push_back(data);
}

// !!!!!!����� ��������� �������� ������� �������� ��������, ��� ��� � ����������� ���� �� ����������� ��������!!!!!!
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

// ������� ������ ����������� ����� ������� 
// � �������, ������������ ����������
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

// ������ ������� ��� ������ ���� ������� (��� �� �����)
/*void HashTable::displayHash() {
    for (int i = 0; i < capacity; i++) {
        cout << "table[" << i << "]";
        for (auto x : table[i])
            cout << " --> " << "[" << x << "]";
        cout << endl;
    }
}*/

// ������� ��� �������� ������������ 
// ���������� ������ ���� (��������)
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

// ������� ���������� �������� ���� �� ������ ����
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
    num_int = atoi(num.c_str());  // ������� � int (�� string)
    return num_int;
}

// ������� ����
int Menu()
{
    int x;
    cout << "\n1. �������� ������� � �������" << endl;  // +
    cout << "2. ������� ������� �� �������" << endl;
    cout << "3. �������� �������" << endl;  // +
    cout << "4. �������� �������" << endl;
    cout << "5. ����� �� ������ ����" << endl;  // +
    cout << "6. ����� �� �������" << endl;
    cout << "7. �����" << endl;

    cout << "::: ";
    cin >> x;
    return x;
};

int main()
{
    setlocale(LC_ALL, "rus");
    HashTable h(1000);

    // �������� �������������� ����������
    string CarNumber;
    string CarMark;
    string Fio;
    string Value; // ��������� ����������, ���������� ����������� ��������� ���������� 
                //  � 1 ������ ����, ����������� ��� 1 ������ � ��� �������
    
    int key;    

    // ������ �� ������� ����
    while (1) {
        switch (Menu())
        {
        case 1:
            system("cls");          
            while (true) {
                cout << "\n������� ����� ���� (������ ������� �ANNNAANNN�, ��� N-�����,\n\
                    A � ����� (��������, ���������) �� ���������: �, �, �, �, �, �, �, �, �, �, Y, �): " << endl;
                cout << "::: ";
                cin >> CarNumber;
                if (RightCarNumber(CarNumber)) {
                    break;
                }
                else {
                    cout << "������ ��� �����!" << endl;
                }
            }
            Value += CarNumber;
            Value += " : ";
            key = DigitsFromCarNumber(CarNumber);

            cout << "������� ����� ����:" << endl;
            cout << "::: ";
            cin.ignore();
            getline(cin, CarMark);
            Value += CarMark;
            Value += " : ";

            cout << "������� ��� ���������:" << endl;
            cout << "::: ";
            getline(cin, Fio);
            Value += Fio;

            h.InsertItem(key, Value);
            Value = "";

            break;

        case 2: // ����� �� �������� ���� ���, ������� ���� ������������..
            system("cls");
            cout << "\n������� ����� ���� (������ ������� �ANNNAANNN�, ��� N-�����,\n\
                    A � ����� (��������, ���������) �� ���������: �, �, �, �, �, �, �, �, �, �, Y, �): " << endl;
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
                cout << "\n������� ����� ���� (������ ������� �ANNNAANNN�, ��� N-�����,\n\
                    A � ����� (��������, ���������) �� ���������: �, �, �, �, �, �, �, �, �, �, Y, �): " << endl;
                cout << "::: ";
                cin >> CarNumber;
                if (RightCarNumber(CarNumber)) {
                    break;
                }
                else {
                    cout << "������ ��� �����!" << endl;
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

