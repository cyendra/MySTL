#ifndef STL_LIST_H_INCLUDED
#define STL_LIST_H_INCLUDED

#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_iterator.h"
#include "stl_algobase.h"
#include "stl_uninitialized.h"

template <class T>
struct __list_node {
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <class T, class Ref, class Ptr>
struct __list_iterator {
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node;

    // constructor
    __list_iterator(link_type x) : node(x) {}
    __list_iterator() {}
    __list_iterator(const iterator& x) : node(x.node) {}

    // overloaded operator
    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }
    reference operator*() const { return (*node).data; }// dereference
    pointer operator->() const { return &(operator*()); }// member access
    self& operator++() {
        node = (link_type)((*node).next);
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        node = (link_type)((*node).prev);
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }
};

template <class T, class Alloc = myAlloc>
class list {
protected:
    typedef void* void_pointer;
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, const T&, const T*> const_iterator;
protected:
    link_type node;
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }
    link_type create_node(const T& x) {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }
    void destroy_node(link_type p) {
        destroy(&p->data);
        put_node(p);
    }
public:
    iterator begin() { return (link_type)((*node).next); }
    iterator end() { return node; }
    bool empty() const { return node->next == node; }
    size_type size() {
        size_type res = 0;
        distance(begin(),end(),res);
        //res = distance(begin(),end());
        return res;
    }
    reference front() { return *begin(); }
    reference back() { return *(--end()); }

    void push_back(const T& x) { insert(end(), x); }
    void push_front(const T& x) { insert(begin(), x); }
    void swap(list<T, Alloc>& x) { swap(node, x.node); }
    iterator insert(iterator pos, const T& x) {
        link_type tmp = create_node(x);
        tmp->next = pos.node;
        tmp->prev = pos.node->prev;
        (link_type(pos.node->prev))->next = tmp;
        pos.node->prev = tmp;
        return tmp;
    }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }
    iterator erase(iterator pos) {
        link_type next_node = (link_type)(pos.node->next);
        link_type prev_node = (link_type)(pos.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(pos.node);
        return iterator(next_node);
    }

    list() { empty_initialize(); }

    void splice(iterator pos, list& x) {
        if (!x.empty()) { transfer(pos, x.begin(), x.end()); }
    }
    void splice(iterator pos, list&, iterator i) {
        iterator j = i;
        ++j;
        if (pos == i || pos == j) return;
        transfer(pos, i, j);
    }
    void splice(iterator pos, list&, iterator first, iterator last) {
        if (first != last) { transfer(pos, first, last); }
    }

    void clear();
    void remove(const T& value);
    void unique();
    void merge(list& x);
    void reverse();
    void sort();

protected:
    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }
    void transfer(iterator pos, iterator first, iterator last) {
        if (pos != last) {
            (*(link_type((*last.node).prev))).next = pos.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*pos.node).prev))).next = first.node;
            link_type tmp = link_type((*pos.node).prev);
            (*pos.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }
};

template <class T, class Alloc>
void list<T, Alloc>::clear() {
    link_type cur = (link_type)node->next;
    while (cur != node) {
        link_type tmp = cur;
        cur = (link_type)cur->next;
        destroy_node(tmp);
    }
    node->next = node;
    node->prev = node;// no use?
}

template <class T, class Alloc>
void list<T, Alloc>::remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) erase(first);
        first = next;
    }
}

template <class T, class Alloc>
void list<T, Alloc>::unique() {
    iterator first = begin();
    iterator last = end();
    if (first == last) return;
    iterator next = first;
    while (++next != last) {
        if (*first == *next) erase(next);
        else first = next;
        next = first;
    }
}

template <class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x) {
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 =x.begin();
    iterator last2 = x.end();
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) {
            iterator next = first2;
            transfer(first1, first2, ++next);
            first2 = next;
        }
        else { ++first1; }
        if (first2 != last2) transfer(last1, first2, last2);
    }
}

template <class T, class Alloc>
void list<T, Alloc>::reverse() {
    if (node->next == node || link_type(node->next)->next == node) return;
    iterator first = begin();
    ++first;
    while (first != end()) {
        iterator old = first;
        ++first;
        transfer(begin(), old, first);
    }
}

template <class T, class Alloc>
void list<T, Alloc>::sort() {
    if (node->next == node || link_type(node->next)->next == node) return;
    list<T, Alloc> carry;
    list<T, Alloc> counter[64];
    int fill = 0;
    while (!empty()) {
        carry.splice(carry.begin(), *this, begin());
        int i = 0;
        while (i < fill && !counter[i].empty()) {
            counter[i].merge(carry);
            carry.swap(counter[i++]);
        }
        carry.swap(counter[i]);
        if (i == fill) ++fill;
    }
    for (int i = 1; i < fill; ++i) { counter[i].merge(counter[i-1]); }
    swap(counter[fill-1]);
}

#endif // STL_LIST_H_INCLUDED
