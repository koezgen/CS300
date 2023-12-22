//
// Created by koezgen on 8.12.2023.
//

#ifndef CS300HW3_HASHTABLE_H
#define CS300HW3_HASHTABLE_H

#include <vector>
#include <string>
#include <iostream>
#include "structs.h"
#define HASH_TABLE_LOAD_PARAMETER 0.85
using namespace std;

bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;

    return true;
}

int nextPrime( int n )
{
    if ( n % 2 == 0 )
        n++;

    for ( ; ! isPrime( n ); n += 2 )
        ;

    return n;
}

template <class HashedObj>
class HashTable
{
public:
    explicit HashTable( const HashedObj & notFound, int size = 101 );
    HashTable( const HashTable & rhs )
            : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
              array( rhs.array ), currentSize( rhs.currentSize ) { }

    const HashedObj & find( const HashedObj & x ) const;
    double loadFactor() const {
        return static_cast<double>(currentSize) / static_cast<double>(array.size());
    }
    void makeEmpty( );
    void insert( const HashedObj & x );
    void remove( const HashedObj & x );

    int unique_words();
    void increment_unique();

    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        explicit HashEntry( const HashedObj & e = HashedObj( ),
                   EntryType i = EMPTY )
                : element( e ), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize;
    int unique;
    const HashedObj ITEM_NOT_FOUND;

    [[nodiscard]] bool isActive( int currentPos ) const;
    int findPos( const HashedObj & x ) const;
    void rehash( );
};

template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound,
                                 int size )
        : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
    makeEmpty( );
}

template <class HashedObj>
int HashTable<HashedObj>::unique_words()
{
    return unique;
}

template <class HashedObj>
void HashTable<HashedObj>::increment_unique()
{
    unique++;
}

template <class HashedObj>
int hashFunc(const HashedObj& obj, int tableSize) {
    const string& key = obj->word;
    int hashVal = 0;

    for (char ch : key) {
        hashVal = 37 * hashVal + ch;
    }

    hashVal %= tableSize;
    if (hashVal < 0) {
        hashVal += tableSize;
    }

    return hashVal;
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const {
    int currentPos = hashFunc(x, array.size()); // Initial position
    int collisionNum = 0;

    // Loop until we find an empty spot or the element itself
    while (array[currentPos].info != EMPTY && array[currentPos].element->word != x->word) {
        collisionNum++;
        currentPos = hashFunc(x, array.size()) + collisionNum * collisionNum; // Recompute position
        currentPos %= array.size(); // Ensure the position is within bounds

        // Fail-safe to avoid infinite loops
        if (collisionNum >= array.size()) {
            return -1; // Table is full or cannot find a spot
        }
    }
    return currentPos;
}


template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        array[ currentPos ].info = DELETED;
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x) const {
    int currentPos = findPos(x);  // Find the position of x in the hash table

    // Check if the element at currentPos is active and equals x
    if (isActive(currentPos) && array[currentPos].element->word == x->word) {
        return array[currentPos].element;  // Element found, return it
    } else {
        return ITEM_NOT_FOUND;  // Element not found, return ITEM_NOT_FOUND
    }
}

template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        return;
    array[ currentPos ] = HashEntry( x, ACTIVE );

    // enlarge the hash table if necessary
    if (++currentSize >= static_cast<int>(array.size() * HASH_TABLE_LOAD_PARAMETER)) {
        rehash();
    }
}

template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for ( int j = 0; j < array.size( ); j++ )
        array[ j ].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
            insert( oldArray[ i ].element );

    cout << "rehashed..." << endl;
    cout << "Previous table size: " << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: " << unique_words() << ", current load factor: " << loadFactor() << endl;
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < array.size( ); i++ )
        array[i].info = EMPTY;
}

#endif
