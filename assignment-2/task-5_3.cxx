/****************************************************************************

Задача 5_3. Binary MSD для long long.

Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не
больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).

in          | out
----------- | ---
3           | 4 7 1000000
4 1000000 7 |

****************************************************************************/

/****************************************************************************
Идея:

Применим бинарный QuickSort. Пробегаем по страшим разрядам чисел (в двоичной
системе), сортируем. Затем запускаем аналогичные итерации для следующего разряда
чисел в массиве. Идеология основана на QuickSort.

****************************************************************************/

#include <iostream>
#include <bitset>


void BitSort(std::bitset<64>* arr, int start, int finsh, int bit) {
    if(bit < 0 || start >= finsh) return;
    int right = start;
    int left = finsh;

    do
    {
        //встречаем первый ноль (бежим на увелечение)
        while(arr[right][bit] != 1 && right <= left)
                right++;
        //встречаем первую единицу (бежим на уменьшение)
        while(arr[left][bit] != 0 && right <= left)
                left--;
        if(right <= left) {
            if(right < left) {
                std::swap(arr[right], arr[left]);
            }
            //переход к следующим эл-ам
            right++;
            left--;
        }
    } while (right <= left);

    if(left > start)
        BitSort(arr, start, left, bit-1);

    if(right < finsh)
        BitSort(arr, right, finsh, bit-1);
}



int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    size_t n;
    std::cin >> n;
    long long* arr = new long long[n];
    std::bitset<64>* byte_arr = new std::bitset<64>[n];
    for(size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
        byte_arr[i] = arr[i];
    }

    BitSort(byte_arr, 0, n-1, 63);

    for(size_t i = 0; i < n; ++i)
       std::cout << byte_arr[i].to_ullong() << " ";
    std::cout << std::endl;

    delete[] arr;
    delete[] byte_arr;

    return 0;
}
