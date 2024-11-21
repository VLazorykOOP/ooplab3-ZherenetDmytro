#include <iostream>
#include <stdexcept>  
using namespace std;

class Matrix {
private:
    int* arr;      
    int n, m;      
    mutable int state; 
    static int objectCount;  

public:
    
    Matrix() : n(3), m(3), state(0) {
        arr = new(nothrow) int[n * m];
        if (arr == nullptr) {
            state = -1; 
        } else {
            for (int i = 0; i < n * m; ++i) {
                arr[i] = 0;  
            }
        }
        ++objectCount;
    }

    // Конструктор з двома параметрами
    Matrix(int rows, int cols) : n(rows), m(cols), state(0) {
        arr = new(nothrow) int[n * m];
        if (arr == nullptr) {
            state = -1;  
        } else {
            for (int i = 0; i < n * m; ++i) {
                arr[i] = 0;  
            }
        }
        ++objectCount;
    }

    // Конструктор з трьома параметрами 
    Matrix(int rows, int cols, int value) : n(rows), m(cols), state(0) {
        arr = new(nothrow) int[n * m];
        if (arr == nullptr) {
            state = -1;  
        } else {
            for (int i = 0; i < n * m; ++i) {
                arr[i] = value; 
            }
        }
        ++objectCount;
    }

    Matrix(const Matrix& mat) : n(mat.n), m(mat.m), state(mat.state) {
        arr = new(nothrow) int[n * m];
        if (arr == nullptr) {
            state = -1;  
        } else {
            for (int i = 0; i < n * m; ++i) {
                arr[i] = mat.arr[i];  
            }
        }
        ++objectCount;
    }

    ~Matrix() {
        delete[] arr;  
        --objectCount;
    }

    Matrix& operator=(const Matrix& mat) {
        if (this == &mat) return *this;

        delete[] arr;  
        n = mat.n;
        m = mat.m;
        state = mat.state;
        arr = new(nothrow) int[n * m];
        if (arr == nullptr) {
            state = -1; 
        } else {
            for (int i = 0; i < n * m; ++i) {
                arr[i] = mat.arr[i];  
            }
        }
        return *this;
    }

    void setElement(int i, int j, int value = 0) {
        if (i >= n || j >= m || i < 0 || j < 0) {
            state = -2;  
            cout << "Помилка: вихід за межі матриці!" << endl;
        } else {
            arr[i * m + j] = value;
        }
    }

    int getElement(int i, int j) const {
        if (i >= n || j >= m || i < 0 || j < 0) {
            state = -2;  
            cout << "Помилка: вихід за межі матриці!" << endl;
            return 0;
        }
        return arr[i * m + j];
    }

    void print() const {
        if (arr == nullptr) {
            cout << "Помилка: матриця не ініціалізована." << endl;
            return;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << arr[i * m + j] << " ";
            }
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& mat) const {
        if (n != mat.n || m != mat.m) {
            cout << "Помилка: розміри матриць не співпадають!" << endl;
            return *this;  
        }

        Matrix result(n, m);  
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result.arr[i * m + j] = arr[i * m + j] + mat.arr[i * m + j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& mat) const {
        if (n != mat.n || m != mat.m) {
            cout << "Помилка: розміри матриць не співпадають!" << endl;
            return *this;
        }

        Matrix result(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result.arr[i * m + j] = arr[i * m + j] - mat.arr[i * m + j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& mat) const {
        if (m != mat.n) {
            cout << "Помилка: кількість стовпців першої матриці не співпадає з кількістю рядків другої!" << endl;
            return *this;
        }

        Matrix result(n, mat.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < mat.m; ++j) {
                result.arr[i * mat.m + j] = 0;
                for (int k = 0; k < m; ++k) {
                    result.arr[i * mat.m + j] += arr[i * m + k] * mat.arr[k * mat.m + j];
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix& mat) const {
        if (n != mat.n || m != mat.m) {
            return false;
        }
        for (int i = 0; i < n * m; ++i) {
            if (arr[i] != mat.arr[i]) {
                return false;
            }
        }
        return true;
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int Matrix::objectCount = 0;

int main() {
    int rows, cols;

    
    cout << "Введіть кількість рядків матриці: ";
    cin >> rows;
    cout << "Введіть кількість стовпців матриці: ";
    cin >> cols;

    
    Matrix m1(rows, cols);
    cout << "Введіть елементи матриці:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            cout << "Елемент [" << i << "][" << j << "]: ";
            cin >> value;
            m1.setElement(i, j, value);
        }
    }

    m1.print();
    cout << endl;

    
    Matrix m2(rows, cols);
    cout << "Введіть елементи другої матриці:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            cout << "Елемент [" << i << "][" << j << "]: ";
            cin >> value;
            m2.setElement(i, j, value);
        }
    }

    m2.print();
    cout << endl;

    
    Matrix m3 = m1 + m2;
    cout << "Результат додавання матриць:" << endl;
    m3.print();
    cout << endl;

    Matrix m4 = m1 - m2;
    cout << "Результат віднімання матриць:" << endl;
    m4.print();
    cout << endl;

    cout << "Кількість об'єктів: " << Matrix::getObjectCount() << endl;

    return 0;
}
