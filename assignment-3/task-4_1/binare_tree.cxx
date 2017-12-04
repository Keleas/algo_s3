#include <huffman.h>

Node* Node::insert( Node *n )
{
    if( !n ) return this;
    if( !this ) return n;
    Node *parent {nullptr};
    Node*t{this->root()};
    while( t ) {
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


Node* Node::transplant( Node* q )
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

Node* Node::Delete()
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

Node* Node::find( int k )
{
    if( !this || k == key )
        return this;
    if( k < key ) return lt->find(k);
    else return rt->find(k);
}

Node* Node::minimum()
{
    if( !this ) return nullptr;
    Node *t{this};
    while( t->lt )
        t = t->lt;
    return t;
}

Node* Node::maximum()
{
    if( !this ) return nullptr;
    Node *t{this};
    while( t->rt )
        t = t->rt;
    return t;
}

Node* Node::root()
{
    if( !this ) return nullptr;
    Node *t{this};
    while ( t->p )
        t = t->p;
    return t;
}

Node* Node::next()
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

Node* Node::prev()
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



/*---------------------------------------------
                        sun functions
---------------------------------------------*/

void wfs( Node *t ) //обход по слоям
{
    std::queue<Node*> q;
    q.push(t);
    while ( !q.empty() )
    {
        Node* x = q.front();
        q.pop();
        std::cout << x->data << "|";
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

void print_key( Node *t )
{
    std::cout << t->key << " ";
}
