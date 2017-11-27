/****************************************************************************
Во всех вариантах данной задачи необходимо реализовать
и использовать **сортировку вставками**.
****************************************************************************/

/****************************************************************************
Задача 1_2. Ломаная 1.

Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся
незамкнутую ломаную, проходящую через все эти точки.

*Указание*: стройте ломаную в порядке возрастания x-координаты. Если имеются
две точки с одинаковой x-координатой, то расположите раньше ту точку, у которой
y-координата меньше.

in  | out
--- | ---
4   | 0 0
0 0 | 0 1
1 1 | 1 0
1 0 | 1 1
0 1 |

****************************************************************************/

/****************************************************************************

Идея:

Сортируем точки:
1 приоритет - наименьшая абсциса
2 приоритет - наименьшая ордината
Таким образом, мы будем строить ломаную из самой нижней, левой точки.
****************************************************************************/

#include <iostream>

template<class T>
struct Point
{
    T x, y;

    bool operator >(const Point &point) const{
        if(this->x > point.x) return true;
        if(this->x == point.x && this->y > point.y) return true;
        return false;
    }
};

void insertSort(Point<int>* arr, size_t size)
{
    for(size_t i = 1; i < size; ++i){
        size_t j = i - 1;
        while(j >= 0 && arr[j] > arr[j+1]){
            std::swap(arr[j], arr[j+1]);
            --j;
        }
    }
}


int main()
{
    int N, a, b;
    std::cin >> N;
    Point<int> *arr = new Point<int>[N];

    for(size_t i = 0; i < N; ++i){
        std::cin >> a >> b;
        arr[i].x = a;
        arr[i].y = b;
    }

    insertSort(arr, N);

    for(size_t i = 0; i < N; ++i)
        std::cout << arr[i].x << " " << arr[i].y << "\n";

    delete[] arr;
    return 0;
}