//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_4. Скользящий максимум.

Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же
задан размер некотрого окна (последовательно расположенных элементов
массива) в этом массиве k, k <= n. Требуется для каждого положения окна
(от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n * log n), память O(n).

*Формат входных данных.* Вначале вводится n - количество элементов
массива. Затем вводится n строк со значением каждого элемента. Затем
вводится k - размер окна.

*Формат выходных данных.* Разделенные пробелом значения максимумов для
каждого положения окна.

  in                  | out
  --------------------|----------------
  3                   | 2 3
  1 2 3               |
  2                   |

  in                  | out
  --------------------|----------------
  9                   | 8 8 8 10 10 10
  0 7 3 8 4 5 10 4 6  |
  4                   |

****************************************************************************/

#include <iostream>


template <class T, bool (*less_func)(const T &, const T &)>
class Heap {
public:
    Heap(size_t dataSize = 0): _buffer(nullptr), _size(0), _capacity(0) {
        add_size(dataSize);
    }

    // конструктор [неотсортированный массив, количество элементов]
    Heap(const T *data, size_t size) : _buffer(nullptr), _size(0), _capacity(0) {
        add_size(size);
        memcpy(&_buffer[0], &data[0], sizeof(T) * size);
        _size = size;

        for (int i = size/2 - 1; i >= 0; --i)
            sift_down(i);
    }

    ~Heap() {
        delete[] _buffer;
    }

    size_t get_size() {
        return _size;
    }

    // выделение памяти
    void add_size(size_t n = 0) {
        if(n < _capacity) return;

        size_t newMemorySize = (n > 0) ? n : 5;

        T *new_buff = new T[newMemorySize];

        for(size_t i = 0; i < _size; i++) {
            new_buff[i] = _buffer[i];
        }

        delete[] _buffer;
        _buffer = new_buff;
        _capacity = newMemorySize;
    }

    // возвращает значение с вершины кучи, НЕ УДАЛЯЯ его из кучи
    T peek() {
        return _buffer[0];
    }

    // возвращает значение с вершины кучи, УДАЛЯЯ его из кучи
    T pop() {
        T elem = _buffer[0];
        --_size;
        if(_size > 0) {
            std::swap(_buffer[0], _buffer[_size]);
            sift_down(0);
        }
        return elem;
    }

    // добавляем элемент в кучу
    void push(T elem){
        if(_capacity == _size) {
            add_size(_capacity * 2);
        }

        _buffer[_size] = elem;
        sift_up(_size);
        ++_size;
    }

    // проталкиваем элемент вверх
    void sift_up(size_t index) {
        size_t parent = ((int) index - 1) / 2;
        while(less_func(_buffer[parent], _buffer[index])) {
            // если child > своего parent, то меняем их местами
            std::swap(_buffer[index], _buffer[parent]);
            index = parent;
        }
    }

    // проталкиваем элемент вниз
    void sift_down(size_t index) {
        while(2 * index + 1 < _size) {
            size_t left = index * 2 + 1; // индекс левого потомка
            size_t right = left + 1; // индекс правого потомка
            size_t k = left; // индекс наибольшего из потомков
            if (right < _size && less_func(_buffer[left], _buffer[right])) {
                ++k;
            }
            if (less_func(_buffer[index], _buffer[k])) { // parent меньше child
                // меняем местами parent и child
                std::swap(_buffer[k], _buffer[index]);
                index = k;
            } else {
                break;
            }
        }
    }

    // вывод содержимого кучи
    void show() {
        for(size_t i = 0; i < _size; i++) {
            std::cout << _buffer[i] << std::endl;
        }
    }

private:
    T* _buffer; // выделенная память
    size_t _size; // количество элементов в куче
    size_t _capacity; // количество элементов, на которые выделена память
};


int main()
{
    return 0;
}

