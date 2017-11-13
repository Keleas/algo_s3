/****************************************************************************
Задача 3_1.

Дан отсортированный массив целых чисел A[0..n-1] и массив
целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите
минимальный индекс k минимального элемента массива A, равного или
превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет,
выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)).
n, m ≤ 10000.

*Формат входных данных.*
В первой строчке записаны числа n и m. Во второй и третьей массивы A и B
соответственно.

  in       | out
  ---------|-------
  2 1      | 1
  1 2      |
  2        |

  in       | out
  ---------|-------
  4 3      | 1 3 0
  2 4 5 7  |
  4 6 1    |

****************************************************************************/

#include <iostream>

//use binary search
//with changes to search for the minimum index
//array A[], namely the shift of the slider to the right,
//if in a row there are the same elements
int binSearch(const int key, const int *arr, const int size)
{
    int left = -1;
    int right = size;
    //in the case where the number is greater than the key in A[],
    //return the largest element
    int minArr = arr[size-1];
    while(left < right -1)
    {
        int mid = (left+right) / 2;
        if(arr[mid] < key)
            left = mid;
        else if (arr[mid] >= key && arr[mid] <= minArr){
            right = mid;
            minArr = arr[mid];
        }
    }
    return right;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    int* A = new int[n];
    int* B = new int[m];

    for(int i = 0; i< n; ++i)
        std::cin >> A[i];

    for(int i = 0; i< m; ++i)
        std::cin >> B[i];

    for(int i = 0; i < m; ++i)
        std::cout << binSearch(B[i], A, n) << " ";

    delete [] A;
    delete [] B;

    return 0;
}
