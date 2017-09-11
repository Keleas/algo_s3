/****************************************************************************
Задача 1_4.

Дано натуральное число N. Представить N в виде A + B, так, что
НОД(A, B) максимален, A ≤ B. Вывести A и B. Если возможно несколько
ответов - вывести ответ с минимальным A.
n ≤ 10^7.

  in  | out
  ----|------
  35  | 7 28
****************************************************************************/

#include <iostream>
#include <cmath>


int fsd ( int n ) // first simple divisor
{
    for ( int i = 3; i <= sqrt(n); ++i )
        if ( n % i == 0 ) return i;
    return 1;
}

int main()
{
    int n;
    std :: cin >> n;

    if ( n % 2 != 0)
    {
        int div = fsd (n);
        if ( div != 1 ) std :: cout << n/div << " " << (div - 1) * (n / div) << std :: endl;
            else  std :: cout << 1 << " " << n - 1 << std :: endl;
     }
    else std :: cout << n/2 << " " << n/2 << std :: endl;

    return 0;
}


