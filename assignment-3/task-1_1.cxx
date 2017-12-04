/****************************************************************************
Дано число N &lt; 10^6 и последовательность целых чисел из [-2^31..2^31]
длиной N. Требуется построить бинарное дерево, заданное наивным порядком
вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если
root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
поддерево root.
****************************************************************************/

/****************************************************************************

Задача 1_1 Выведите элементы в порядке in-order (слева направо).

  in    | out
  ----- | ---
  3     |
  2 1 3 | 1 2 3

  in    | out
  ----- | ---
  3     |
  1 2 3 | 1 2 3

  in    | out
  ----- | ---
  3     |
  3 1 2 | 1 2 3

****************************************************************************/

#include <cassert>
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <assert.h>

class Node
{
public:
    const int key;
    Node(int k)
        : key {k}
    {}

    Node* insert( Node *n )
    {
        if( !n ) return this;
        if( !this ) return n;
        Node *parent {nullptr}, *t{this->root()};
        while( t )
        {
            parent = t;
            if( n->key < t->key ) t = t->lt;
            else t = t->rt;
        }
        n->p = parent;
        if( n->key < parent->key )
            parent->lt = n;
        else
            parent->rt = n;
        return this;
    }


    Node* transplant( Node* q )
    {
        if( !this ) return q;

        if(p) {
            if( this == p->lt )
                p->lt = q;
            else
                p->rt = q;
        }
        if( q ) q->p = p;

        return q;
    }

    Node* Delete()
    {
        if( !lt ) {
            return transplant(rt);
        } else if( !rt ) {
            return transplant(lt);
        }
        else {
            Node* y = rt->minimum();
            if( y->p != this ) {
                y->transplant(y->rt);
                y->rt = rt;
                y->rt->p = y;
            }
            transplant(y);
            y->lt = lt;
            y->lt->p = y;

            return y;
        }
     }

    Node* find( int k )
    {
        if( !this || k == key )
            return this;
        if( k < key ) return lt->find(k);
        else return rt->find(k);
    }

    Node* minimum()
    {
        if( !this ) return nullptr;
        Node *t{this};
        while( t->lt )
            t = t->lt;
        return t;
    }

    Node* maximum()
    {
        if( !this ) return nullptr;
        Node *t{this};
        while( t->rt )
            t = t->rt;
        return t;
    }

    Node* root()
    {
        if( !this ) return nullptr;
        Node *t{this};
        while ( t->p )
            t = t->p;
        return t;
    }

    Node* next()
    {
        if( !this ) return nullptr;
        if( rt )
            return rt->minimum();
        Node *parent{p}, *root{this};
        while( parent && root == parent->rt )
        {
            root = parent;
            parent = parent->p;
        }
        return parent;
    }

    Node* prev()
    {
        if( !this ) return nullptr;
        if( lt )
            return rt->maximum();
        Node *parent{p}, *root{this};
        while( parent && root == parent->lt )
        {
            root=parent;
            parent=parent->p;
        }
        return parent;
    }

    Node* right() { return rt; }
    Node* left() { return lt; }
    Node* parent() { return p; }

    bool is_leaf() { return !lt && !rt; }


private:
    Node *p {nullptr};                 // parent
    Node *lt {nullptr}, *rt {nullptr}; //left,right
};

/*---------------------------------------------
                        sun functions
---------------------------------------------*/

void print_min( Node *head )
{
    Node* x{head};
    Node* min = x->minimum();
    while( min )
    {
        std::cout << min->key << " ";
        min = min->next();
    }
}

void print_max( Node *head )
{
    Node* x{head};
    Node* max = x->maximum();
    while( max )
    {
        std::cout << max->key << " ";
        max = max->next();
    }
}

void wfs( Node *t ) //обход в ширину
{
    std::queue<Node*> q;
    q.push(t);
    while ( !q.empty() )
    {
        Node* x = q.front();
        q.pop();
        std::cout << x->key << " ";
        if( x->left() )
            q.push( x->left() );
        if( x->right() )
            q.push( x->right() );
    }
}

void prefix_traverse( Node *t, void f( Node* ) ) //обход в глубину
{
    f( t );
    if( t->left() )
        prefix_traverse( t->left(), f );
    if(t->right())
        prefix_traverse( t->right(), f );
}

void print_key( Node *t )  // function by traverse
{
    std::cout << t->key << " ";
}


void print_key_value( Node *t )
{
    std::cout << t->key << '\t';
}

//-----------------------------------------
// support function

bool summer( Node *head, int sum, const int d )         //1.15. find ways sum
{
    if( !head ) return false;
    sum += head->key;
    if( !head->is_leaf() )
        return summer( head->left(), sum, d ) || summer( head->right(), sum, d );
    if( head->is_leaf() && sum == d )
        return true;
    return false;
}

Node* read( const std::string& filename )
{
    std::ifstream ifs( filename );
    assert( ifs );

    int n;
    ifs >> n;
    Node* head = new Node{n};
    while( ifs >> n )
        head = head->insert(new Node{n});
    return head;
}


int main()
{
    Node* head = read( "E:\\tree.txt" );

    wfs( head );

    std::cout << "\n" << "--------------------------------------------------------------" << "\n";
    prefix_traverse( head, print_key );  // prefix way of tree (1.8 and 1.9)

    return 0;
}
