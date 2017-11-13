/****************************************************************************
Написать структуру данных, обрабатывающую команды push\* и pop\*.

*Формат входных данных.*
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back

Для очереди используются команды 2 и 3. Для дека используются все четыре команды.

Если дана команда pop\*, то число b - ожидаемое значение.Если команда
pop вызвана для пустой структуры данных, то ожидается “-1”.

*Формат выходных данных.*
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе,
если хотя бы одно ожидание не оправдалось, то напечатать NO.
****************************************************************************/

/****************************************************************************
Задача 4_3.

Реализовать очередь с помощью двух стеков. Использовать стек,
реализованный с помощью динамического буфера.

  in    | out
  ------|-----
  3     | YES
  3 44  |
  3 50  |
  2 44  |

  in    | out
  ------|-----
  2     | YES
  2 -1  |
  3 10  |

  in    | out
  ------|-----
  2     | NO
  3 44  |
  2 66  |

****************************************************************************/


#include <iostream>
#include <vector>

template<typename T>

class Stack
{
public:
    Stack(): buffer{nullptr}, s_capacity{0}, head{0}
    {}

    ~Stack(){
        if( buffer)
            delete[] buffer;
    }

    using value_type = T;

    size_t capacity() const{
        return s_capacity;
    }

    bool empty() const{
        return ( head == 0) ? true : false;
    }

    void push( T x)
    {
        if( capacity() == 0)
            init_buffer();

        if( head+1 == capacity())
        {
            //создадим новый стек и перезапишем все в него
            T* new_buf = new T[mem_size*capacity()];
            for( size_t i = 0; i < capacity(); ++i)
                new_buf[i] = buffer[i];
            delete[] buffer;
            buffer = new_buf;
            s_capacity *= mem_size;
        }
        buffer[++head] = x;
    }

    T pop()
    {
        T temp = buffer[head--];
        return temp;
    }

private:
    T *buffer;
    size_t s_capacity;
    size_t head;
    static constexpr size_t mem_size = 2;

    void init_buffer()
    {
        s_capacity = mem_size;
        buffer = new T[s_capacity];
    }
};

template<typename T>

class Queue
{
public:
    bool empty() const{
        return (rightStack.empty() && leftStack.empty()) ? true : false;
    }

    void push(T x)
    {
        rightStack.push(x);
    }

    T pop()
    {
        if( !leftStack.empty())
            return leftStack.pop();
        else{
            while( !rightStack.empty())
                leftStack.push(rightStack.pop());
            return leftStack.pop();
        }
    }

    using value_type = T;

private:
    Stack<T> rightStack;
    Stack<T> leftStack;
};


int main()
{
    Queue<int> arr;
    int n, cmd, num;
    bool check = true;

    std::cin >> n;
    for( int i = 0; i < n; ++i)
    {
        std::cin >> cmd >> num;

        switch (cmd) {
        case 2:
            if (arr.empty()){
                if( num != -1)
                    check = false;
            }
            else {
                int head = arr.pop();
                if( num != head)
                    check = false;
            }
            break;
        case 3:
            arr.push(num);
            break;
        default:
            check = false;
            break;
        }
    }
    if( check)
    std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;

    return 0;

}

