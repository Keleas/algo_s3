/****************************************************************************
Задача 3_1. Солдаты.

В одной военной части решили построить в одну шеренгу по росту. Т.к. часть
была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и
вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако
солдаты в процессе прихода и ухода должны были всегда быть выстроены по
росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат
отвечал прапорщик, который заметил интересную особенность – все солдаты в
части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику
правильно расставлять солдат, а именно для каждого приходящего солдата
указывать, перед каким солдатом в строе он должен становится. Требуемая
скорость выполнения команды - O(log n).

*Формат входных данных.*

Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой
следующей строке содержится описание команды: число 1 и X если солдат приходит
в строй (X – рост солдата, натуральное число до 100 000 включительно) и число
2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты
в строе нумеруются с нуля.

*Формат выходных данных.*

На каждую команду 1 (добавление в строй) вы должны выводить число K – номер
позиции, на которую должен встать этот солдат (все стоящие за ним двигаются
назад).

  in    | out
  ----- | ---
  5     | 0
  1 100 | 0
  1 200 | 2
  1 50  | 1
  2 1   |
  1 150 |

****************************************************************************/


/****************************************************************************
Идея:

Ввкдем в лист параметр - количество узлов у каждого листа и будем отслеживать их
количество в процессе добавления нового листа в дерево.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Повороты:

           p           <--(left)           q
          /  \       (right)-->         /   \
        q     C                          A       p
      /  \                                        /  \
   A      B                                    B    C

****************************************************************************/

struct Node
{
    int key; // ключ
    int nodes; // количество узлов у данного листа
    uint8_t height; //1 byte
    Node* left;
    Node* right;

    Node(int _key)
        : key{_key}, height{1}, nodes{1}, left{NULL} , right{NULL}
    {}
};


unsigned char height(Node* p) {
    return p ? p->height : NULL;
}


//балансировочный фактор
int bfactor(Node* p) {
    return height(p->right) - height(p->left);
}


int Nodes(Node* p) {
    return ( p == NULL ) ? 0 : p->nodes;
}


void fixNodes(Node* p) {
    int left_h = Nodes(p->left);
    int right_h = Nodes(p->right);

    p->nodes = left_h + right_h + 1;
}


//восстановление корректного значения height
void fixHeight(Node* p) {
    unsigned char h1 = height(p->right);
    unsigned char h2 = height(p->left);

    p->height = std::max(h1,h2) + 1;
}


//правый поворот
Node* rotate_right(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;

    fixNodes(p);
    fixNodes(q);

    fixHeight(q);
    fixHeight(p);

    return q;
}


//левый поворот
Node* rotate_left(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;

    fixNodes(q);
    fixNodes(p);

    fixHeight(q);
    fixHeight(p);

    return p;
}


//балнсировка поворотами
Node* balance(Node* p) {
    fixHeight(p);
    if( bfactor(p) == 2 ) {
        if( bfactor(p->right) < 0 )
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if( bfactor(p) == -2 ) {
        if( bfactor(p->left) > 0 )
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }

    return p;
}


Node* insert(Node* p, int k, int& position) {
    if( !p ) return new Node(k);

    ++(p->nodes);

    if( k < p->key ) {
        position += Nodes(p->right) + 1;
        p->left = insert(p->left, k, position);
    } else
        p->right = insert(p->right, k, position);

    return balance(p);
}


Node* find_min(Node* p) {
    return p->left ? find_min(p->left) : p;
}


Node* remove_min(Node* p) {
    if( p->left == 0 )
        return p->right;

    p->left = remove_min(p->left);
    --p->nodes;

    return balance(p);
}


Node* Remove(Node* p, int position) {
    if( p == NULL ) return NULL;
    if( position >= p->nodes ) return p;

    int current = 0;
    std::stack<Node *> nodes;

    while( true ) {
        int nodes_right = Nodes(p->right);
        // в противном случае, номер лежит левее корня дерева
        if( position - current > nodes_right ) {
            nodes.push(p);
            p = p->left;
            current += nodes_right + 1;
        } // правее корня
        else if( position - current < nodes_right ) {
            if( p->right != NULL ) {
                nodes.push(p);
                p = p->right;
            } else {
                break;
            }
        } else {
            // нашли место, с которого нужно удалить
            //сохранили его данные для налаживания связей
            Node *left = p->left;
            Node *right = p->right;
            int key = p->key;

            delete p;

            // если не было у удаляемого эл-та дочерних, то
            // просто вытаскиваем предшествующий ему из стека
            if( right == NULL ) {
                //если не было левого
                if( left == NULL ) {
                    if( !nodes.empty() ) {
                        p = nodes.top();
                        nodes.pop();
                        //налаживаем связи
                        if (p->key > key) {
                            p->left = NULL;
                        } else {
                            p->right = NULL;
                        }

                        --p->nodes;
                    } else {
                        return NULL;
                    }
                } else {
                    // если у него был левый, меньше него элемент
                    p = left;
                }
            } else {
                // если был правый, больше него элемент
                Node* min = find_min(right);
                min->right = remove_min(right);
                min->left = left;
                fixNodes(min);
                p = balance(min);
            }
            break;
        }
    }

    // вытаскиваем все из стека обратно
    while( !nodes.empty() ) {
        Node *node = nodes.top();
        --node->nodes;

        if( node->key > p->key ) {
            node->left = p;
        } else {
            node->right = p;
        }

        p = balance(node);
        nodes.pop();
    }

    return p;
}


enum OP{ ADD = 1, DELETE = 2 };

int main()
{
    int n;
    std::cin >> n;

     Node* root = NULL;
     std::vector<int> result;

     int cmd, key, position;

     for( size_t i = 0; i < n; ++i ) {
         std::cin >> cmd;

         switch( cmd ) {
         case OP::ADD :
             position = 0;
             std::cin >> key;
             root = insert(root, key, position);
             result.push_back(position);
             break;
        case OP::DELETE :
             std::cin >> key;
            root = Remove(root, key);
             break;
        default :
             break;
         }
     }

     for( size_t i = 0; i < result.size(); ++i )
         std::cout << result[i] << std::endl;

     return 0;
}
