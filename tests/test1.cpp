#include "test.h"


Test(FirstTest)
{
    int a = 5;
    int b = 3;

    Check(a, ==, b);
    Check(a, ==, 5);
}


int main()
{
    RunAllTests();
}