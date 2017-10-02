//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************

Задача 5_3. Прямоугольники.

Дана последовательность *N* прямоугольников различной ширины и высоты
(w_i,h_i). Прямоугольники расположены, начиная с точки (0, 0), на оси
ОХ вплотную друг за другом (вправо). Требуется найти *M* - площадь
максимального прямоугольника (параллельного осям координат), который
можно вырезать из этой фигуры. Время работы - O(n).

```
^ y                              ^ y
|                                |
|        +--+                    |        +--+
|        |  |    +--+            |        |  |    +--+
|        |  |    |  |            |        |  |    |  |
+--------+  |    |  |            *************    |  |
|        |  |    |  |            *************    |  |
|        |  +----+  |            *************----+  |
|        |  |    |  |    x       *************    |  |      x
+--------+--+----+--+---->       *************----+--+------>
```

*Формат входных данных.* В первой строке задано число *N* (1 ≤ *N* ≤
10000). Далее идет *N* строк. В каждой строке содержится два числа width
и height: ширина и высота i-го прямоугольника. (0 < width ≤ 10000, 0 ≤ height ≤ 10000)

*Формат выходных данных.* Вывести число *M*. (0 ≤ M ≤ 10^9).

  in      | out
  --------|------
  4       | 1200
  30 30   |
  10 40   |
  20 10   |
  10 40   |

  in      | out
  --------|------
  1       | 3000
  1 3000  |

  in      | out
  --------|------
  3       | 8
  1 1     |
  1 3     |
  3 2     |

****************************************************************************/

#include <iostream>

class Rectangle{
public:
    Rectangle(int w = 0, int h = 0) : width(w), height(h) {
    }

    int get_width() {
        return width;
    }

    int get_height() {
        return height;
    }

    void set_width(int w) {
        width = w;
    }

    void grow_width(int add_width) {
        width += add_width;
    }

    void set_height(int h) {
        height = h;
    }

    int get_area() {
        return width * height;
    }

protected:
    int width;
    int height;
};


template <class T>
class Stack{
public:
    Stack() : buffer(nullptr), s_capacity(0), head(0) {
    }

    ~Stack() {
        if( buffer)
        delete[] buffer;
    }

    // увеличение стека
    void growSize() {
        int newMemorySize = s_capacity > 0 ? s_capacity * 2 : 5;
        T *new_buff = new T[newMemorySize];

        if(head > 0) {
            for(size_t i = 0; i < head; ++i)
                new_buff[i] = buffer[i];
        }
        buffer = new_buff;
        s_capacity = newMemorySize;
    }

    T &pop(bool check = true) {
        if(check) {
            return buffer[(head--) - 1];
        }
        return buffer[head - 1];
    }

    // получение элемента с вершины (без удаления)
    T &see() {
        return pop(false);
    }

    void push(T x) {
        if(s_capacity == head) {
            growSize();
        }
        buffer[head++] = x;
    }

    bool empty() {
        return (head == 0) ? true : false;
    }

private:
    T *buffer;
    size_t s_capacity; //количество мест в сетеке
    size_t head; //количество элементов в стеке
};


int get_max_square(Rectangle *arr, size_t n)
    {
    Stack<Rectangle> stack;
    stack.push(arr[0]);
    int max = arr[0].get_area();

    for(size_t i = 1; i < n; ++i)
    {
        Rectangle *lastRect = &stack.see();    //последний прямоугольник в стеке
        Rectangle *curRect = &arr[i]; //текущий прямоугольник

        if( curRect->get_height() >= lastRect->get_height())
            // текущий прямоугольник выше, добавляем его в стек
            stack.push(*curRect);
        else
        {
            // текущий прямоугольник ниже предыдущих
            int newHeight = lastRect->get_height();

            while(newHeight > curRect->get_height()) { // пока не встретим прямоугольник ниже или такой же по высоте
                lastRect = &stack.pop();

                if(lastRect->get_area() > max)
                    max = lastRect->get_area();

                if(stack.empty()) {
                    // больше прямоугольников нет
                    // проверяем прямоугольник, сложенный с последним по высоте как текущий
                    Rectangle new_rect(lastRect->get_width() + curRect->get_width(), newHeight = curRect->get_height());
                    stack.push(new_rect);
                }
                else
                {
                    // складываем с предыдущим прямоугольником
                    stack.see().grow_width(lastRect->get_width());
                    int nextHeight = stack.see().get_height();

                    if(nextHeight > curRect->get_height())
                        newHeight = nextHeight;
                    else if(nextHeight == curRect->get_height()) {
                        stack.see().grow_width(curRect->get_width());
                        newHeight = curRect->get_height();
                    }
                    else{
                        Rectangle new_rect(lastRect->get_width() + curRect->get_width(), newHeight = curRect->get_height());
                        stack.push(new_rect);
                    }
                }
            }
        }
    }
    return max;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    n++; //в конце будет Rect(0,0)
    Rectangle *arr = new Rectangle[n];

    for(size_t i = 0; i < n - 1; ++i) {
        int w, h;
        std::cin >> w >> h;
        arr[i].set_width(w);
        arr[i].set_height(h);
    }
    arr[n-1].set_width(0);
    arr[n-1].set_height(0);

    std::cout << get_max_square(arr, n) << std::endl;

    delete[] arr;

    return 0;
}
