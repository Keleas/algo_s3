/****************************************************************************
Задача 1_1

Найти, на сколько нулей оканчивается n! = 1 * 2 * 3 * … * n.
n <= 1000.

  in  | out
  ----|-----
  25  | 6
****************************************************************************/

#include <iostream>

int fact ( int n, int divider )
{
    int count = 0;

    while ( n )
    {
        n /= divider;
        count += n;
    }
    return count;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << fact(n,5);

    return 0;
}


