#include <iostream>
#include <stdexcept>
using namespace std;

class Vector {
private:
    unsigned int* arr;       
    unsigned int size;      
    int state;               
    static int objectCount;  

public:
    // Конструктор без параметрів
    Vector() : size(1), state(0) {
        arr = new(nothrow) unsigned int[size];
        if (arr == nullptr) {
            state = -1;  // Помилка: недостатньо пам'яті
        } else {
            arr[0] = 0;  
        }
        ++objectCount;
    }

    // Конструктор з одним параметром
    Vector(unsigned int s) : size(s), state(0) {
        if (s <= 0) {
            state = -2;  
            arr = nullptr;
        } else {
            arr = new(nothrow) unsigned int[size];
            if (arr == nullptr) {
                state = -1;  
            } else {
                for (unsigned int i = 0; i < size; ++i) {
                    arr[i] = 0;  
                }
            }
        }
        ++objectCount;
    }

    // розмір вектора та значення ініціалізації
    Vector(unsigned int s, unsigned int initValue) : size(s), state(0) {
        if (s <= 0) {
            state = -2;
            arr = nullptr;
        } else {
            arr = new(nothrow) unsigned int[size];
            if (arr == nullptr) {
                state = -1;  
            } else {
                for (unsigned int i = 0; i < size; ++i) {
                    arr[i] = initValue;  
                }
            }
        }
        ++objectCount;
    }


    Vector(const Vector& v) : size(v.size), state(v.state) {
        arr = new(nothrow) unsigned int[size];
        if (arr == nullptr) {
            state = -1; 
        } else {
            for (unsigned int i = 0; i < size; ++i) {
                arr[i] = v.arr[i];  
            }
        }
        ++objectCount;
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& v) {
        if (this == &v) {
            return *this;  // Перевірка на самоприсвоєння
        }

        delete[] arr;  
        size = v.size;
        state = v.state;
        arr = new(nothrow) unsigned int[size];
        if (arr == nullptr) {
            state = -1;  
        } else {
            for (unsigned int i = 0; i < size; ++i) {
                arr[i] = v.arr[i];  // Копіюємо елементи
            }
        }

        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] arr;  
        --objectCount;
    }

    // Функція для встановлення значення елементу
    void setElement(unsigned int index, unsigned int value = 0) {
        if (index >= size) {
            state = -3;  // Помилка: вихід за межі масиву
            cout << "Помилка: вихід за межі масиву!" << endl;
        } else {
            arr[index] = value;
        }
    }

    // Функція для отримання значення елементу
    unsigned int getElement(unsigned int index) {
        if (index >= size) {
            state = -3;  
            cout << "Помилка: вихід за межі масиву!" << endl;
            return 0;  
        }
        return arr[index];
    }

    // Функція друку
    void print() const {
        if (arr == nullptr) {
            cout << "Помилка: масив не ініціалізований." << endl;
            return;
        }
        for (unsigned int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Додавання векторів
    Vector operator+(const Vector& v) const {
        if (size != v.size) {
            cout << "Помилка: вектори різного розміру!" << endl;
            return *this;
        }

        Vector result(size);
        for (unsigned int i = 0; i < size; ++i) {
            result.arr[i] = arr[i] + v.arr[i];
        }
        return result;
    }

    
    Vector operator-(const Vector& v) const {
        if (size != v.size) {
            cout << "Помилка: вектори різного розміру!" << endl;
            return *this;  
        }

        Vector result(size);
        for (unsigned int i = 0; i < size; ++i) {
            result.arr[i] = arr[i] - v.arr[i];
        }
        return result;
    }

    // Множення 
    Vector operator*(unsigned short multiplier) const {
        Vector result(size);
        for (unsigned int i = 0; i < size; ++i) {
            result.arr[i] = arr[i] * multiplier;
        }
        return result;
    }

    // Порівняння векторів
    bool operator==(const Vector& v) const {
        if (size != v.size) return false;
        for (unsigned int i = 0; i < size; ++i) {
            if (arr[i] != v.arr[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vector& v) const {
        return !(*this == v);
    }

    bool operator>(const Vector& v) const {
        if (size != v.size) return false;
        for (unsigned int i = 0; i < size; ++i) {
            if (arr[i] <= v.arr[i]) return false;
        }
        return true;
    }

    bool operator<(const Vector& v) const {
        return v > *this;
    }

   
    static int getObjectCount() {
        return objectCount;
    }
};


int Vector::objectCount = 0;

int main() {
     
    Vector v1(5, 2);  
    Vector v2(5, 3);  
    
    cout << "Вектор v1: ";
    v1.print();
    cout << "Вектор v2: ";
    v2.print();


    Vector v3 = v1 + v2;
    cout << "v1 + v2: ";
    v3.print();


 
    Vector v5 = v1 * 3;
    cout << "v1 * 3: ";
    v5.print();

    
    cout << "v1 == v2? " << (v1 == v2 ? "True" : "False") << endl;

    cout << "Кількість об'єктів: " << Vector::getObjectCount() << endl;

    return 0;
}
