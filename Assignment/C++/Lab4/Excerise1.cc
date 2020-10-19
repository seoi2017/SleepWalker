/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab4_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
struct CandyBar
{
    string name;
    double weight;
    int noc;
    CandyBar(string name, double weight, int noc) : name(name), weight(weight), noc(noc) {}
    inline void output()
    {
        cout << "Brand: " << this->name << endl;
        cout << "Weight: " << this->weight << endl;
        cout << "Calories: " << this->noc << endl;
    }
};
int main()
{
    string name;
    double weight;
    int noc;
    cout << "Enter brand name of a Candy bar: ";
    getline(cin, name);
    cout << "Enter weight of the Candy bar: ";
    cin >> weight;
    cout << "Enter calories (an integer value) in the Candy bar: ";
    cin >> noc;
    CandyBar obj(name, weight, noc);
    obj.output();
    return 0;
}