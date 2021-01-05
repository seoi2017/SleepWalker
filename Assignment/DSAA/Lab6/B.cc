/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_B
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
#define MAX_STRING 1000010
char a[MAX_STRING];
int nextArray[MAX_STRING];              //next数组。
void find_next(char str[])
{                          //写成"char* str"也可。
    int len = strlen(str); //取字符串长度。
    nextArray[0] = -1;          //第0位不可能有公共前后缀，故值为-1。
    for (int i = 1, j; i < len; i++)
    {                    //从第1位开始寻找每位的next值。
        j = nextArray[i - 1]; //得到前一位的next值
        while ((j >= 0) && (str[j + 1] != str[i]))
        {                //如果j>=0则说明前一位有公共前后缀，若从上一位公共前后缀的下一位开始失配，则通过已有的next值向前回溯。
            j = nextArray[j]; //通过已有的next值向前回溯，直到找到公共前后缀(str[j+1]==str[i])或者完全不匹配(j==-1)。
        }
        //到这里，第i位的公共前后缀计算完成。
        if (str[i] == str[j + 1])
        {                    //若找到公共前后缀。
            nextArray[i] = j + 1; //得到第i位的next为j+1。
        }
        else
        {                 //若没有找到。
            nextArray[i] = -1; //就设next为-1。
        }
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%s", a);
    find_next(a);
    int len = strlen(a);
    for (int i = 0; i < len; ++i)
        printf("%d\n", nextArray[i] + 1);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}