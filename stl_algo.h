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



#endif // STL_ALGO_H_INCLUDED
