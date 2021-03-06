/****************************************************************************
Дано число N &lt; 10^6 и последовательность пар целых чисел из [-2^31..2^31]
длиной N.

Построить декартово дерево из N узлов, характеризующихся парами чисел
{Xi, Yi}.

Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом
дереве.

Добавление узла в декартово дерево выполняйте второй версией алгоритма,
рассказанного на лекции:

- При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
первом поддереве все ключи меньше x, а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y).
Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
****************************************************************************/

/****************************************************************************

Задача 2_1 Вычислить разницу глубин наивного дерева поиска и декартового
дерева. Разница может быть отрицательна.

  in    | out
  ----- | ---
  10    |
  5 11  |
  18 8  |
  25 7  |
  50 12 |
  30 30 |
  15 15 |
  20 10 |
  22 5  |
  40 20 |
  45 9  | 2

  in    | out
  ----- | ---
  10    |
  38 19 |
  37 5  |
  47 15 |
  35 0  |
  12 3  |
  0 42  |
  31 37 |
  21 45 |
  30 26 |
  41 6  | 2

****************************************************************************/

#include <iostream>

int main()
{
    return 0;
}

