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
 Задача 4_1.

Реализовать очередь с динамическим зацикленным буфером.

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

template<typename T>
class Deque
{
public:
    Deque(): buffer{nullptr}, dsize{0}, dcapacity{0}, head{0}, end{0}
    {}

    ~Deque(){
        if( buffer)
            delete[] buffer;
    }

    using value_type = T;

    int front() const{
        return buffer[head];
    }

    int back() const{
        return buffer[end];
    }

    size_t capacity() const{
        return dcapacity;
    }

    size_t size() const{
        return dsize;
    }

    bool empty() const{
        return ( dsize == 0) ? true : false;
    }

    //в случае, переполнения памяти, мы заводим новую очередь
    //и перезаписываем все туда
    void reserve(const size_t size)
    {
        T* new_buf = new T[size];

        // копируем страую очередь в новый массив
        if ( head < end)
            std::copy( buffer + head, buffer + end, new_buf + head);
        else {
            std::copy( buffer + head, buffer + dcapacity, new_buf + head);
            std::copy( buffer, buffer + end, new_buf + dcapacity);
        }

        delete[] buffer;
        //налаживание связей
        if( head > end)
            end = head + ( dcapacity - head) + end;

        buffer = new_buf;
        dcapacity = size;

    }
    //толкаем новый
    void push_back(T x)
    {
        //в случа, если мы только начиаем созадавать очередь
        if( capacity() == 0)
            init_buffer();

            if( !empty())
            {
                //если нет места
                if( size() + 1 == capacity())
                    reserve(mem_size * dcapacity);
            }
            buffer[end++] = x;
            //для создания кольца
            end %= dcapacity;
            ++dsize;
    }
    //вытакскиваем
    void push_front(T x)
    {
        if( capacity() == 0)
            init_buffer();

        if( !empty())
        {
            if( size()+1 == capacity())
                reserve( mem_size * dcapacity);
            if( head == 0)
                head = dcapacity;
            buffer[--head] = x;
        }
        else{
            buffer[head] = x;
            ++end;
        }
        ++dsize;
    }

    void pop_front()
    {
        if( !empty()){
            head = ( head+1) % dcapacity;
            --dsize;
        }
    }

    void pop_back()
    {
        if( !empty()){
            if( end == 0)
                end = dcapacity;
            --end;
            --dsize;
        }
    }

    void print_deque() const
    {
        std::cout << "head: " << head <<  ", end: " << end << "/n";
        for( size_t i =0; i < dcapacity; ++i)
        {
            if( i >= end || i <= head)
                std::cout << "|err";
            else std::cout << "|" << buffer[i];
            if( i == head)
                std::cout << "|>";
            else if( i == end)
                std::cout << "<|";
            else std::cout << "|";
        }
        std::cout << std::endl;
    }

private:
    T *buffer;
    size_t dsize; //реальный размер очереди
    size_t dcapacity; //количество выделенных элементов под очередь
    int head; //голова
    int end; //конец
    //счетчик для увеличения очереди в случае переполнения
    //при переполении создаем очередь в 2 раза больше старой
    static constexpr size_t mem_size = 2;

    //инициализация размера очереди при добавлении самого первого элемента
    void init_buffer()
    {
        dcapacity = mem_size;
        buffer = new T[dcapacity];
    }

};

int main()
{
    Deque<int> arr;
    int n, cmd, num;
    bool check = true;

    std::cin >> n;
    for( size_t i =0; i < n; ++i)
    {
        std::cin >> cmd >> num;

        switch (cmd) {
        case 1:
          arr.push_front(num);
          break;
        case 2:
          if (arr.empty()) {
            if (num != -1) {
              check = false;
            }
          }
          else {
            int n = arr.front();
            arr.pop_front();
            if (num != n) {
              check = false;
            }
          }
          break;
        case 3:
          arr.push_back(num);
          break;
        case 4:
          if (arr.empty()) {
            if (num != -1) {
              check = false;
            }
          }
          else {
            int n = arr.back();
            arr.pop_back();
            if (num != n) {
              check = false;
            }
          }
        default:
          break;
        }
      }

      if (!check) {
        std::cout << "NO";
      }
      else {
        std::cout << "YES";
      }
      std::cout << std::endl;

     // Deque::print_deque();

      return 0;
    }
