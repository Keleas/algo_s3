/****************************************************************************
 Задача 4_1. Первые k элементов длинной последовательности.

Дана очень длинная последовательность целых чисел длины n. Требуется вывести
в отсортированном виде её первые k элементов. Последовательность может не
помещаться в память. Время работы O(n * log(k)). Доп. память O(k).
Использовать слияние.

in                 | out
------------------ | ---
9 4                | 1 2 3 4
3 7 4 5 6 1 15 4 2 |

****************************************************************************/

#include <iostream>

template<class T>
class LimitedMerger {
public:
    LimitedMerger(): _data{nullptr}, _realLength{0}, _maxLength{0}
    {}

    LimitedMerger(size_t k) {
        _realLength = 0;
        _reserveMemory(k);
    }

    ~LimitedMerger() {
        delete[] _data;
    }


    // сливает новый массив со старым и сохраняет
    void merge(T *data, size_t start, size_t end)
    {
        if(_data == nullptr)
            _reserveMemory(_maxLength);

        data += start;

        T *tmp = new T[_maxLength];

        size_t i = 0; // итератор исходного массива
        size_t j = 0; // итератор нового массива

        while(i < _realLength && j < end - start && i + j < _maxLength) {
            if(_data[i] < data[j]) {
                tmp[i + j] = _data[i];
                ++i;
            }
            else
            {
                tmp[i + j] = data[j];
                ++j;
            }
        }
        if(i + j < _maxLength) {
            if(i == _realLength) {
                while(j < end - start && i + j < _maxLength) {
                    tmp[i + j] = data[j];
                    ++j;
                }
            }
            else if(j == end - start) {
                while(i < _realLength && i + j < _maxLength) {
                    tmp[i + j] = _data[i];
                    ++i;
                }
            }
        }

        delete[] _data;
        _data = tmp;
        _realLength = i + j;
    }

    // возвращает максимальный элемент в массиве на данный момент
    T getMax() {
        return _data[_realLength - 1];
    }

    // возвращает результат и удаляет указатель на него из объекта
    T *getResult() {
        T *result = _data;
        _data = nullptr;
        _realLength = 0;
        return result;
    }

private:
    T *_data; // массив
    size_t _realLength;
    size_t _maxLength; // максимальная длина

    void _reserveMemory(size_t num) {
        _maxLength = num;
        _data = new T[num];
    }
};



template<class T>
void mergeSort(T *data, int left, int right, T *buffer = nullptr)
{
    if(right - left < 2) return;

    bool first = (buffer == nullptr);
    if(first) {
        buffer = new T[right - left];
    }

    size_t size = (right - left);
    size_t half = size / 2;

    mergeSort(data, left, left + half, buffer);
    mergeSort(data, left + half, right, buffer);

    size_t i = 0;
    size_t j = 0;
    while(i < half && j < size - half) {
        if(data[left+i] < data[left+half + j]) {
            buffer[i + j] = data[left+i];
            ++i;
        }
        else {
            buffer[i + j] = data[left+half + j];
            ++j;
        }
    }

    if(i == half) {
        for (;j < size - half; j++)
            buffer[i + j] = data[left+half + j];
    }
    else {
        for (;i < half; i++)
            buffer[i + j] = data[left+i];
    }

    for(i = 0; i < size; i++)
        data[left + i] = buffer[i];

    if(first) delete[] buffer;
}

// возвращет первые k элементов отсортированного массива элементов, введенных из потока stream
template<class T>
T *getKSortedElements(size_t n, size_t k, std::istream &stream) {
    int left = n; // осталось ввести
    T *data = new T[k]; // вводим первые k элементов
    for(size_t i = 0; i < k; i++) {
        stream >> data[i];
    }
    left -= k;

    //сортируем k эл-ов и сливаем с итогом
    mergeSort(data, 0, k);
    LimitedMerger<T> merger(k);
    merger.merge(data, 0, k);

    while(left > 0) {
        int t = 0;
        for(; t < k && t < left; ++t)
            stream >> data[t];

        mergeSort(data, 0, t);
        merger.merge(data, 0, t);

        left -= t;
    }

    return merger.getResult();
}

int main() {
    size_t n = 0; // количество элементов всего
    size_t k = 0; // количество требуемых элементов
    std::cin >> n >> k;

    int *res = getKSortedElements<int>(n, k, std::cin);
    for(size_t i = 0; i < k; ++i) {
        std::cout << res[i] << " ";
    }

    return 0;
}
