/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab7_Excerise1
*/
#include "CandyBar.h"
void setCandyBar(CandyBar &cb)
{
    printf("Call the set function of Passing by reference:\n");
    printf("Enter brand name of a Candy bar:");
    scanf("\n%[^\n]", cb.brand);
    printf("Enter weight of the Candy bar:");
    scanf("%lf", &cb.weight);
    printf("Enter calories (an integer value) in the Candy bar:");
    scanf("%d", &cb.calorie);
}
void setCandyBar(CandyBar *cb)
{
    printf("Call the set function of Passing by pointer:\n");
    printf("Enter brand name of a Candy bar:");
    scanf("\n%[^\n]", cb->brand);
    printf("Enter weight of the Candy bar:");
    scanf("%lf", &cb->weight);
    printf("Enter calories (an integer value) in the Candy bar:");
    scanf("%d", &cb->calorie);
}
void showCandyBar(const CandyBar &cb)
{
    printf("Call the show function of Passing by reference:\n");
    printf("Brand: %s\n", cb.brand);
    printf("Weight: %f\n", cb.weight);
    printf("Calories: %d\n", cb.calorie);
}
void showCandyBar(const CandyBar *cb)
{
    printf("Call the show function of Passing by pointer:\n");
    printf("Brand: %s\n", cb->brand);
    printf("Weight: %f\n", cb->weight);
    printf("Calories: %d\n", cb->calorie);
}