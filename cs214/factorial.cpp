#include <iostream>
#include <cmath>

using namespace std;

int factorial(int n)
{
    int product = 1;
    while (n > 1)
    {
        product *= n;
        n--;
    }
    return product;
}


int main()
{
    int *a;

    *a = 5;

    cout << a << endl;
    return 0;
}
