#pragma once
#ifndef EXC_CANDYBAR_H
#define EXE_CANDYBAR_H
#include <bits/stdc++.h>

constexpr int LEN = 30;
typedef struct CANDYBAR
{
    char brand[LEN];
    double weight;
    int calorie;
}CandyBar;

void setCandyBar(CandyBar &cb);
void setCandyBar(CandyBar *cb);
void showCandyBar(const CandyBar &cb);
void showCandyBar(const CandyBar *cb);

#endif // EXC_CANDYBAR_H