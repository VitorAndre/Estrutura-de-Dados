#include <iostream>

using namespace std;

int f(int x)
{
    if (x <= 3)
    {
        return x;
    }
    else
    {
        return f(x - 1) * f(x - 2) * f(x - 3);
    }
}

int main()
{

    cout << f(4);
    return 0;
}