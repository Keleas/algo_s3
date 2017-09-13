/****************************************************************************
Задача 1_6.

Дан массив целых чисел A\[0..n). Не используя других массивов
переставить элементы массива A в обратном порядке за O(n).
n ≤ 10000.

  in        | out
  ----------|----------
  4         | 2 -5 9 3
  3 9 -5 2  | 
****************************************************************************/

#include <iostream>

int main()
{
  int n;
  std::cin >> n;
  int *arr = new int[n];

  for ( int i = 0; i < n ; ++i )
    std::cin >> arr[i];

  for ( int i = 0; i < n/2; ++i )
    std::swap(arr[i], arr[n - i - 1] );

  for ( int i = 0; i < n ; ++i )
    std::cout << arr[i] << " ";
  
  delete [] arr;

  return 0;
}


