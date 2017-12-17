/****************************************************************************
Реализуйте структуру данных типа "множество строк" на основе
динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые
и состоят из строчных латинских букв. Начальный размер таблицы должен
быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в
случае, когда коэффициент заполнения таблицы достигает 3/4.

Хеш-функцию строки реализуйте с помощью вычисления значения многочлена
методом Горнера.

Структура данных должна поддерживать операции добавления строки в
множество, удаления строки из множества и проверки принадлежности данной
строки множеству.
****************************************************************************/

/****************************************************************************

Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба\
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

*Формат входных данных*

Каждая строка входных данных задает одну операцию над множеством. Запись
операции состоит из типа операции и следующей за ним через пробел
строки, над которой проводится операция.

Тип операции -- один из трех символов:\
 + означает добавление данной строки в множество;\
 - означает удаление строки из множества;\
 ? означает проверку принадлежности данной строки множеству.

При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует
в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ,
что он присутствует в этом множестве.

*Формат выходных данных*

Программа должна вывести для каждой операции одну из двух строк OK или
FAIL, в зависимости от того, встречается ли данное слово в нашем
множестве.

+-----------+--------+
| stdin     | stdout |
+-----------+--------+
| \+ hello\ | OK     |
| + bye\    | OK     |
| ? bye     | OK     |
| \+ bye\   | FAIL   |
| - bye\    | OK     |
| ? bye\    | FAIL   |
| ? hello   | OK     |
+-----------+--------+

****************************************************************************/


#include <iostream>



class HashTable{
public:
    HashTable();

    ~HashTable();

    // Вставить значению по ключу. True - успех, false - иначе
    bool insert(std::string key);

    // Удалить значение по ключу. True - успех, false - иначе
    bool remove(std::string key);

    // Вернуть true, если есть key, и false в других случаях
    bool contains(std::string key) const;

    // Печать таблицы
    void print() const;

private:
    struct Node{
        Node(std::string key);

        std::string data;
        bool deleted;
    };

    // Рехэш в случае переполнения
    void rehash();
    // Хэш по ключу
    int hash(std::string key) const;
    size_t _bufferSize;
    // Занято в буффере
    size_t _size;
    Node **_nodes;
};

/***************************************************************************/

HashTable::Node::Node(std::string key) :
        data(key), deleted(false)
{}

/***************************************************************************/

HashTable::HashTable():
        _bufferSize(8), _size(0)
{
    _nodes = new Node*[_bufferSize];
    for(size_t i = 0; i < _bufferSize; i++)
        _nodes[i] = nullptr;
}

HashTable::~HashTable(){
    for (size_t i = 0; i < _bufferSize; ++i)
        if (_nodes[i] != nullptr)
            delete _nodes[i];
    delete[] _nodes;
}


bool HashTable::contains(std::string key) const{
    int hashed = hash(key);
    size_t i = 0;
    while( _nodes[hashed] != nullptr && i < _bufferSize ) {
        if( !_nodes[hashed]->deleted && _nodes[hashed]->data.compare(key) == 0 )
            return true;
        ++i;
        hashed = (hashed + i) % _bufferSize;
    }
    return false;
}


bool HashTable::insert(std::string key){
    if( contains(key) )
        return false;

    if(3*_bufferSize <= 4*(_size + 1))
        rehash();

    int hashed = hash(key);
    size_t i = 0;

    while( i < _bufferSize ) {
        if( _nodes[hashed] == nullptr ) {
            _nodes[hashed] = new Node(key);
            _size++;
            return true;
        }
        else if( _nodes[hashed]->deleted ) {
            _nodes[hashed]->data = key;
            _nodes[hashed]->deleted = false;
            _size++;
            return true;
        }
        ++i;
        hashed = (hashed + i) % _bufferSize;
    }
    return false;
}



bool HashTable::remove(std::string key){
    if( !contains(key) )
        return false;

    int hashed = hash(key);
    size_t i = 0;

    while( i < _bufferSize ) {
        if( !_nodes[hashed]->deleted && _nodes[hashed]->data.compare(key) == 0 ) {
            _nodes[hashed]->deleted = true;
            _size--;
            return true;
        }
        ++i;
        hashed = (hashed + i) % _bufferSize;
    }
    return false;
}



void HashTable::print() const{
    std::cout << "Alfa: " << (double) _size / _bufferSize
         << "; Size: " << _size
         << "; BufferSize: " << _bufferSize << '\n';
    for( size_t i = 0; i < _bufferSize; ++i )
        if( _nodes[i] == nullptr )
            std::cout << "NULL \n";
        else
            std::cout << "KEY: " << _nodes[i]->data
                 << "; DELETED: " << _nodes[i]->deleted
                 << "; ADDR: " << _nodes[i] << '\n';
}

/***************************************************************************/

void HashTable::rehash(){
    Node ** tmp = _nodes;
    _bufferSize *= 2;
    _size = 0;
    _nodes = new Node*[_bufferSize];

    for( size_t i = 0; i < _bufferSize; ++i )
        _nodes[i] = nullptr;

    for( size_t i = 0; i < _bufferSize / 2; ++i )
        if( tmp[i] != nullptr ) {
            if( !tmp[i]->deleted )
                insert(tmp[i]->data);
            delete tmp[i];
        }

    delete[] tmp;
}


int HashTable::hash(std::string key) const{
    int hashed = 0;
    for( size_t i = 0; i < key.length(); i++ ) {
        hashed = (hashed + 127 * key[i]) % _bufferSize;
    }
    return hashed;
}

/***************************************************************************/

enum OP{ ADD = '+', DELETE = '-', IS_THERE = '?' };

int main(){
    HashTable hashTable;

    while( !std::cin.eof() ) {
        char command;
        std::string str;

        std::cin >> command;
        std::cin >> str;

        if( str.empty() ) break;

        switch( command ){
            case ADD:
                if( hashTable.insert(str) )
                    std::cout << "OK\n";
                else
                    std::cout << "FAIL\n";
                break;
            case DELETE:
                if( hashTable.remove(str) )
                    std::cout << "OK\n";
                else
                    std::cout << "FAIL\n";
                break;
            case IS_THERE:
                if( hashTable.contains(str) )
                    std::cout << "OK\n";
                else
                    std::cout << "FAIL\n";
                break;
            default:
                break;
        }
    }
    return 0;
}
