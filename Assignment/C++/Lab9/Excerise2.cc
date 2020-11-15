/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab9_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
template<int INDEX = 0>
class Rectangle
{
private:
    double height, width;
    int index = INDEX;
public:
    Rectangle() : height(0.0), width(0.0) {}
    Rectangle(const double &x, const double &y) : width(x), height(y) {}
    double getArea()
    {
        return this->height * this->width;
    }
    double getPerimeter()
    {
        return (this->height + this->width) * 2;
    }
    void display()
    {
        printf("Rectangle %d\n", this->index);
        printf("-------------------\n");
        printf("Width:\t\t%lf\n", this->width);
        printf("Height:\t\t%lf\n", this->height);
        printf("Area:\t\t%lf\n", this->getArea());
        printf("Perimeter:\t%lf\n", this->getPerimeter());
        printf("-------------------\n");
    }
};
int main()
{
    Rectangle<1> a(4, 40);
    Rectangle<2> b(3.5, 35.9);
    a.display(), b.display();
    return 0;
}