/****************************************************************************
Задача 3_4.

Дан отсортированный массив различных целых чисел A[0..n-1] и
массив целых чисел B[0..m-1]. Для каждого элемента массива B[i]
найдите минимальный индекс элемента массива A[k], ближайшего по
значению к B[i]. Время работы поиска для каждого элемента B[i]:
O(log(k)).
n ≤ 110000, m ≤ 1000.

 in          | out
-------------|-----------
 3           | 0 0 2
 10 20 30    |
 3           |
 9 15 35     |

 in          | out
-------------|-----------
 3           | 0 0 0 2
 10 20 30    |
 4           |
 8 9 10 32   |

****************************************************************************/

#include <iostream>

/****************************************************************************
Идея:
бинарным поиском ищем 2 элемента массива A[],
между которыми лежит наше число из B[],
а затем смотрим, где разница меньше:
от левого числа или правого, и соответственно выводим что подходит.
****************************************************************************/
int binSearch(const int key, const int *arr, const int size)
{
    int left = -1;
    int right = size;
    while(left < right -1)
    {
        int mid = (left+right) / 2;
        if(arr[mid] <= key)
            left = mid;
        else if (arr[mid] >= key)
            right = mid;
    }
    //Небольшой костыль для правильного вывода крайних случаев:
    //нужный элемент самый первый или последний.
    if(right == size) --right;
    if(left == -1) ++left;
    return (key-arr[left] <= arr[right]-key) ? left : right;
}

int main()
{
    int n;
    std::cin >> n;
    int* A = new int[n];
    for(int i = 0; i < n; ++i)
        std::cin >> A[i];

    int m;
    std::cin >> m;
    int* B = new int[m];
    for(int i = 0; i < m; ++i)
        std::cin >> B[i];

    for(int i = 0; i < m; ++i)
        std::cout << binSearch(B[i], A, n) << " ";

    delete [] A;
    delete [] B;

    return 0;
}

