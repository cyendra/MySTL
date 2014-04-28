#ifndef STL_ALGOBASE_H_INCLUDED
#define STL_ALGOBASE_H_INCLUDED
#include "stl_iterator.h"

/**** copy ****/

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

/**** copy_backward ****/

template <class BidirectionalIterator1,
          class BidirectionalIterator2>
inline BidirectionalIterator2 __copy_backward(BidirectionalIterator1 first,
                                     BidirectionalIterator1 last,
                                     BidirectionalIterator2 res,
                                     bidirectional_iterator_tag) {
    --last;
    --res;
    for ( ; first != last; --res, --last) { *res = *last; }
    *res = *first;
    return res;
}

template <class RandomAccessIterator,
          class BidirectionalIterator>
inline BidirectionalIterator __copy_backward(RandomAccessIterator first,
                                    RandomAccessIterator last,
                                    BidirectionalIterator res,
                                    random_access_iterator_tag) {
    return __copy_backward_d(first, last, res, distance_type(first));
}

template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_backward_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator res, Distance*) {
    Distance n = last - first;
    --last;
    --res;
    for ( ; n > 0; --n, --res, --last) { *res = *last; }
    return res;
}

template <class T>
inline T* __copy_backward_t(const T* first, const T* last, T* res) {
    return __copy_backward_d(first,last,res,(ptrdiff_t*)0);
}


template <class BidirectionalIterator1,
          class BidirectionalIterator2>
struct __copy_backward_dispatch {
    BidirectionalIterator2 operator()(BidirectionalIterator1 first,
                                      BidirectionalIterator1 last,
                                      BidirectionalIterator2 res) {
        return __copy_backward(first, last, res, iterator_category(first));
    }
};

template <class T>
struct __copy_backward_dispatch<const T*, T*> {
    T* operator()(const T* first, const T* last, T* res) {
        return __copy_backward_t(first, last, res);
    }
};

template <class T>
struct __copy_backward_dispatch<T*, T*> {
    T* operator()(T* first, T* last, T* res) {
        return __copy_backward_t(first, last, res);
    }
};


template <class BidirectionalIterator1,
          class BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
                                            BidirectionalIterator1 last,
                                            BidirectionalIterator2 res) {
    return __copy_backward_dispatch<BidirectionalIterator1,BidirectionalIterator2>()(first,last,res);
}





/**** Çó×îÖµ max/min ****/
template <class T>
inline const T& max(const T& a, const T& b) { return a < b? b : a; }

template <class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) { return comp(a, b) ? b : a; }

template <class T>
inline const T& min(const T& a, const T& b) { return a < b? a : b; }

template <class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp) { return comp(b, a) ? b : a; }

/**** fill ****/
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    for ( ; first != last; ++first ) { *first = value; }
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for ( ; n > 0; --n, ++first ) { *first = value; }
    return first;
}

/**** swap ****/
template <class T>
inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    __iter_swap(a, b, value_type(a));
}

/** equal **/
template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    for ( ; first1 != last1; ++first1, ++first2 ) {
        if (*first1 != *first2) { return false; }
    }
    return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred) {
    for ( ; first1 != last1; ++first1, ++first2 ) {
        if (!binary_pred(*first1, *first2)) { return false; }
    }
    return true;
}

#endif // STL_ALGOBASE_H_INCLUDED
