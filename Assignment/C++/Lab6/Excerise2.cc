/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab6_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
struct Box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
    Box(const char *str, float a = 0, float b = 0, float c = 0): height(a), width(b), length(c), volume(0)
    {
        memcpy(this->maker, str, sizeof(this->maker));
    }
    void display()
    {
        printf("Maker: %s\n", this->maker);
        printf("Height: %f\n", this->height);
        printf("Width: %f\n", this->width);
        printf("Length: %f\n", this->length);
        printf("Volume: %f\n", this->volume);
    }
};
inline void display(Box box)
{
    printf("Maker: %s\n", box.maker);
    printf("Height: %f\n", box.height);
    printf("Width: %f\n", box.width);
    printf("Length: %f\n", box.length);
    printf("Volume: %f\n", box.volume);
}
inline void calc(Box *box)
{
    box->volume = (box->height * box->length * box->width);
}
int main()
{
    Box box("Jack Smith", 3.4, 4.5, 5.6);
    // box.display();
    display(box);
    calc(&box);
    box.display();
    return 0;
}