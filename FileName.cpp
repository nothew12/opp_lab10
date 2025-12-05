#include <iostream>
#include <cmath>
#include<Windows.h>
using namespace std;


class Triangle {
public:
    virtual double getSideA() const = 0;
    virtual double getSideB() const = 0;
    virtual double getSideC() const = 0;

   
    double median(char side) const {
        double a = getSideA();
        double b = getSideB();
        double c = getSideC();

        if (side == 'a') return 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
        if (side == 'b') return 0.5 * sqrt(2 * a * a + 2 * c * c - b * b);
        if (side == 'c') return 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);
        throw invalid_argument("Невірна сторона");
    }

    
    double midline(char side) const {
        if (side == 'a') return getSideA() / 2.0;
        if (side == 'b') return getSideB() / 2.0;
        if (side == 'c') return getSideC() / 2.0;
        throw invalid_argument("Невірна сторона");
    }

    virtual ~Triangle() {}
};


class TriangleByVertices : public Triangle {
    double x1, y1, x2, y2, x3, y3;

    double dist(double x1, double y1, double x2, double y2) const {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

public:
    TriangleByVertices(double X1, double Y1,
        double X2, double Y2,
        double X3, double Y3)
        : x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3) {
    }

    double getSideA() const override { return dist(x2, y2, x3, y3); }
    double getSideB() const override { return dist(x1, y1, x3, y3); }
    double getSideC() const override { return dist(x1, y1, x2, y2); }
};



class TriangleBySides : public Triangle {
    double a, b, c;
public:
    TriangleBySides(double A, double B, double C) : a(A), b(B), c(C) {}

    double getSideA() const override { return a; }
    double getSideB() const override { return b; }
    double getSideC() const override { return c; }
};



class TriangleByMedians : public Triangle {
    double a, b, c;

public:
    TriangleByMedians(double ma, double mb, double mc) {
        a = (2.0 / 3.0) * sqrt(2 * mb * mb + 2 * mc * mc - ma * ma);
        b = (2.0 / 3.0) * sqrt(2 * ma * ma + 2 * mc * mc - mb * mb);
        c = (2.0 / 3.0) * sqrt(2 * ma * ma + 2 * mb * mb - mc * mc);
    }

    double getSideA() const override { return a; }
    double getSideB() const override { return b; }
    double getSideC() const override { return c; }
};


class RightTriangle : public TriangleBySides {
public:
    RightTriangle(double a, double b) : TriangleBySides(a, b, sqrt(a* a + b * b)) {}

    double inradius() const {
        double a = getSideA(), b = getSideB(), c = getSideC();
        return (a + b - c) / 2.0;
    }

    double circumradius() const {
        return getSideC() / 2.0;
    }
};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Triangle* t1 = new TriangleByVertices(0, 0, 3, 0, 0, 4);
    cout << "Медіана до сторони a = " << t1->median('a') << endl;
    cout << "Середня лінія паралельна стороні b = " << t1->midline('b') << endl;

    Triangle* t2 = new TriangleByMedians(5, 6, 7);
    cout << "Сторона a з медіан = " << t2->getSideA() << endl;

    RightTriangle rt(3, 4);
    cout << "Вписане коло r = " << rt.inradius() << endl;
    cout << "Описане коло R = " << rt.circumradius() << endl;

    delete t1;
    delete t2;
    return 0;
}