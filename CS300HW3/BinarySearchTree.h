//
// Created by koezgen on 8.12.2023.
//

#ifndef CS300HW3_BINARYSEARCHTREE_H
#define CS300HW3_BINARYSEARCHTREE_H

#include <sstream>

using namespace std;

struct wordcount {
    string wordname;
    int count;
};

struct textFile {

    string fileName;
    vector<wordcount> word_count;
};

struct DocumentItem {
    string documentName;
    int count;
};

struct WordItem {
    WordItem(string word) : word(word), left(nullptr), right(nullptr), height(0) {}
    WordItem( const string & theElement, WordItem *lt, WordItem *rt, int h = 0 )
            : word( theElement ), left( lt ), right( rt ), height( h ) { }
    string word;
    WordItem* left;
    WordItem* right;
    vector<DocumentItem> details;
    int height;
};

struct FileContents {
    string FileName;
    vector<string> FileContent;

    FileContents(string filename, vector<string> content);
};

FileContents::FileContents(string filename, vector<string> content) {
    FileName = filename;
    FileContent = content;
}
// Key is the COMPARABLE
// Value is the POINTER TO TREE NODE
template <class Key, class Value>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(Key notFound);
    ~BinarySearchTree( );

    const Value & findMin( ) const;
    const Value & findMax( ) const;
    Value find( Key x ) const;

    void makeEmpty( );
    void insert( const Key & x );
    void remove( const Key & x );

private:
    Value root;
    Value ITEM_NOT_FOUND;

    const Key & elementAt( Value t ) const;

    void insert( const Key & x, Value & t ) const;
    void remove(const Key & x, Value & t ) const;

    Value findMin( Value t ) const;
    Value findMax( Value t ) const;
    Value find( Key x, Value t ) const;
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
BinarySearchTree<Key, Value>::BinarySearchTree(Key notFound)
        : ITEM_NOT_FOUND(new WordItem(notFound))
{
    root = NULL;
}

template<class Key, class Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    makeEmpty( );
}

template<class Key, class Value>
const Value &BinarySearchTree<Key, Value>::findMin() const {
    return elementAt( findMin( root ) );
}

template<class Key, class Value>
const Value &BinarySearchTree<Key, Value>::findMax() const {
    return elementAt( findMax( root ) );
}

template<class Key, class Value>
Value BinarySearchTree<Key, Value>::find(Key x) const {
    return find( x, root );
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::makeEmpty() {
    makeEmpty( root );
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const Key &x) {
    insert( x, root );
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::remove(const Key &x) {
    remove( x, root );
}

template<class Key, class Value>
const Key &BinarySearchTree<Key, Value>::elementAt(Value t) const {
    if (t == NULL) {
        return ITEM_NOT_FOUND->word; // Assuming ITEM_NOT_FOUND is a Key
    }
    return t->word; // Assuming 'word' is a Key (std::string) in the WordItem
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const Key &x, Value &t) const {
    if (t == NULL) {
        t = new WordItem(x); }

    else if ( x < t->word ) {
        // X should be inserted to the left tree!
        insert( x, t->left );
    }

    else if( t->word < x )
    {    // Otherwise X is inserted to the right subtree
        insert( x, t->right );
    }
    else
        ; // Why spend CPU Clock on this????

    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::remove(const Key &x, Value &t) const {
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->word )
        remove( x, t->left );
    else if( t->word < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->word = findMin(t->right)->word;  // Get the minimum word from the right subtree
        remove(t->word, t->right);
    }
    else // one or no children
    {
        Value oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

template<class Key, class Value>
Value BinarySearchTree<Key, Value>::findMin(Value t) const {
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template<class Key, class Value>
Value BinarySearchTree<Key, Value>::findMax(Value t) const {
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template<class Key, class Value>
Value BinarySearchTree<Key, Value>::find(Key x, Value t) const
{
    if ( t == nullptr )
        return ITEM_NOT_FOUND;
    else if( x < t->word )
        return find( x, t->left );
    else if( t->word < x )
        return find( x, t->right );
    else
        return t;    // Match
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::makeEmpty(Value &t) const {
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template<class Key, class Value>
int BinarySearchTree<Key, Value>::height(Value t) const {
    if (t == NULL)
        return -1;

    return t->height;
}

template<class Key, class Value>
int BinarySearchTree<Key, Value>::max(int lhs, int rhs) const {
    if (lhs > rhs)
        return lhs;

    return rhs;
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::rotateWithLeftChild(Value &k2) const {
    Value k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::rotateWithRightChild(Value &k1) const {
    Value k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::doubleWithLeftChild(Value &k3) const {
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::doubleWithRightChild(Value &k1) const {
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

#endif //CS300HW3_BINARYSEARCHTREE_H
