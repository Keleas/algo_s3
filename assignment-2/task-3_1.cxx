/****************************************************************************
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера
n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое
бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
Напишите нерекурсивный алгоритм.

Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).

Функцию Partition следует реализовывать методом прохода двумя итераторами
в одном направлении. Описание для случая прохода от начала массива к концу:

- Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
- Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
  Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат
  нерассмотренные элементы. Последним элементом лежит опорный.
- Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
- Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
- Шаг алгоритма. Рассматривается элемент, на который указывает j.
  Если он больше опорного, то сдвигаем j.
  Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
- В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

           i,j
      а)  ▐ 2 │ 8 │ 7 │ 1 │ 3 │ 5 │ 6 ▐ 4 │
      
               i,j
      б)  ▐ 2 ▐ 8 │ 7 │ 1 │ 3 │ 5 │ 6 ▐ 4 │
      
                i   j
      в)  │ 2 ▐░8░▐ 7 │ 1 │ 3 │ 5 │ 6 ▐ 4 │

                i       j
      г)  │ 2 ▐░8░│░7░▐ 1 │ 3 │ 5 │ 6 ▐ 4 │

                    i       j
      д)  │ 2 │ 1 ▐░7░│░8░▐ 3 │ 5 │ 6 ▐ 4 │

                        i       j
      е)  │ 2 │ 1 │ 3 ▐░8░│░7░▐ 5 │ 6 ▐ 4 │

                        i           j
      ж)  │ 2 │ 1 │ 3 ▐░8░│░7░│░5░▐ 6 ▐ 4 │

                        i               j
      з)  │ 2 │ 1 │ 3 ▐░8░│░7░│░5░│░6░▐ 4 │

                        i
      и)  │ 2 │ 1 │ 3 ▐ 4 ▐░7░│░5░│░6░│░8░▐

****************************************************************************/

/****************************************************************************
Задача 3_1.

Реализуйте стратегию выбора опорного элемента "медиана трёх".
Функцию Partition реализуйте методом прохода двумя итераторами от начала
массива к концу.
****************************************************************************/


#include <iostream>

// выбор опорного элемента
// медиана трёх
template<class T>
size_t selectPivot(T *data, size_t left, size_t rght)
{
    size_t half = (left + rght - 1) / 2; // середина списка

    if(data[left] < data[half])
    {
        if(data[rght] < data[left])
            return left;
        else if(data[rght] < data[half])
            return rght;
        return half;
    }
    else
    {
        if(data[rght] < data[half])
            return half;
        else if(data[rght] < data[left])
            return rght;
        return left;
    }
}

template<class T>
size_t partition(T *data, size_t left, size_t rght)
{
    size_t pivotPos = selectPivot(data, left, rght);

    if(pivotPos != rght - 1) { // меняем местами опорный элемент с последним
        std::swap(data[rght - 1], data[pivotPos]);
    }

    size_t i = left;
    size_t j = left;
    T pivot = data[rght - 1];
    while(j < rght - 1) {
        if(data[j] <= pivot) {
            // текущий элемент не больше опорного
            // меняем его с первым из больших
            std::swap(data[i++], data[j]);
        }
        ++j;
    }
    if(i != rght - 1) { // ставим опорный элемент на место
        std::swap(data[i], data[rght - 1]);
    }
    return i;
}

// поиск к-ой порядковой статистики
template<class T>
T findKStatistics(T *data, size_t _left, size_t _rght, size_t k)
{
    size_t lastPivotPos = 0;
    size_t left = _left;
    size_t right = _rght;

    while(left < right) {
        if((lastPivotPos = partition(data, left, right)) == k)
            return data[lastPivotPos];
        else if(lastPivotPos > k) {
            // опорный элемент оказался правее искомого
            right = lastPivotPos;
        }
        else
        {
            // опорный элемент не дошел до искомого
            left = lastPivotPos + 1;
        }
    }
    return data[lastPivotPos];
}

int main()
{
    size_t n = 0; // количество элементов в массиве
    size_t k = 0; // номер для поиска порядковой статистики
    std::cin >> n >> k;

    int *arr = new int[n];
    for(size_t i = 0; i < (size_t) n; ++i)
        std::cin >> arr[i];

    std::cout << findKStatistics(arr, 0, (size_t) n, k);

    delete[] arr;

    return 0;
}
