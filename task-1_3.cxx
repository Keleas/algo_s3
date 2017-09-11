/****************************************************************************
Задача 1_3

Даны четыре неотрицательных числа a, b, c и d. Сложить две
рациональные дроби a/b и c/d, а их результат представить в виде
несократимой дроби m/n. Вывести числа m и n.\
a, b, c, d ≤ 1000.

  in         | out
  -----------|-------
  3 10 5 18  | 26 45
****************************************************************************/

#include <iostream>

int gcd ( int a, int b) // greatest common divisor
{
    return ( b == 0 ) ?  a : gcd ( b, a % b);
}

int main()
{
    int a,b,c,d;
    std :: cin >> a >> b >> c >> d;

    int m = a * d + c * b;
    int n = b * d;
    int divider = gcd (n, m);

    std :: cout << m / divider << " " << n / divider << std :: endl;

    return 0;
}


