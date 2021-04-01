#include "test.h"

int Fibonacci(int n)
{
    if (n <= 1)
        return n;
    else
        return Fibonacci(n-1) + Fibonacci(n-2);
}


Test(FirstTest)
{
    Check(Fibonacci(9), ==, 34);
}


int main()
{
    RunAllTests();
}