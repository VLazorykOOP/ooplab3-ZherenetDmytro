#include <iostream>
#include <string>
using namespace std;

class Parallelogram {
private:
    double base;         
    double height;      
    double side;          
    string color;         

public:
    
    Parallelogram() : base(1.0), height(1.0), side(1.0), color("White") {}

    
    Parallelogram(double b, double h, double s, string c) {
        setBase(b);
        setHeight(h);
        setSide(s);
        setColor(c);
    }

    
    double area() const {
        return base * height;
    }

    
    double perimeter() const {
        return 2 * (base + side);
    }

    
    void setBase(double b) {
        if (b > 0) {
            base = b;
        } else {
            cout << "Невірне значення основи. Основу слід задавати більше за 0." << endl;
        }
    }

    void setHeight(double h) {
        if (h > 0) {
            height = h;
        } else {
            cout << "Невірне значення висоти. Висоту слід задавати більше за 0." << endl;
        }
    }

    void setSide(double s) {
        if (s > 0) {
            side = s;
        } else {
            cout << "Невірне значення бічної сторони. Бічну сторону слід задавати більше за 0." << endl;
        }
    }

    void setColor(const string &c) {
        if (c.empty()) {
            cout << "Невірне значення кольору. Колір не може бути порожнім." << endl;
        } else {
            color = c;
        }
    }

    
    double getBase() const {
        return base;
    }

    double getHeight() const {
        return height;
    }

    double getSide() const {
        return side;
    }

    string getColor() const {
        return color;
    }

    
    void print() const {
        cout << "Паралелограм: " << endl;
        cout << "Основа: " << base << endl;
        cout << "Висота: " << height << endl;
        cout << "Бічна сторона: " << side << endl;
        cout << "Колір: " << color << endl;
        cout << "Площа: " << area() << endl;
        cout << "Периметр: " << perimeter() << endl;
    }
};

int main() {
    double base, height, side;
    string color;
    
    cout << "Тест 1: Використання конструктора за замовчуванням:" << endl;
    Parallelogram p1;
    p1.print();
    
    cout << "\nТест 2: Використання конструктора з параметрами:" << endl;
    Parallelogram p2(5.0, 3.0, 4.0, "Red");
    p2.print();

    cout << "\nТест 3: Встановлення значень через функції-члени:" << endl;
    p2.setBase(7.0);
    p2.setHeight(5.0);
    p2.setSide(6.0);
    p2.setColor("Blue");
    p2.print();

    
    cout << "\nТест 4: Некоректне значення для основи:" << endl;
    p2.setBase(-3.0);
    p2.setHeight(-2.0);
    p2.setSide(-4.0);
    p2.setColor("");

    
    cout << "Введіть основу паралелограма: ";
    cin >> base;
    
    cout << "Введіть висоту паралелограма: ";
    cin >> height;
    
    cout << "Введіть бічну сторону паралелограма: ";
    cin >> side;
    
    cout << "Введіть колір паралелограма: ";
    cin.ignore();  
    getline(cin, color);

    
    Parallelogram p(base, height, side, color);

    
    p.print();

    

    return 0;
}

