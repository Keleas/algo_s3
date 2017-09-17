/****************************************************************************
Задача 3_3.

Даны два массива неповторяющихся целых чисел, упорядоченные по
возрастанию. A[0..n-1] и B[0..m-1]. n >> m. Найдите их
пересечение. Требуемое время работы: O(m * log k), где k - позиция
элементта B[m-1] в массиве A. В процессе поиска очередного элемента
B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
n, k ≤ 10000.

  in         | out
  -----------|-------
  5          | 1 3 5
  3          |
  1 2 3 4 5  |
  1 3 5      |
****************************************************************************/

#include <iostream>

/****************************************************************************
 Идея:
И снова мы берем двоичный поиск, но теперь
вносим корректировку в функцию поиска: передаем
левую границу для каждого поиска, чтобы учесть результат
посика для B[i-1].
****************************************************************************/

int binSearch(const int key, const int *arr, const int size, int lft)
{
    int left = lft-1;
    int right = size;
    while(left < right-1)
    {
        int mid = (left+right) /2;
        if(arr[mid] < key) left = mid;
        else  right = mid;
    }
    return right;
}

int main()
{
    int n, m;
    std::cin >> n  >> m;
    int* A = new int[n];
    int* B = new int[m];

    for(int i = 0; i < n; ++i)
        std::cin >> A[i];

    for(int i = 0; i < m; ++i)
        std::cin >> B[i];
    //счетчик для сужения границ нового поиска
    int left = 0;
    for(int i = 0; i <m; ++i)
    {
        left = binSearch(B[i], A, n, left);
        if(A[left] == B[i]) std::cout << A[left] << " ";
    }

    delete [] A;
    delete [] B;

    return 0;
}

