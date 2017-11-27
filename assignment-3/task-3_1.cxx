/****************************************************************************
Задача 3_1. Солдаты.

*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           p           <--(left)           q
*          /  \       (right)-->         /   \
*        q     C                          A       p
*      /  \                                        /  \
*   A      B                                    B    C
*


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

//вставка
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

        if( position - current > nodes_right ) {
            nodes.push(p);
            p = p->left;
            current += nodes_right + 1;
        } else if( position - current < nodes_right ) {
            if( p->right != NULL ) {
                nodes.push(p);
                p = p->right;
            } else {
                break;
            }
        } else {
            Node *left = p->left;
            Node *right = p->right;
            int key = p->key;

            delete p;

            if( right == NULL ) {
                if( left == NULL ) {
                    if( !nodes.empty() ) {
                        p = nodes.top();
                        nodes.pop();

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
                    p = left;
                }
            } else {
                Node* min = find_min(right);
                min->right = remove_min(right);
                min->left = left;
                fixNodes(min);
                p = balance(min);
            }
            break;
        }
    }

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

void Delete(Node *p) {
    if ( !p ) return;

    Delete(p->left);
    Delete(p->right);

    delete p;
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
