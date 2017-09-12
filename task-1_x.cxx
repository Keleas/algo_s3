/****************************************************************************
Задача 1_*.

Найти все простые числа в диапазоне \[2..n\] за O(n).

  in  | out
  ----|---------------
  15  | 2 3 5 7 11 13

****************************************************************************/
#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    int *compNum = new int [n+1];
    // массив, в котором будем отслеживать составные числа
    // compNum[i] != 0  ==> оно составное
    std::vector<int> prNum;
    // запоминаем простые числа
    for ( int i = 0; i <= n+1; ++i )
        compNum[i] = 0;
    // изначальное предположение , что все числа простые

    for ( int i = 2; i <= n; ++i )
    {
        if ( compNum[i] == 0) {
            compNum[i] = i;
            prNum.push_back(i);
        }
        // добавляем простые числа

        for ( int j = 0; j < prNum.size() && prNum[j] <= compNum[i] && i*prNum[j] <= n; ++j )
            compNum[ i * prNum[j] ] = prNum[j];
            // так мы забиваем все составные числа ненулевыми значениями
            // в весь массив compNum[]
    }

    for ( int i = 0; i < prNum.size(); ++i )
        std::cout << prNum[i] << " ";

    return 0;
}