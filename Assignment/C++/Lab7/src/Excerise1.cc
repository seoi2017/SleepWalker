#include "CandyBar.h"
int main()
{
    CandyBar cb;
    setCandyBar(cb);
    showCandyBar(cb);
    setCandyBar(&cb);
    showCandyBar(&cb);
    return 0;
}