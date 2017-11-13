/****************************************************************************
Задача 6_1. Соревнование

**Быстрейшая сортировка.**

Дан массив целых чисел в диапазоне [0..10^9]. Размер массива кратен 10
и ограничен сверху значением 2.5 * 10^6 элементов. Все значения массива
являются элементами псевдо-рандомной последовательности. Необходимо
отсортировать элементы массива за минимальное время и вывести каждый
**десятый** элемент отсортированной последовательности.

Реализуйте сортировку, основанную на QuickSort.

Минимальный набор оптимизаций, который необходимо реализовать:

1. Оптимизация ввода/вывода

2. Оптимизация выбора опорного элемента

3. Оптимизация Partition

4. Написать без рекурсии

5. Оптимизация концевой рекурсии

Задача обязательная.

За первое место в сдвоенной группе + 15 баллов.

За второе место + 10 баллов.

За третье место + 5 баллов.

in                   | out
-------------------- | ---
3 0 2 1 5 4 21 4 6 5 | 21

****************************************************************************/

#include <iostream>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <ctime>

#define STACK_MIN_LENGTH 10
#define QUICK_SORT_STOP_LENGTH 7
#define MY_MAX 2500000

template<class T>
class Stack {
public:
    Stack(int size = STACK_MIN_LENGTH) : _buffer(NULL), _bufferSize(0), _size(0) {
        _resize(size);
    }

    ~Stack() {
        delete[] _buffer;
    }

    bool isEmpty() {
        return _size < 1;
    }


    void push(const T &val) {
        if(_size == _bufferSize) {
            _resize(_bufferSize * 2);
        }

        _buffer[_size++] = val;
    }


    T pop() {
        assert(!isEmpty());
        return _buffer[--_size];
    }

private:
    T *_buffer; //буффер
    int _bufferSize; //выделенное место под буффер
    int _size; //реальное кол-во эл-ов

    //выделение памяти
    void _resize(int newBufferSize = STACK_MIN_LENGTH) {
        T *newBuffer = new T[newBufferSize];

        if(_buffer != NULL && _size > 0) {
            memmove(newBuffer, _buffer, _size * sizeof(T));
        }

        delete[] _buffer;
        _buffer = newBuffer;
        _bufferSize = newBufferSize;
    }

};

// выбираем опорный элемент
// медиана трёх
template<class T>
int getPivot(T *data, int start, int end) {
    int pivotPos = 0, half = (start + end - 1) / 2 - 1;
    if (data[start] < data[half]) {
        pivotPos = 0;
        if (data[half] < data[end - 1]) {
            pivotPos = half;
        }
        else if(data[start] < data[end - 1]) {
            pivotPos = end - 1;
        }
    }
    else
    {
        pivotPos = end - 1;
        if (data[end - 1] < data[half]) {
            pivotPos = half;
        }
        else if (data[start] < data[end - 1]) {
            pivotPos = start;
        }
    }
    return pivotPos;
}


template<class T>
int partition(T *data, int start, int end) {
    int pivotPos = getPivot(data, start, end);
    if (pivotPos < start)
        pivotPos = start;
    if (pivotPos > end)
        pivotPos = end;

    if (start == end)
        return pivotPos;

    std::swap(data[pivotPos], data[end]);
    pivotPos = end;

    int i = start;
    int j = start;
    while(j < end) {
        if(data[j] <= data[pivotPos]) {
            if (i != j)
                std::swap(data[j], data[i]);
            ++i;
            ++j;
        }
        if(j < end) {
            while(data[j] > data[pivotPos]) {
                if(++j == end) break;
            }
        }
    }
    std::swap(data[i], data[pivotPos]);
    pivotPos = i;
    return pivotPos;
}


template<class T>
void quickSort(T *data, int start, int end) {
    Stack<int> stack(2 * log2(end - start) + 2);
    // предполагаем, что в один момент времени в стеке будет log2(n) "вызовов" qsort

    int first = start;
    int last = end - 1;
    stack.push(first);
    stack.push(last);
    int pivotPos = 0;

    //вместо рекурсии
    while(!stack.isEmpty()) {
        last = stack.pop();
        first = stack.pop();

        if(last - first < QUICK_SORT_STOP_LENGTH) {
            continue;
        }
        else
        {
            pivotPos = partition<T>(data, first, last);

            if(pivotPos < last) {
                stack.push(pivotPos + 1);
                stack.push(last);
            }
            if(first < pivotPos - 1) {
                stack.push(first);
                stack.push(pivotPos - 1);
            }
        }

    }
}

template<class T>
void insertionSort(T *data, int left, int right) {
    for (int i = left + 1; i < right; i++) {
        // бинарный поиск места вставки
        int l = 0, r = i;
        T toSearch = data[i];
        while(l < r) {
            int middle = (l + r) / 2;
            if(toSearch > data[middle]) {
                l = middle + 1;
            }
            else {
                r = middle;
            }
        }

        int position = r;
        if(position < i ) {
            T temp = data[i];
            memmove(&data[position+1], &data[position], (i - position) * sizeof(T));
            data[position] = temp;
        }
    }
}

// функция для контеста
void FastSort(int *data, int n) {
    // сначала быстрая сортировка
    quickSort(data, 0, n);
    // а потом вставками подкорректируем
    insertionSort(data, 0, n);
}


int main()
{
/* для контеста

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::srand(time(0));
        int a;
        int* parr = new int[MY_MAX];
        int index = 0;
        while(std::cin) {
            std::cin >> a;
            parr[index++] = a;
        }

        FastSort(parr, index-1);

        for(size_t i = 9; i < index-1; i+=10) {
            std::cout << parr[i] << " ";
        }

        delete[] parr;
*/

    /* генератор данных для сортировки

    std::ofstream fout("E:\\sort_test.txt");
    for(size_t i = 0; i < MY_MAX; ++i) {
        fout << std::rand() % 500 - std::rand() % 500 << " ";
    }
    */

    std::srand(time(0));

    std::ifstream ifs("E:\\sort_test1.txt");
    if(!ifs)
        std::cout << "you're so stupid \n";

    int* memory = new int[MY_MAX];
    int index = 0;
    int val;
    while(ifs >> val) {
        memory[index++] = val;
    }

    FastSort(memory, index-1);

    std::cout << "runtime = " << clock()/1000.0;
    delete[] memory;

   return 0;
}
