//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************
 Задача 5_1. Скобочная последовательность.

Дан фрагмент последовательности скобок, состоящей из символов (){}[].

Требуется определить, возможно ли продолжить фрагмент в обе стороны,
получив корректную последовательность.

Длина исходной последовательности ≤ 800000.

*Формат входных данных.* Строка, содержащая символы (){}[] и,
возможно, перевод строки.

*Формат выходных данных.* Если возможно - вывести минимальную корректную
последовательность, иначе - напечатать "**IMPOSSIBLE**".

  in          | out
  ------------|--------------------------
  {}[[[[{}[]  | {}[[[[{}[]]]]]
  {][[[[{}[]  | IMPOSSIBLE
  ]()}[](({}  | {[]()}[](({}))

****************************************************************************/

/****************************************************************************
 Идея:

 Сформировать к исходным данным надстройку слева и справа, чтобы
 получилось правльное скобочное выражение при их слиянии.
 Посимвольно считываем поток ввода. Помещаем в стек только скобки, которые не образуют
 правильные скобоыне выражения, т.е. мы будем знать к каким скобкам нужно составлять
 надстройку слева и справа. В ходе посимвольного считывания скобок, проверяем на возможность
 достроить исходное выражение до правильного.

****************************************************************************/


#include <iostream>
#include <string>
#include <sstream>


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


int main()
{
    try{
        //стэк
        Stack<char> arr;
        //строка для построения скобочного выражения в начале
        std::string s_start{""};
        //строка для построения исходного скобочного выражения
        std::string s_mid{""};
        //строка для построения скобочного выражения в конце
        std::string s_end{""};

        std::getline( std::cin, s_mid);
        std::istringstream is {s_mid};
        char c;

        while ( is >> c)
        {
            char head;

            switch (c) {
            case '(':
                arr.push(c);
                break;
            case '[':
                arr.push(c);
                break;
            case '{':
                arr.push(c);
                break;
            case ')':
                if( !arr.empty()){
                    head = arr.pop();
                    //проверяем на неправильный ввод
                    if ( head == '{' || head == '[')
                        throw false;
                    //если не было до нее закр. скобки такого же типа
                    else if( head == ')' || head == '}' || head == ']'){
                        arr.push(head);
                        arr.push(c);
                    }
                }
                else arr.push(c);
                break;
            case ']':
                if( !arr.empty()){
                    head = arr.pop();
                    if ( head == '{' || head == '(')
                        throw false;
                    else if( head == ')' || head == '}' || head == ']'){
                        arr.push(head);
                        arr.push(c);
                    }
                }
                else arr.push(c);
                break;
            case '}':
                if( !arr.empty()){
                    head = arr.pop();
                    if ( head == '[' || head == '(')
                        throw false;
                    else if( head == ')' || head == '}' || head == ']'){
                        arr.push(head);
                        arr.push(c);
                    }
                }
                else arr.push(c);
                break;
            default:
                throw false;
                break;
            }
        }

        //формируем строки из скобок,
        //которые нужно дописать в начале и в конце
        //строки s_mid
        while ( !arr.empty()){
            char temp=arr.pop();
            switch (temp){
            case '(' :
                s_end += ')';
                break;
            case '{' :
                s_end += '}';
                break;
            case '[' :
                s_end += ']';
                break;
            case ')' :
                s_start += '(';
                break;
            case '}' :
                s_start +='{';
                break;
            case ']' :
                s_start += '[';
                break;
            default:
                break;
            }
        }

        //слиение строк
        s_mid = s_start + s_mid + s_end;

        for ( size_t i = 0; i< s_mid.size(); ++i )
            std::cout  << s_mid[i];

        return 0;
    }
    catch(bool)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
        return 0;
    }
    catch(...)
    {
        std::cerr << "Ooops, uknown error" << std::endl;
        return 1;
    }
}
