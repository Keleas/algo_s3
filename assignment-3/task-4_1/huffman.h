#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <assert.h>
#include <vector>
#include <fstream>

class Node
{
public:
    int key;
    char data;
    Node(char _data, int _key)
        : key {_key}, data{_data}
    {}

    Node(Node* _left, Node* _right, int _key)
        : lt{_left}, rt{_right}, key{_key}, data{NULL}
    {}

    Node* insert( Node *n ); //вставка
    Node* transplant( Node* q ); //поменять местами
    Node* Delete(); //удалить
    Node* find( int k ); //найти элемент
    Node* minimum(); //найти минимальный
    Node* maximum(); //найти максимальный
    Node* root(); //корень дерева
    Node* next(); //следующий от текущего по ключу
    Node* prev(); //предыдущий по ключу

    Node* right() {return rt;}
    Node* left() {return lt;}
    Node* parent() {return p;}

    bool is_leaf() {
        return !lt && !rt;
    }


    void BuildTable(Node* head); // таблица кодов элементов
private:
    Node *p {nullptr}; //корень
    Node *lt {nullptr}; //левый
    Node *rt {nullptr};  //правый
    friend void BuildTable(Node* head);
};

/*---------------------------------------------
                   additional functions
---------------------------------------------*/

void wfs( Node *t ); //обход по слоям
void prefix_traverse( Node *t, void f( Node* ) ); //обход в глубину
void print_key( Node *t );

//кодирование и сжатие с сохранением таблицы и дерева
void encode(const std::string& original);
//разархивация файла по таблице и дереву
void decode(const std::string& compression);

#endif // HUFFMAN_H
