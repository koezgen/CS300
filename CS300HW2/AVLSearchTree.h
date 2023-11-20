//
// Created by koezgen on 20.11.2023.
//

#ifndef CS300HW2_AVLSEARCHTREE_H
#define CS300HW2_AVLSEARCHTREE_H

// Key is the COMPARABLE
// Value is the POINTER TO TREE NODE
template <class Key, class Value>
class AVLSearchTree
{
public:
    explicit AVLSearchTree( const Key & notFound );
    AVLSearchTree( const AVLSearchTree<Key, Value>& rhs);
    ~AVLSearchTree( );

    const Value & findMin( ) const;
    const Value & findMax( ) const;
    const Value & find( const Key & x ) const;

    void makeEmpty( );
    void insert( const Key & x );
    void remove( const Key & x );

private:
    Value root;
    const Key ITEM_NOT_FOUND;

    const Key & elementAt( Value t ) const;

    void insert( const Key & x, Value & t ) const;
    void remove(const Key & x, Value & t ) const;

    Value findMin( Value t ) const;
    Value findMax( Value t ) const;
    Value find( const Key & x, Value t ) const;
    void makeEmpty( Value & t ) const;

    // Avl manipulations
    int height( Value t ) const;
    int max( int lhs, int rhs ) const;
    void rotateWithLeftChild( Value & k2 ) const;
    void rotateWithRightChild( Value & k1 ) const;
    void doubleWithLeftChild( Value & k3 ) const;
    void doubleWithRightChild( Value & k1 ) const;
};

template<class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree(const Key &notFound) {
    ITEM_NOT_FOUND = notFound;
    root = NULL;
}

template<class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree(const AVLSearchTree<Key, Value> &rhs)
: root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

template<class Key, class Value>
AVLSearchTree<Key, Value>::~AVLSearchTree() {
    makeEmpty( );
}

template<class Key, class Value>
const Value &AVLSearchTree<Key, Value>::findMin() const {
    return elementAt( findMin( root ) );
}

template<class Key, class Value>
const Value &AVLSearchTree<Key, Value>::findMax() const {
    return elementAt( findMax( root ) );
}

template<class Key, class Value>
const Value &AVLSearchTree<Key, Value>::find(const Key &x) const {
    return elementAt( find( x, root ) );
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty() {
    makeEmpty( root );
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key &x) {
    insert( x, root );
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key &x) {
    remove( x, root );
}


template<class Key, class Value>
const Key &AVLSearchTree<Key, Value>::elementAt(Value t) const {
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key &x, Value &t) const {
    if ( t == NULL )
        t = new Value( x, NULL, NULL );

    else if ( x < t->element ) {
        // X should be inserted to the left tree!
        insert( x, t->left );

        // Check if the left tree is out of balance (left subtree grew in height!)
        if ( height( t->left ) - height( t->right ) == 2 )
            if ( x < t->left->element )  // X was inserted to the left-left subtree!
                rotateWithLeftChild( t );
            else			     // X was inserted to the left-right subtree!
                doubleWithLeftChild( t );
    }

    else if( t->element < x )
    {    // Otherwise X is inserted to the right subtree
        insert( x, t->right );
        if ( height( t->right ) - height( t->left ) == 2 )
            // height of the right subtree increased
            if ( t->right->element < x )
                // X was inserted to right-right subtree
                rotateWithRightChild( t );
            else // X was inserted to right-left subtree
                doubleWithRightChild( t );
    }
    else
        ;  // Duplicate; do nothing

    // update the height the node
    t->height = max( height( t->left ), height( t->right ) ) + 1;

}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key &x, Value &t) const {
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        Value *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

template<class Key, class Value>
Value AVLSearchTree<Key, Value>::findMin(Value t) const {
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template<class Key, class Value>
Value AVLSearchTree<Key, Value>::findMax(Value t) const {
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template<class Key, class Value>
Value AVLSearchTree<Key, Value>::find(const Key &x, Value t) const {
    if ( t == NULL )
        return NULL;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x )
        return find( x, t->right );
    else
        return t;
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty(Value &t) const {
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template<class Key, class Value>
int AVLSearchTree<Key, Value>::height(Value t) const {
    if (t == NULL)
        return -1;

    return t->height;
}

template<class Key, class Value>
int AVLSearchTree<Key, Value>::max(int lhs, int rhs) const {
    if (lhs > rhs)
        return lhs;

    return rhs;
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithLeftChild(Value &k2) const {
    Value k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithRightChild(Value &k1) const {
    Value k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithLeftChild(Value &k3) const {
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template<class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithRightChild(Value &k1) const {
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

#endif
