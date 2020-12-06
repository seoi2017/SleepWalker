/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab12_Excerise1_to_4
*/
#include <bits/stdc++.h>

using namespace std;

class CStereoShape
{
private:
    static int numberOfObject;
public:
    CStereoShape()
    {
        ++CStereoShape::numberOfObject;
    }
    ~CStereoShape()
    {
        --CStereoShape::numberOfObject;
    }
    virtual double GetArea()
    {
        cout << "CStereoShape::GetArea()" << endl;
        return 0.0;
    }
    virtual double GetVolume()
    {
        cout << "CStereoShape::GetVolume()" << endl;
        return 0.0;
    }
    virtual void Show()
    {
        cout << "CStereoShape::Show()" << endl;
    }
    int GetNumOfObject()
    {
        return CStereoShape::numberOfObject;
    }
};

class CCube : public CStereoShape
{
private:
    double length, width, height;
public:
    CCube() : CStereoShape()
    {
        this->length = 0.0;
        this->width = 0.0;
        this->height = 0.0;
    }
    CCube(const double& length, const double& width, const double& height) : CStereoShape()
    {
        this->length = length;
        this->width = width;
        this->height = height;
    }
    CCube(const CCube& other) : CStereoShape()
    {
        this->length = other.length;
        this->width = other.width;
        this->height = other.height;
    }
    double GetArea()
    {
        cout << "CCube::GetArea()" << endl;
        return ((this->length * this->width) + (this->height * this->length) + (this->width * this->height)) * 2;
    }
    double GetVolume()
    {
        cout << "CCube::GetVolume()" << endl;
        return (this->length * this->height * this->width);
    }
    void Show()
    {
        cout << "CCube::Show()" << endl;
        cout << "================================" << endl;
        cout << "Length: " << this->length << endl;
        cout << "Height: " << this->height << endl;
        cout << "Width: " << this->width << endl;
        cout << "================================" << endl;
    }
};

class CSphare : public CStereoShape
{
private:
    static constexpr double pi = 3.14159265;
    double radius;
public:
    CSphare() : CStereoShape()
    {
        this->radius = 0.0;
    }
    CSphare(const double& radius) : CStereoShape()
    {
        this->radius = radius;
    }
    CSphare(const CSphare& other) : CStereoShape()
    {
        this->radius = other.radius;
    }
    double GetArea()
    {
        cout << "CSphare::GetArea()" << endl;
        return (4.0 * CSphare::pi * this->radius * this->radius);
    }
    double GetVolume()
    {
        cout << "CSphare::GetVolume()" << endl;
        return (4.0 / 3.0 * CSphare::pi * this->radius * this->radius * this->radius);
    }
    void Show()
    {
        cout << "CSphare::Show()" << endl;
        cout << "================================" << endl;
        cout << "Radius: " << this->radius << endl;
        cout << "================================" << endl;
    }
};

int CStereoShape::numberOfObject = 0;

int main()
{
    CCube a_cube(4.0, 5.0, 6.0);
    CSphare c_sphere(7.9);
    CStereoShape* p = &a_cube;
    p->Show();
    p = &c_sphere;
    p->Show();
    cout << p->GetNumOfObject() << endl;
    return 0;
}