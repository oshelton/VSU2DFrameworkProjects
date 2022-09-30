#ifndef ASSOCIATIVEITERATOR_H_INCLUDED
#define ASSOCIATIVEITERATOR_H_INCLUDED

#include "dll.h"

///Basic struct for representing a pair of pointers.
struct Pair <T, U>
{
    T* first;
    T* second;

    Pair(T* f, U* s)
    {
        first = f;
        second = s;
    }
};

///Basic struct for representing a pair of const pointers.
struct ConstPair <T, U>
{
    T* const first;
    T* const second;

    Pair(T* const f, U* const s)
    {
        first = f;
        second = s;
    }
};

///Templated iterator type for use with associative data structures.  This class and its subclasses implement the Iterator pattern.
class EXPORT_FRAME AssocitiveIterator <T, U>
{
public:
    ///Require virtual deconstructor.
    virtual AssociativeIterator();

    ///Get whether or not the Iterator has any more elements.
    virtual bool hasElement() = 0;
    ///Retrieve the Iterators current element and increment whatever is being used to keep track of where we are in the Container.
    virtual const Pair<T, U>& next() = 0;
};

///Templated iterator type for const iterators for use with associative data structures.  This class and its subclasses implement the Iterator pattern.
class EXPORT_FRAME ConstAssociativeIterator <T, U>
{
public:
    ///Require virtual deconstructor.
    virtual Iterator();

    ///Get whether or not the Iterator has any more elements.
    virtual bool hasElement() = 0;
    ///Retrieve the Iterators current element and increment whatever is being used to keep track of where we are in the Container.
    virtual const ConstPair<T, U> const next() = 0;
};

#endif // ASSOCIATIVEITERATOR_H_INCLUDED
