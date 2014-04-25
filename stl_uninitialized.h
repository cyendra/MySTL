#ifndef STL_UNINITIALIZED_H_INCLUDED
#define STL_UNINITIALIZED_H_INCLUDED

#include "stl_construct.h"

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator res) {
    ForwardIterator cur = res;
    for ( ; first != last; ++first, ++cur) { construct(&*cur, *first); }
    return cur;
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
    ForwardIterator cur = first;
    for ( ; cur != last; ++cur ) { construct(&*cur, x); }
}

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
    ForwardIterator cur = first;
    for ( ; n > 0; --n, ++cur ) { construct(&*cur, x); }
    return cur;
}


#endif // STL_UNINITIALIZED_H_INCLUDED
