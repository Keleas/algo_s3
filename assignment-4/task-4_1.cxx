/****************************************************************************
Задача № 4. Динамика на дереве (6 баллов)

Дано невзвешенное дерево. Расстоянием между двумя вершинами будем
называть количество ребер в пути, соединяющем эти две вершины.

****************************************************************************/

/****************************************************************************

Самая удаленная вершина.

Для каждой вершины определите расстояние до самой удаленной от нее
вершины. Время работы должно быть O(n).

*Формат входных данных:*

В первой строке записано количество вершин n ≤ 10000. Затем следует n --
1 строка, описывающая ребра дерева. Каждое ребро -- это два различных
целых числа -- индексы вершин в диапазоне\
\[0, n--1\]. Индекс корня -- 0. В каждом ребре родительской вершиной
является та, чей номер меньше.

*Формат выходных данных:*

Выход должен содержать n строк. В i-ой строке выводится расстояние от
i-ой вершины до самой удаленной от нее.

+-----+-----+
| in  | out |
+-----+-----+
| 3   | 2   |
| 0 1 | 1   |
| 1 2 | 2   |
+-----+-----+

****************************************************************************/

/****************************************************************************
Идея:



****************************************************************************/

#include <iostream>
#include <algorithm>

class Tree{
public:
    Tree(int n);
    void distance(std::vector <int>& out);
    void insert(int x, int y);

private:
    struct Node{
        std::vector <Node*>  child;
        int index;
        int depth;
    };
    int  max_child_depth(Node* node, int except);
    void fix_depth(Node* node);
    void find_dist(Node* node, int maxDepth, std::vector <int>& out);
    std::vector <Node> nodes;
};


Tree::Tree(int n):
    nodes(n)
{
    for( int i = 0; i < n; ++i )
        nodes[i].index = i;
}

void Tree::insert(int x, int y) {
    //это так у каждой вершины есть список его детей вершин
    //при этом мы кидаем в список объекты графа, т.е. у детей есть данные, за кем они в графе
    nodes[std::min(x, y)].child.push_back(&nodes[std::max(x, y)]);
}

/*
С одним детем или без детей глубина будет равна 0. Это для того, чтобы можно было
тащить за собой дистанцию до самого дальнего элемента от данного в функции
поиска дистанции.
*/
int Tree::max_child_depth(Node * node, int expect) // expect = -1 - найдет максимальную глубину для узла
{
    int maxDepth = 0;
    for( size_t i = 0; i < node->child.size(); ++i )
        if( node->child[i]->index != expect
                && node->child[i]->depth > maxDepth )
        {
            maxDepth = node->child[i]->depth;
        }
    return maxDepth;
}


//определяем глубину для каждой вершины
void Tree::fix_depth(Node * node) {
    if (node == nullptr )
        return;

    for( size_t i = 0; i < node->child.size(); ++i )
        fix_depth(node->child[i]);

    node->depth = max_child_depth(node, - 1) + 1;
}

void Tree::find_dist(Node * node, int maxDepth, std::vector<int> & out){
    if( node == nullptr )
        return;

    for( size_t i = 0; i < node->child.size(); ++i )
        find_dist(node->child[i], std::max(max_child_depth(node, node->child[i]->index), maxDepth) + 1, out);

/*
Рекурсивно спускаемся до самых крайних вершин в дереве, передавая им постоянно
наращивающуюся дистанцию.
max(maxChildrenDepth(node, node->children[i]->index), maxDepth - с помощью этого
формируем самый длинный путь до возмжного элемента
*/
    out[node->index] = std::max(max_child_depth(node, -1), maxDepth);
}


void Tree::distance(std::vector<int>& out){
    fix_depth(&nodes[0]);
    find_dist(&nodes[0], 0, out);
}

int main()
{
    int n;
    std::cin >> n;
    Tree tree(n);
    for(int i = 0; i < n - 1; ++i){
        int x, y;
        std::cin >> x >> y;
        tree.insert(x, y);
    }

    std::vector <int> out(n);
    tree.distance(out);
    for(int i = 0; i < n; ++i)
        std::cout << "i = " << i << " -> " << out[i] << '\n';

    return 0;
}

