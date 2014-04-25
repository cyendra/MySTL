#ifndef STL_CONSTRUCT_H_INCLUDED
#define STL_CONSTRUCT_H_INCLUDED

#include <new>

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
    new (p) T1(value);
}

template <class T>
inline void destroy(T* pointer) {
    pointer->~T();
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    for ( ; first < last; ++first) {
        destroy(&*first);
    }
}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}


#endif // STL_CONSTRUCT_H_INCLUDED
