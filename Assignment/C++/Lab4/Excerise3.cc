/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise3
*/
#include <bits/stdc++.h>
using namespace std;
inline bool isLetter(char chr)
{
    if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
        return true;
    if (chr == ' ')
        return true;
    return false;
}
inline string turn(string str)
{
    for (int i = 0; i < str.length(); ++i)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = 'A' + (str[i] - 'a');
    return str;
}
int main()
{
    string str;
    getline(cin, str);
    for (string::iterator i = str.begin(); i != str.end(); ++i)
    {
        if(isLetter(*i) == false)
        {
            str.erase(i);
            --i;
        }
    }
    // cout << str << endl;
    // cout << turn(str) << endl;
    freopen("f1.txt", "w", stdout);
    printf("%s", str.c_str());
    fclose(stdout);
    freopen("f2.txt", "w", stdout);
    printf("%s", turn(str).c_str());
    fclose(stdout);
    return 0;
}
// Hi! I am Candy, 18 years old.