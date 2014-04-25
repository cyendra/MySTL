#ifndef STL_VECTOR_H_INCLUDED
#define STL_VECTOR_H_INCLUDED

#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_iterator.h"
#include "stl_uninitialized.h"
#include "stl_algobase.h"
#include "stl_algo.h"

template <class T, class Alloc = myAlloc>
class vector {
public:
    typedef T            value_type;
    typedef value_type*  pointer;
    typedef value_type*  iterator;
    typedef value_type&  reference;
    typedef size_t       size_type;
    typedef ptrdiff_t    difference_type;
protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void insert_aux(iterator position, const T& x);
    void deallocate() {
        if (start) {
            data_allocator::deallocate(start, end_of_storage - start);
        }
    }
    void fill_initialize(size_type n, const T& value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return size_type(finish - start); }
    size_type capacity() const { return size_type(end_of_storage - start); }
    bool empty() const { return start == finish; }
    reference operator[](size_type n) { return *(start + n); }

    vector():start(0),finish(0),end_of_storage(0) {}
    vector(size_type n, const T& value) { fill_initialize(n, value); }
    vector(int n, const T& value) { fill_initialize(n, value); }
    vector(long n, const T& value) { fill_initialize(n, value); }
    explicit vector(size_type n) { fill_initialize(n, T()); }

    ~vector() {
        destroy(start, finish);
        deallocate();
    }
    reference front() { return *start; }
    reference back() { return *(finish - 1); }
    void push_back(const T& x) {
        if (finish != end_of_storage) {
            construct(finish, x);
            ++finish;
        }
        else {
            insert_aux(finish, x);
        }
    }
    void pop_back() {
        --finish;
        destroy(finish);
    }
    iterator erase(iterator pos) {
        if (pos + 1 != finish) { copy(pos + 1, finish, pos); }
        --finish;
        destroy(finish);
        return pos;
    }
    iterator erase(iterator first, iterator last) {
        iterator i = copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }
    void resize(size_type new_size, const T& x) {
        if (new_size < size()) { erase(start + new_size, finish); }
        else { insert(finish, new_size - size(), x); }
    }
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() { erase(start, finish); }
    void insert(iterator pos, size_type n, const T& x);
protected:
    iterator allocate_and_fill(size_type n, const T& x) {
        iterator res = data_allocator::allocate(n);
        uninitialized_fill_n(res, n, x);
        return res;
    }

private:
};

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
    if (finish != end_of_storage) {
        construct(finish, *(finish - 1));
        ++finish;
        T x_copy = x;
        copy_backward(position, finish - 1, finish);
        *position = x_copy;
    }
    else {
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2 * old_size : 1;
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try {
            new_finish = uninitialized_copy(start, position, new_start);
            construct(new_finish, x);
            ++new_finish;
            new_finish = uninitialized_copy(position, finish, new_finish);
        }
        catch (...) {
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }
        destroy(begin(),end());
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator pos, size_type n, const T& x) {
    if (n != 0) {
        if (size_type(end_of_storage - finish) >= n) {
            T x_copy = x;
            const size_type elems_after = finish - pos;
            iterator old_finish = finish;
            if (elems_after > n) {
                uninitialized_copy(finish - n, finish, finish);
                finish += n;
                copy_backward(pos, old_finish - n, old_finish);
                fill(pos, pos + n, x_copy);
            }
            else {
                uninitialized_fill_n(finish, n - elems_after, x_copy);
                finish += n -elems_after;
                uninitialized_copy(pos, old_finish, finish);
                finish += elems_after;
                fill(pos, old_finish, x_copy);
            }
        }
        else {
            const size_type old_size = size();
            const size_type len = old_size + max(old_size, n);
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start, pos, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, x);
                new_finish = uninitialized_copy(pos, finish, new_finish);
            }
            catch (...) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw;
            }
            destroy(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }
}


#endif // STL_VECTOR_H_INCLUDED
