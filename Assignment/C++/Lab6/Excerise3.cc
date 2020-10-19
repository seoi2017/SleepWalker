/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab6_Excerise3
*/
#include <bits/stdc++.h>
using namespace std;
int Fill_array(double arr[], const int &size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("Enter value #%d: ", i + 1);
        if (scanf("%lf", arr + i) == 0)
            return i;
    }
    return size;
}
void Show_array(double *arr, const int &size)
{
    for (int i = 0; i < size; ++i)
        printf("%.0lf ", *(arr + i));
    printf("\n");
}
void Reverse_array(double *arr, const int &size)
{
    for (int i = 0; i < size / 2; ++i)
        swap(*(arr + i), *(arr + size - i - 1));
}
int main()
{
    int size;
    printf("Enter the size of an array: ");
    scanf("%d", &size);
    double *arr = new double[size];
    size = Fill_array(arr, size);
    Show_array(arr, size);
    Reverse_array(arr, size);
    Show_array(arr, size);
    Reverse_array(arr + 1, size - 2);
    Show_array(arr, size);
    return 0;
}