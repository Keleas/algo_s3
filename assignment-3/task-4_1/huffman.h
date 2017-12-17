#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <fstream>
#include <map>
#include <iostream>
#include <list>
#include <string>

/***************************************************************************/

typedef char byte;
typedef bool bit;

/***************************************************************************/

using std::map;
using std::list;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;

/***************************************************************************/

class IInputStream {
public:
    IInputStream(ifstream & fin):
            fin_(fin)
    {}
    // Возвращает false, если поток закончился
    bool Read(byte& value){
        if(fin_.eof())
            return false;
        fin_.get(value);
        return true;
    }

private:
    ifstream & fin_;
};

class IOutputStream {
public:
    IOutputStream(ofstream & fout):
            fout_(fout)
    {}
    void Write(byte value){
        fout_ << value;
    }

private:
    ofstream & fout_;
};


/***************************************************************************/

class bitostream{
public:
    bitostream(IOutputStream & stream);

    // Запись битов. Вернуть true, если успешно
    bool write(bit value);

private:
    // Поток
    IOutputStream &  stream_;

    // Количество байт
    byte currentByte_;

    // Количество бит в текущем байте
    char bitsWritten_;

};



class bitistream{
public:
    bitistream(IInputStream & stream);

    // Чтение бит. Вернет false в случае конца чтения
    bool read(bit & value);

private:
    // Поток
    IInputStream &  stream_;

    // Количество байт
    byte    currentByte_;

    // Количество бит в текущем байте
    char    bitsRead_;

};

/******************************************************************************/

class Node{
public:
    Node();
    Node(byte value, long weight, Node * left, Node * right);

    byte value;
    long weight;
    Node* left;
    Node* right;
};

bool nodeComparator(Node * & L, Node * R);

// Постороить дерево Хаффмана
Node* buildTree(map <byte, long> freq);

// Таблица кодов
void getCodes(Node * node, long code, map <byte, long> & codes);

// Вывод дерева Хаффмана (для отладки)
void printTree(Node * node, int depth, const map <byte, long> & codes);

// Удалить дерево
void deleteTree(Node * node);

// Длина каждого кода символа
void countCodeLengths(const map <byte, long> & codes, map <byte, char> & codeLengths);

// Удаление лишних узлов в дереве
void fixTree(Node * node);

// Encode файла
void Encode(IInputStream & original, IOutputStream & compressed);

// Decode файла
void Decode(IInputStream & compressed, IOutputStream & decoded);


#endif // HUFFMAN_H
