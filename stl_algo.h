#ifndef STL_ALGO_H_INCLUDED
#define STL_ALGO_H_INCLUDED

#include "stl_algobase.h"
#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_iterator.h"

/**** find ****/
template <class Iterator, class T>
Iterator find(Iterator begin, Iterator end, const T& value) {
    while (begin != end && *begin != value) ++begin;
    return begin;
}

/** accumulate **/
template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
    for ( ; first != last; ++first ) { init = init + *first; }
    return init;
}

template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
    for ( ; first != last; ++first ) { init = binary_op(init, *first); }
    return init;
}

/** reverse **/

template <class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag) {
    while (true) {
        if (first == last || first == --last) return;
        else iter_swap(first++,last);
    }
}

template <class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
    while (first < last) iter_swap(first++,--last);
}

template <class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
    __reverse(first, last, iterator_category(first));
}


/** permutation **/

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;) {
        BidirectionalIterator ii = i;
        --i;
        if (*i < *ii) {
            BidirectionalIterator j = last;
            while (!(*i < *--j));
            iter_swap(i,j);
            reverse(ii, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}


#endif // STL_ALGO_H_INCLUDED
