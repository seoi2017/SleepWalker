/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab9_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
class CandyBar
{
private:
    char name[256];
    double weight;
    int calorie;
public:
    void setCandyBar()
    {
        printf("Enter the brand name of the candy bar: ");
        scanf("%[^\n]", this->name);
        printf("Enter the weight of the candy bar: ");
        scanf("%lf", &this->weight);
        printf("Enter calories(an integer value) in the candy bar: ");
        scanf("%d", &this->calorie);
    }
    void showCandyBar()
    {
        printf("Brand: %s\n", this->name);
        printf("Weight: %lf\n", this->weight);
        printf("Calories: %d\n", this->calorie);
    }
};
int main()
{
    CandyBar cb;
    cb.setCandyBar();
    cb.showCandyBar();
    return 0;
}