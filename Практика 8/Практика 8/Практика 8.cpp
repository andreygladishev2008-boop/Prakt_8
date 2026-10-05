// Практика 8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
using namespace std;

struct Product 
{
    char name[50];
    double price;
    int quantity;
};

struct Node 
{
    Product data;
    Node* next;
    Node* prev;

    Node(const Product& p) : data(p), next(nullptr), prev(nullptr) {}
};

class DoubleLinkedList 
{
private:
    Node* head;
    Node* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoubleLinkedList() 
    {
        clear();
    }

    void push_front(const Product& p) 
    {
        Node* newNode = new Node(p);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }

    void push_back(const Product& p) 
    {
        Node* newNode = new Node(p);
        if (tail == nullptr) 
        {
            head = tail = newNode;
        }
        else 
        {
            newNode -> prev = tail;
            tail -> next = newNode;
            tail = newNode;
        }
    }

    void pop_front() 
    {
        if (head == nullptr) return;
        Node* temp = head;
        if (head == tail) 
        {
            head = tail = nullptr;
        }
        else 
        {
            head = head -> next;
            head -> prev = nullptr;
        }
        delete temp;
    }

    void pop_back() 
    {
        if (tail == nullptr) return;
        Node* temp = tail;
        if (head == tail) 
        {
            head = tail = nullptr;
        }
        else 
        {
            tail = tail -> prev;
            tail -> next = nullptr;
        }
        delete temp;
    }

    void display_forward() const 
    {
        if (head == nullptr) 
        {
            cout << "Список пуст." << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) 
        {
            cout << "Название: " << current -> data.name
                << " | Цена: " << current -> data.price
                << " | Кол-во: " << current -> data.quantity << endl;
            current = current -> next;
        }
    }

    void display_backward() const 
    {
        if (tail == nullptr) 
        {
            cout << "Список пуст." << endl;
            return;
        }
        Node* current = tail;
        while (current != nullptr) 
        {
            cout << "Название: " << current -> data.name
                << " | Цена: " << current -> data.price
                << " | Кол-во: " << current -> data.quantity << endl;
            current = current -> prev;
        }
    }

    Node* find_by_name(const char* searchName) const 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            if (strcmp(current -> data.name, searchName) == 0) 
            {
                return current;
            }
            current = current -> next;
        }
        return nullptr;
    }

    void remove_node(Node* nodeToRemove) 
    {
        if (nodeToRemove == nullptr) return;

        if (nodeToRemove == head) 
        {
            pop_front();
            return;
        }
        if (nodeToRemove == tail) 
        {
            pop_back();
            return;
        }

        nodeToRemove -> prev -> next = nodeToRemove -> next;
        nodeToRemove -> next -> prev = nodeToRemove -> prev;
        delete nodeToRemove;
    }

    void clear() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* nextNode = current -> next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }

    void find_product(const char* searchName) const 
    {
        Node* found = find_by_name(searchName);
        if (found != nullptr) 
        {
            cout << "Товар найден: " << found -> data.name
                << " | Цена: " << found -> data.price
                << " | Кол-во: " << found -> data.quantity << endl;
        }
        else 
        {
            cout << "Товар с названием '" << searchName << "' не найден." << endl;
        }
    }

    void remove_zero_quantity() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* nextNode = current -> next;
            if (current -> data.quantity == 0) 
            {
                remove_node(current);
            }
            current = nextNode;
        }
        cout << "Товары с нулевым количеством удалены." << endl;
    }

    void move_most_expensive_to_front() {
        if (head == nullptr || head == tail) return;

        Node* maxNode = head;
        Node* current = head -> next;

        while (current != nullptr) 
        {
            if (current -> data.price > maxNode -> data.price) 
            {
                maxNode = current;
            }
            current = current -> next;
        }

        if (maxNode == head) 
        {
            cout << "Самый дорогой товар уже находится в начале списка." << endl;
            return;
        }

        if (maxNode == tail) 
        {
            tail = maxNode -> prev;
            tail -> next = nullptr;
        }
        else 
        {
            maxNode -> prev -> next = maxNode -> next;
            maxNode -> next -> prev = maxNode -> prev;
        }

        maxNode -> prev = nullptr;
        maxNode -> next = head;
        head -> prev = maxNode;
        head = maxNode;

        cout << "Самый дорогой товар перемещен в начало списка." << endl;
    }
};


int get_int_input() 
{
    int value;
    while (!(cin >> value)) 
    {
        cout << "Ошибка ввода. Введите число: ";
        cin.clear();
        cin.ignore(10000, '\n'); 
    }
    cin.ignore(); 
    return value;
}

double get_double_input() 
{
    double value;
    while (!(cin >> value)) 
    {
        cout << "Ошибка ввода. Введите число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();
    return value;
}

int main() 
{
    setlocale(NULL, "Russian");
    DoubleLinkedList list;
    int choice;

    do {
        cout << "\nМеню склада товаров: \n";
        cout << "1. Добавить товар в начало\n";
        cout << "2. Добавить товар в конец\n";
        cout << "3. Удалить первый товар\n";
        cout << "4. Удалить последний товар\n";
        cout << "5. Вывести список (от начала к концу)\n";
        cout << "6. Вывести список (от конца к началу)\n";
        cout << "7. Найти товар по названию\n";
        cout << "8. Удалить товары с нулевым количеством\n";
        cout << "9. Переместить самый дорогой товар в начало\n";
        cout << "10. Очистить список\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        choice = get_int_input();

        if (choice == 1 || choice == 2) 
        {
            Product p;
            cout << "Введите название товара: ";
            cin.getline(p.name, 50);
            cout << "Введите цену: ";
            p.price = get_double_input();
            cout << "Введите количество: ";
            p.quantity = get_int_input();

            if (choice == 1) list.push_front(p);
            else list.push_back(p);
            cout << "Товар добавлен." << endl;
        }
        else if (choice == 3) 
        {
            list.pop_front();
            cout << "Первый товар удален." << endl;
        }
        else if (choice == 4) 
        {
            list.pop_back();
            cout << "Последний товар удален." << endl;
        }
        else if (choice == 5) 
        {
            cout << "Список (начало -> конец)\n";
            list.display_forward();
        }
        else if (choice == 6) 
        {
            cout << "Список (конец -> начало)\n";
            list.display_backward();
        }
        else if (choice == 7) 
        {
            char searchName[50];
            cout << "Введите название для поиска: ";
            cin.getline(searchName, 50);
            list.find_product(searchName);
        }
        else if (choice == 8) 
        {
            list.remove_zero_quantity();
        }
        else if (choice == 9) 
        {
            list.move_most_expensive_to_front();
        }
        else if (choice == 10) 
        {
            list.clear();
            cout << "Список очищен." << endl;
        }
        else if (choice == 0) 
        {
            cout << "Выход из программы. Освобождение памяти..." << endl;
        }
        else {
            cout << "Неверный пункт меню. Попробуйте снова." << endl;
        }

    } while (choice != 0);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
