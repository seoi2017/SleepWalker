/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
struct CandyBar
{
    string name;
    double weight;
    int noc;
    CandyBar() {}
    CandyBar(string name, double weight, int noc) : name(name), weight(weight), noc(noc) {}
    inline void output()
    {
        cout << "Brand: " << this->name << endl;
        cout << "Weight: " << this->weight << endl;
        cout << "Calories: " << this->noc << endl;
    }
    inline void output__()
    {
        cout << "Brand: " << this->name << endl;
        cout << "Calories per weight: " << this->noc / this->weight << endl;
    }
    bool operator<(const CandyBar &x) const
    {
        return (this->noc / this->weight) < (x.noc / x.weight);
    }
};
int main()
{
    string name;
    double weight;
    int noc;
    CandyBar obj[3];
    cout << "Pleast input three CandyBar's information:" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "Enter brand name of a Candy bar: ";
        getline(cin, name);
        cout << "Enter weight of the Candy bar: ";
        cin >> weight;
        cout << "Enter calories (an integer value) in the Candy bar: ";
        cin >> noc;
        cin.get();
        obj[i] = CandyBar(name, weight, noc);
    }
    sort(obj, obj + 3);
    cout << endl << "Displaying the CandyBar array contents:" << endl;
    for (auto i : obj)
        i.output();
    cout << endl << "The greatest calories per weight is:" << endl;
    obj[2].output__();
    return 0;
}