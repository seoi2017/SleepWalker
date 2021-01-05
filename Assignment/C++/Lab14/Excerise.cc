/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab14_Excerise
*/
#include <bits/stdc++.h>
using namespace std;
class OutOfRangeException : public exception
{
private:
    char* message;
public:
    OutOfRangeException(const char* message) : exception()
    {
        this->message = new char[strlen(message)];
        memcpy(this->message, message, strlen(message));
    }
    const char* what() const throw()
    {
        return this->message;
    }
};
float calculateAverage()
{
    vector<int> input(4);
    float result = 0.0f;
    for (int& i : input)
        cin >> i;
    for (int i : input)
        if (i < 0 || i > 100)
            throw OutOfRangeException("Parameter out of range.");
        else
            result += (float)i;
    return result / 4.0f;
}
int main()
{
    char oper;
    begin:
    try
    {
        cout << "Please enter marks for 4 courses: ";
        float ans = calculateAverage();
        cout << "The average of the four courses is: " << ans << endl;
    }
    catch (const OutOfRangeException& e)
    {
        cerr << e.what() << endl;
        cout << "Would you want to enter another marks for 4 courses(y/n)? ";
        if (cin >> oper; oper == 'y')
            goto begin;
        else if (oper == 'n')
            cout << "Bye, see you next time." << endl;
        else
            cout << "Sorry, unknown input" << endl;
    }
    return 0;
}