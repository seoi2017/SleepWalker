/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab5_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
struct Pizza
{
    string company;
    int diameter;
    double weight;
    Pizza(string c, int d, double w) : company(c), diameter(d), weight(w) {}
    void display()
    {
        cout << "Displaying the information of the pizza:" << endl;
        cout << "Company Name: " << this->company << endl;
        cout << "Pizza Diameter: " << this->diameter << " inches" << endl;
        cout << "Pizza Weight: " << this->weight << " g" << endl;
    }
};
int main()
{
    string company;
    int diameter;
    double weight;
    cout << "Enter the name of pizza company: ";
    getline(cin, company);
    cout << "Enter the diameter of the pizza (inches): ";
    cin >> diameter;
    cout << "Enter the weight of the pizza (g): ";
    cin >> weight;
    Pizza *pizza = new Pizza(company, diameter, weight);
    pizza->display();
    delete pizza;
    return 0;
}