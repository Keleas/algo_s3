/****************************************************************************
Задача 4_1.

Напишите две функции для создания архива из одного файла и извлечения файла
из архива.

    // Метод архивирует данные из потока original
    void Encode(IInputStream& original, IOutputStream& compressed);

    // Метод восстанавливает оригинальные данные
    void Decode(IInputStream& compressed, IOutputStream& original);

где:

    typedef char byte;

    interface IInputStream {
        // Возвращает false, если поток закончился
        virtual bool Read(byte& value) = 0;
    };

    interface IOutputStream {
        virtual void Write(byte value) = 0;
    };

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый
8-битный символ.

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также
включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла
в процентах от исходного.

Лучшие 3 решения из каждой группы оцениваются в 15, 10 и 5 баллов соответственно.

Пример минимального решения:

    #include "Huffman.h"

    static void copyStream(IInputStream&input, IOutputStream& output) {
        byte value;
        while(input.Read(value)) {
            output.Write(value);
        }
    }

    void Encode(IInputStream& original, IOutputStream& compressed) {
      copyStream(original, compressed);
    }

    void Decode(IInputStream& compressed, IOutputStream& original) {
        copyStream(compressed, original);
    }

****************************************************************************/

/****************************************************************************
 Идея:

 Находим статистику символов, храним в ассоциативном массиве. Создаем из
 каждого элемента контейнера map узел - Node и кидаем в приоритетную
 очредь. Очередь соритирует по возрастанию ключа. Затем вытаскиваем из
 очереди два первых - создаем новый лист с теми двумя в дочерних элементах.
 Работаем пока в очереди не осталось одного элемента - вершины дерева.
 Шифруем исходное сообщение - ищем каждый символ в дереве, формируем
 новую строку.

    Кодированная структура файла:
         1 байт, сохраняющий количество неиспользуемых битов в остальной части файла;
         1 байт, сохраняющий количество байтов на код;
         1 байт, сохраняющий размер алфавита.

         Таблица:
         Для каждого символа:
         1 байт, сохраняющий закодированный символ
         bytesPerCode байтов, сохраняющих код.

         Закодированные данные.


****************************************************************************/


#include "Huffman.h"

int main()
{
    ifstream _original("E:\\original.txt");
    ofstream _compressed1("E:\\encoded.txt");
    IInputStream original(_original);
    IOutputStream compressed1(_compressed1);
    Encode(original, compressed1);
    _compressed1.close();
    _original.close();

    ifstream _compressed2("E:\\encoded.txt");
    ofstream _decoded("E:\\decoded.txt");
    IInputStream compressed2(_compressed2);
    IOutputStream decoded(_decoded);
    Decode(compressed2, decoded);
    _compressed2.close();
    _decoded.close();

    _original.open("E:\\original.txt");
    _compressed2.open("E:\\decoded.txt");
    while(!_original.eof()){
        byte a, b;
        _original.get(a);
        _compressed2.get(b);
        if(a != b)
            std::cerr << "Doesn't match \n";
    }
    cout << "Ready \n";

    return 0;
}
