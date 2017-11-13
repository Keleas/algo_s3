/****************************************************************************
Задача 3_2.

Дан массив целых чисел А[0..n-1]. Известно, что на интервале
[0, m] значения массива строго возрастают, а на интервале [m, n-1]
строго убывают. Найти m за O(log m).
2 ≤ n ≤ 10000.

  in                   | out
  ---------------------|-----
  10                   | 6
  1 2 3 4 5 6 7 6 5 4  |

****************************************************************************/


#include <iostream>

//similar to binary search
//in this problem we take a partition into 3 segments
int main()
{
    int n;
    std::cin >> n;
    int* A = new int[n];
    for(int i = 0; i < n; ++i)
        std::cin >> A[i];

    int left = -1;
    int right = n;
    while(right - left >= 3)
    {
        int mid1 = left + (right-left)/3;
        int mid2 = right - (right-left)/3;

        if(A[mid1] < A[mid2]) left = mid1;
        else right = mid2;
    }
    std::cout << right -1 << std::endl;

    delete [] A;

    return 0;
}

