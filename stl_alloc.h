#ifndef STL_ALLOC_H_INCLUDED
#define STL_ALLOC_H_INCLUDED

#include <iostream>
#define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1)

#include <cstdlib>

template <int inst>
class __malloc_alloc_template {
private:

    // 内存不足的情况
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (* __malloc_alloc_oom_handler)();

public:

    static void *allocate(size_t n) {
        void *res = malloc(n);
        if (res == 0) res = oom_malloc(n);
        return res;
    }

    static void deallocate(void *p, size_t /* n */) {
        free(p);
    }

    static void *reallocate(void *p, size_t /* old_sz */, size_t new_sz) {
        void *res = realloc(p,new_sz);
        if (res == 0) res = oom_realloc(p, new_sz);
        return res;
    }
    typedef void(*pt2Func)();
    static pt2Func (* set_malloc_handler(void (*f)())) {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return(old);
    }

};

template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n) {
    void (* my_malloc_handler)();
    void *res;
    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)();
        res = malloc(n);
        if (res) return(res);
    }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
    void (* my_malloc_handler)();
    void *res;
    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)();
        res = realloc(p, n);
        if (res) return(res);
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc myAlloc;

template<class T, class Alloc>
class simple_alloc {
public:
    static T* allocate(size_t n) {
        return n==0 ? 0 : (T*)Alloc::allocate(n * sizeof(T));
    }
    static T* allocate(void) {
        return (T*)Alloc::allocate(sizeof(T));
    }
    static void deallocate(T *p, size_t n) {
        if (n!=0) Alloc::deallocate(p, n * sizeof(T));
    }
    static void deallocate(T *p) {
        Alloc::deallocate(p, sizeof(T));
    }
};

#endif // STL_ALLOC_H_INCLUDED
