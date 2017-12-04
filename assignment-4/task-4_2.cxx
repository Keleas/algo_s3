/****************************************************************************
Задача № 4. Динамика на дереве (6 баллов)

Дано невзвешенное дерево. Расстоянием между двумя вершинами будем
называть количество ребер в пути, соединяющем эти две вершины.

****************************************************************************/
/****************************************************************************

Сумма длин до остальных.

Для каждой вершины определите сумму расстояний до всех остальных вершин.
Время работы должно быть O(n).

*Формат входных данных:*

В первой строке записано количество вершин n ≤ 10000. Затем следует n --
1 строка, описывающая ребра дерева. Каждое ребро -- это два различных
целых числа -- индексы вершин в диапазоне\
\[0, n--1\]. Индекс корня -- 0. В каждом ребре родительской вершиной
является та, чей номер меньше.

*Формат выходных данных:*

Выход должен содержать n строк. В i-ой строке выводится сумма расстояний
от i-ой вершины до всех остальных.

+-----+-----+
| in  | out |
+-----+-----+
| 3   | 3   |
| 0 1 | 2   |
| 1 2 | 3   |
+-----+-----+

****************************************************************************/

#include <iostream>

int main()
{
    return 0;
}

