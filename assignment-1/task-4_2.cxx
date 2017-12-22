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
Задача 4_2.

Реализовать дек с динамическим зацикленным буфером.

  in    | out
  ------|-----
  3     | YES
  1 44  |
  3 50  |
  2 44  |

  in    | out
  ------|-----
  2     | YES
  2 -1  |
  1 10  |

  in    | out
  ------|-----
  2     | NO
  3 44  |
  4 66  |

****************************************************************************/

#include <iostream>

#define START_BUFFER_SIZE 32

class Deque {
public:
    Deque();
    virtual ~Deque();
    void push_back(int element);
    int pop_back();
    void push_front(int element);
    int pop_front();
    bool empty();
private:
    int* buffer;
    int buffer_size;
    int front_index;
    int back_index;
    void growBack();
    void growFront();
};

Deque::Deque() {
    buffer = new int[START_BUFFER_SIZE];
    buffer_size = START_BUFFER_SIZE;
    back_index = -1;
    front_index = -1;
}

Deque::~Deque() {
    delete[] buffer;
}

void Deque::growBack() {
    if( back_index != 0 ){
        return;
    }

    int to_add = buffer_size;
    int *new_buffer = new int[buffer_size + to_add];

    for( size_t i = 0; i < buffer_size; ++i ){
        new_buffer[i + to_add] = buffer[i];
    }

    delete[] buffer;

    buffer = new_buffer;
    buffer_size += to_add;
    back_index += to_add;
    front_index += to_add;
}

void Deque::growFront() {
    if( front_index != buffer_size - 1 ){
        return;
    }

    int to_add = buffer_size;
    int *new_buffer = new int[buffer_size + to_add];

    for( size_t i = 0; i < buffer_size; ++i ){
        new_buffer[i] = buffer[i];
    }

    delete[] buffer;

    buffer = new_buffer;
    buffer_size += to_add;
}

void Deque::push_back(int element) {
    if (back_index != -1) {
        if (back_index == 0) {
            growBack();
        }
    } else {
        back_index = buffer_size / 2;
    }

    buffer[--back_index] = element;

    if (front_index == -1) {
        front_index = back_index;
    }
}

int Deque::pop_back() {
    if (back_index == front_index && back_index == -1) {
        return -1;
    }

    int result = buffer[back_index];

    back_index++;

    if (back_index > front_index) {
        back_index = -1;
        front_index = -1;
    }

    return result;
}

bool Deque::empty() {
    return ( buffer_size == 0 ) ? true : false;
}

void Deque::push_front(int element) {
    if (front_index != -1) {
        if (front_index == buffer_size - 1) {
            growFront();
        }
    } else {
        front_index = buffer_size / 2 - 1;
    }

    buffer[++front_index] = element;

    if (back_index == -1) {
        back_index = front_index;
    }
}

int Deque::pop_front() {
    if (back_index == front_index && back_index == -1) {
        return -1;
    }

    int result = buffer[front_index];

    front_index--;

    if (front_index < back_index) {
        back_index = -1;
        front_index = -1;
    }

    return result;
}

enum OP{ push_front = 1, pop_front = 2, push_back = 3, pop_back = 4};

int main()
{
    Deque arr;
    int n, cmd, num;
    bool check = true;

    std::cin >> n;

    for( size_t i = 0; i < n; ++i ){
        std::cin >> cmd >> num;
        switch (cmd) {
        case OP::push_front:
          arr.push_front(num);
          break;
        case OP::pop_front:
          if (arr.empty()) {
            if (num != -1) {
              check = false;
            }
          }
          else {
            int n = arr.pop_front();
            if (num != n) {
              check = false;
            }
          }
          break;
        case OP::push_back:
          arr.push_back(num);
          break;
        case OP::pop_back:
          if (arr.empty()) {
            if (num != -1) {
              check = false;
            }
          }
          else {
            int n = arr.pop_back();
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


    return 0;
}


