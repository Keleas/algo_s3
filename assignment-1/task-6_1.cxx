//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_1. Жадина.

Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной
массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не
более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
которые может поднять одновременно, откусывает от каждого половину и
кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм,
он откусывает большую половину. Фрукт массы 1гр он съедает полностью.\
Определить за сколько подходов Вовочка съест все фрукты в корзине.

*Формат входных данных.* Вначале вводится n - количество фруктов и n
строк с массами фруктов. n ≤ 50000. Затем K - "грузоподъемность". K ≤ 1000.

*Формат выходных данных.* Неотрицательное число - количество подходов к
корзине.

  in             | out
  ---------------|-----
  3              | 4
  1 2 2          |
  2              |

  in             | out
  ---------------|-----
  3              | 5
  4 3 5          |
  6              |

  in             | out
  ---------------|-----
  7              | 3
  1 1 1 1 1 1 1  |
  3              |

****************************************************************************/


#include <iostream>
#include <cstring>
#include <vector>

// сравнение с помощью оператора <
template <class T>
bool isLess(const T &obj1, const T &obj2) {
    return obj1 < obj2;
}

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


template <class T>
int countEatingSteps(T *fruits, size_t left, size_t right, T max_weight)
{
    if(max_weight == 0) return 0;

    int steps = 0; // количество шагов
    Heap<T, isLess> fruits_heap(fruits + left, right); // формируем кучу
    std::vector<T> buffer; // временный буфер

    T cur_weight = 0; // вес текущего фрукта
    T total_weight = 0; // вес фруктов на текущем шаге

    while(true)
    {
        cur_weight = fruits_heap.get_size() > 0 ? fruits_heap.peek() : 0;

        if(fruits_heap.get_size() > 0 && total_weight + cur_weight <= max_weight) {
            total_weight += fruits_heap.pop();

            if(cur_weight != 1) {
                //оставил половину
                buffer.push_back(cur_weight / 2);
            }
        }
        else
        {
            // больше не лезет - кидаем в кучу то, что не доел
            while(buffer.size() > 0) {
                fruits_heap.push(buffer.back());
                buffer.pop_back();
            }
            total_weight = 0;
            ++steps;
        }

        // фрукты в корзине закончились
        if(fruits_heap.get_size() == 0 && buffer.size() == 0){
            ++steps;
            break;
        }
    }

    return (right != 0) ? steps : 0;
}

int main() {
    int n;
    std::cin >> n;

    int *fruits = new int[n];
    for(size_t i = 0; i < n; ++i)
        std::cin >> fruits[i];

    int k;
    std::cin >> k;

    std::cout << countEatingSteps(fruits, 0, n, k) << std::endl;

    delete[] fruits;

    return 0;
}
