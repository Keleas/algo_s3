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

Задача 2_2 Вычислить количество узлов в самом широком слое декартового дерева
и количество узлов в самом широком слое наивного дерева поиска. Вывести их
разницу. Разница может быть отрицательна.

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
  45 9  | 1

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
  41 6  | 1

****************************************************************************/

#include <iostream>
#include <queue>

template <class T>
class TreeNode {
public:
    T key;
    int priority;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(const T &_data, int _priority = 0): key(_data), priority(_priority), left(NULL), right(NULL) {
    }
};

template <class T>
class NaiveTree {
public:
    NaiveTree() : root(NULL) {
    }

    ~NaiveTree() {
        std::queue<TreeNode<T> *> tmp;
        if( root != NULL ) {
            tmp.push(root);
        }

        while( !tmp.empty() ) {
            TreeNode<T> *cur = tmp.front();
            if( cur->left != NULL )
                tmp.push(cur->left);

            if( cur->right != NULL )
                tmp.push(cur->right);
            delete cur;
            tmp.pop();
        }
    }

    void setRoot(TreeNode<T> *_root) {
        root = _root;
    }

    void insert(const T &data) {
        TreeNode<T> *node = new TreeNode<T>(data);
        TreeNode<T> *curNode = root;

        if( curNode == NULL ) {
            setRoot(node);
            return;
        }

        while( true ) {
            if( data < curNode->key ) {
                if( curNode->left != NULL )
                    curNode = curNode->left;
                else {
                    curNode->left = node;
                    return;
                }
            }
            else {
                if( curNode->right != NULL )
                    curNode = curNode->right;
                else {
                    curNode->right = node;
                    return;
                }
            }
        }
    }

    int get_mWidth() {
        int maxWidth = 0,
            curWidth = 0;

        std::queue<TreeNode<T> *> layerNodes;
        TreeNode<T> *cur = NULL;
        layerNodes.push(root);

        while( !layerNodes.empty() ) {
            if(( curWidth = layerNodes.size()) > maxWidth )
                maxWidth = curWidth;

            for( size_t i = 0; i < curWidth; ++i ) {
                cur = layerNodes.front();
                if( cur->left != NULL )
                    layerNodes.push(cur->left);

                if(cur->right != NULL)
                    layerNodes.push(cur->right);
                layerNodes.pop();
            }
        }
        return maxWidth;
    }

private:
    TreeNode<T> *root;
};


template <class T>
class TreapTree {
public:
    TreapTree() : root(NULL)
    {}

    ~TreapTree() {
        std::queue<TreeNode<T> *> tmp;
        if( root != NULL )
            tmp.push(root);

        while( !tmp.empty() ) {
            TreeNode<T> *cur = tmp.front();
            if( cur->left != NULL )
                tmp.push(cur->left);

            if( cur->right != NULL )
                tmp.push(cur->right);

            delete cur;
            tmp.pop();
        }
    }

    void split(TreeNode<T> *curNode, const T &data, TreeNode<T> *&left, TreeNode<T> *&right) {
        if( curNode == NULL ) {
            left = NULL;
            right = NULL;
        }
        else if( curNode->key <= data ) {
            split(curNode->right, data, curNode->right, right);
            left = curNode;
        }
        else {
            split(curNode->left, data, left, curNode->left);
            right = curNode;
        }
    }

    void setRoot(TreeNode<T> *_root) {
        root = _root;
    }

    void insert(const T &data, int priority) {
        TreeNode<T> *node = new TreeNode<T>(data, priority);
        TreeNode<T>*curNode = root;
        TreeNode<T>*prevNode = root;

        if( curNode == NULL ) {
            setRoot(node);
            return;
        }

        // Спускаемся по дереву и останавливаемся на первом элементе,
        // в котором значение приоритета оказалось меньше заданого
        while( curNode != NULL && priority <= curNode->priority ) {
            prevNode = curNode;
            if( data <= curNode->key )
                curNode = curNode->left;
            else
                curNode = curNode->right;
        }

        // Разрезаем поддерево найденного элемента на T1 и Т2.
        // Полученные T1 и T2 записываем в качестве левого и правого
        split(curNode, data, node->left, node->right);

        // Ставим на место элемента, найденного в первом пункте.
        if( curNode == root )
            root = node;
        else if( data <= prevNode->key ) {
            prevNode->left = node;
        }
        else {
            prevNode->right = node;
        }
    }

    int get_mWidth() {
        int maxWidth = 0;
        int curWidth = 0;

        std::queue<TreeNode<T> *> layerNodes;
        TreeNode<T> *cur = NULL;
        layerNodes.push(root);

        while( !layerNodes.empty() ) {
            if( (curWidth = layerNodes.size()) > maxWidth ) {
                maxWidth = curWidth;
            }

            for( size_t i = 0; i < curWidth; ++i ) {
                cur = layerNodes.front();
                if( cur->left != NULL )
                    layerNodes.push(cur->left);
                if(cur->right != NULL)
                    layerNodes.push(cur->right);

                layerNodes.pop();
            }
        }

        return maxWidth;
    }

private:
    TreeNode<T> *root;
};



int main() {
    NaiveTree<long> naive;
    TreapTree<long> treap;

    size_t n = 0;
    std::cin >> n;

    long data = 0;
    int priority = 0;

    for( size_t i = 0; i < n; ++i ) {
        if( std::cin >> data >> priority ) {
            naive.insert(data);
            treap.insert(data, priority);
        }
    }

    std::cout << treap.get_mWidth() - naive.get_mWidth() << std::endl;

    return 0;
}




    //
    //                       _oo0oo_
    //                      o8888888o
    //                      88" . "88
    //                      (| -_- |)
    //                      0\  =  /0
    //                    ___/`---'\___
    //                  .' \\|     |// '.
    //                 / \\|||  :  |||// \
    //                / _||||| -:- |||||- \
    //               |   | \\\  -  /// |   |
    //               | \_|  ''\---/''  |_/ |
    //               \  .-\__  '-'  ___/-. /
    //             ___'. .'  /--.--\  `. .'___
    //          ."" '<  `.___\_<|>_/___.' >' "".
    //         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
    //         \  \ `_.   \_ __\ /__ _/   .-` /  /
    //     =====`-.____`.___ \_____/___.-`___.-'=====
    //                       `=---='
    //
    //
    //     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //
    //               佛祖保佑         永无BUG
    //
