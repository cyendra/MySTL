#ifndef STL_ALGOBASE_H_INCLUDED
#define STL_ALGOBASE_H_INCLUDED
#include "stl_iterator.h"



template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator res, input_iterator_tag) {
    for ( ; first != last; ++res, ++first) { *res = *first; }
    return res;
}

template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator res, random_access_iterator_tag) {
    return __copy_d(first, last, res, distance_type(first));
}

template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator res, Distance*) {
    for (Distance n = last - first; n > 0; --n, ++res, ++first) { *res = *first; }
    return res;
}

template <class T>
inline T* __copy_t(const T* first, const T* last, T* res) {
    return __copy_d(first,last,res,(ptrdiff_t*)0);
}

template <class InputIterator, class OutputIterator>
struct __copy_dispatch {
    OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator res) {
        return __copy(first, last, res, iterator_category(first));
    }
};

template <class T>
struct __copy_dispatch<const T*, T*> {
    T* operator()(const T* first, const T* last, T* res) {
        return __copy_t(first, last, res);
    }
};

template <class T>
struct __copy_dispatch<T*, T*> {
    T* operator()(T* first, T* last, T* res) {
        return __copy_t(first, last, res);
    }
};


template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator res) {
    return __copy_dispatch<InputIterator,OutputIterator>()(first,last,res);
}


#endif // STL_ALGOBASE_H_INCLUDED
