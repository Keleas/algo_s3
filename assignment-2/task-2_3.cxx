/****************************************************************************
Во всех задачах данного раздела необходимо реализовать и использовать
**локальную пирамидальную сортировку** (без использования дополнительной
памяти). Общее время работы алгоритма O(n log n).
****************************************************************************/

/****************************************************************************
Задача 2_3. Закраска прямой 1.

На числовой прямой окрасили N отрезков. Известны координаты левого и правого
концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.

in  | out
--- | ---
3   | 5
1 4 |
7 8 |
2 5 |

****************************************************************************/

/****************************************************************************
Идея:

Упорядочить координаты отрезков на прямой по возрастанию. При этом создаем
class Point, который содержит в себе координату и информацию о том, является ли
данная точка стартом отрезка. Мы будем идти по отрезку и фиксировать сколько на
данном моменте слоев. Если хотя бы один слой, тогда считаем длину этого слоя,
идем дальше. Таким образом, мы считаем длину каждого слоя отдельно, но за
за линейное время.

  ///////////                           ////
--|---|--------|---|----------------|---|--------->
        ///////////
  1    2          4   5                    7   8

  На данном примере мы высчитываем длину 1-2 слоя, затем 2-4, 4-5 и т.д.

****************************************************************************/

#include <iostream>

class Point {
public:
    int x; // координата
    bool start; // фиксируем начало ли это отрезка
    Point(int _x = 0, bool _start = false) : x(_x), start(_start) {}
};

bool isPointLess(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

template <class T>
class Heap
{
public:
    //формирем кучу из массива
    Heap(T *buffer, size_t size, bool (*lessFunc)(const T &, const T &))
        : _buffer(buffer), _size(size), _bufferSize(size), _lessFunc(lessFunc)
    {
        for(int i = size/2 - 1; i >= 0; --i)
            siftDown(i);
    }

    T* getBuffer() {
        return _buffer;
    }

    size_t getSize() {
        return _size;
    }

    //берем эл-т не удаляя его
    const T &peek() {
        return _buffer[0];
    }

    //берем эл-т удаляя его
    T pop() {
        T elem = _buffer[0];
        _size--;

        if(_size > 0) {
            std::swap(_buffer[0], _buffer[_size]);
            siftDown(0);
        }

        return elem;
    }

    //добавить эл-т
    void insert(const T &elem) {
        if(_bufferSize == _size)
            growBufferSize(_bufferSize * 2);

        _buffer[_size] = elem;
        siftUp(_size);
        _size++;
    }

private:
    T* _buffer; //буффер
    size_t _size; //кол-во эл-ов
    size_t _bufferSize; //возможное кол-во эл-ов
    bool (*_lessFunc)(const T &, const T &); //функция сравнения на меньше

    //выделение памяти
    void growBufferSize(size_t n = 0) {
        if(n < _bufferSize) return;

        size_t newBufferSize = (n > 0) ? n : 5;
        T *newBuffer = new T[newBufferSize];

        for(size_t i = 0; i < _size; ++i)
            newBuffer[i] = _buffer[i];

        delete[] _buffer;
        _buffer = newBuffer;
        _bufferSize = newBufferSize;
    }

    void siftUp(size_t index) {
        size_t parent = ((int) index - 1) / 2;
        while(_lessFunc(_buffer[parent], _buffer[index]))
        {
            std::swap(_buffer[index], _buffer[parent]);
            index = parent;
        }
    }

    void siftDown(size_t index) {
        while(2 * index + 1 < _size) {
            size_t left = index * 2 + 1; //индекс левого
            size_t right = left + 1; //индекс правого
            size_t k = left; // индекс наибольшего из потомков

            if (right < _size && _lessFunc(_buffer[left], _buffer[right]))
                ++k;

            if (_lessFunc(_buffer[index], _buffer[k]))
            {
                std::swap(_buffer[k], _buffer[index]);
                index = k;
            } else break;
        }
    }

    void print() {
        for(size_t i = 0; i < _size; ++i)
            std::cout << _buffer[i] << std::endl;
    }

};


// пирамидальная сортировка
template<class T>
void heapSort(T *data, size_t left, size_t right, bool (*isLess)(const T &, const T &)) {
    Heap<T> heap(data + left, right - left, isLess);

    for(size_t i = left; i < right; ++i)
        heap.pop();
}


int Shaded_Section(Point *points, size_t n) {
    int result = 0;

    heapSort<Point>(points, 0, n, &isPointLess);

    int lastStart = points[0].x;
    int curLayers = 1;

    for(size_t i = 1; i < n; ++i) {
        if(curLayers > 0) //проверяем на наличие хотя бы одного слоя
                result += (points[i].x - lastStart);

        curLayers += (points[i].start) ? 1 : -1; //обновляем кол-во слоев
        lastStart = points[i].x;
    }

    return result;
}


int main()
{
    size_t n = 0;
    std::cin >> n;

    n *= 2;
    Point *points = new Point[n];

    for(size_t i = 0; i < n; ++i) {
        std::cin >> points[i].x;
        points[i].start = (i % 2 == 0);
    }

    heapSort<Point>(points, 0, n, &isPointLess);

    /*for(size_t i = 0; i < n; ++i)
        std::cout << points[i].x << " ";
    std::cout << "\n";*/

    std::cout << Shaded_Section(points, n);

    delete[] points;
    return 0;
}

