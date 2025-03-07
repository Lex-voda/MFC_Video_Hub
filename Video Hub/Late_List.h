#ifndef _LATELIST_H
#define _LATELIST_H
#include<iostream>
using namespace std;
template <typename T> class Node;
template <typename T> class Iterator;
template <typename T> class List;

template <typename T>                   // element of the list (unidirectional)
class Node {
private:
    T data;
    Node<T>* prev;
    Node<T>* next;
public:
    Node() : prev(nullptr), next(nullptr) {}
    Node(const T& content) : data(content), prev(nullptr), next(nullptr) {}
    ~Node() = default;
    friend class Iterator<T>;
    friend class List<T>;
};

template <typename T>                   // Iterator of the Node
class Iterator {
private:
    Node<T>* current;
public:
    Iterator() : current(nullptr) {}
    ~Iterator() = default;
    T& operator*();
    T* operator->();
    Iterator<T> operator+(int);
    Iterator<T> operator-(int);
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);
    bool operator==(const Iterator<T>& rhs) const;
    bool operator!=(const Iterator<T>& rhs) const;
    friend class List<T>;
};

template <typename T>
class List {
    typedef Node<T>* Ptr;
private:
    Ptr head, tail;
    int list_size;
public:
    List();
    List(const List<T>&);
    ~List();
    const List<T>& operator=(List<T>& rhs);
    Iterator<T> begin()
    {
        Iterator<T> it; it.current = head->next; return it;
    }
    Iterator<T> end()
    {
        Iterator<T> it; it.current = tail; return it;
    }
    Iterator<T> find(Iterator<T> first, Iterator<T> last, const T& obj);
    bool empty() const;
    int size() const;
    void clear();
    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();
    const T& front();
    const T& back();
    Iterator<T> insert(const Iterator<T>&, T);
    Iterator<T> remove(const T&);
    Iterator<T> remove(Iterator<T>&);
    void print();
};

// overloaded operators
template <typename T>
inline T& Iterator<T>::operator*()
{
    return current->data;
}

template <typename T>
inline T* Iterator<T>::operator->()
{
    return &(current->data);
}

template <typename T>
inline Iterator<T>& Iterator<T>::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> pointer = *this;
    current = current->next;
    return pointer;
}

template <typename T>
inline Iterator<T>& Iterator<T>::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
inline Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T> pointer = *this;
    current = current->prev;
    return *this;
}

template <typename T>
inline Iterator<T> Iterator<T>::operator+(int n)
{
    Iterator<T> pointer = *this;
    for (int i = 0; i < n; i++)
        pointer++;
    return pointer;
}

template <typename T>
inline Iterator<T> Iterator<T>::operator-(int n)
{
    Iterator<T> pointer = *this;
    for (int i = 0; i < n; i++)
        pointer--;
    return pointer;
}

template <typename T>
inline bool Iterator<T>::operator==(const Iterator<T>& rhs) const
{
    return current == rhs.current ? true : false;
}

template <typename T>
inline bool Iterator<T>::operator!=(const Iterator<T>& rhs) const
{
    return !(this->current == rhs.current);
}

template <typename T>
inline List<T>::List()
    : list_size(0), head(new Node<T>), tail(new Node<T>)
{
    head->next = tail;
    tail->prev = head;
}

template <typename T>
inline List<T>::List(const List<T>& rhs)
    : list_size(0), head(new Node<T>), tail(new Node<T>)
{
    head->next = tail;
    tail->prev = head;
    for (Iterator<T> it = rhs.begin(); it != rhs.end(); it++)
        push_back(*it);
}

template <typename T>
inline List<T>::~List()
{
    clear();
    delete head;
    delete tail;
}

template <typename T>
inline const List<T>& List<T>::operator=(List<T>& rhs)
{
    if (this != &rhs) {
        clear();
        for (Iterator<T> it = rhs.begin(); it != rhs.end(); it++)
            push_back(*it);
    }
    return *this;
}

template <typename T>
inline bool List<T>::empty() const
{
    return list_size == 0 ? true : false;
}

template <typename T>
inline int List<T>::size() const
{
    return list_size;
}

// insert at the end
template <typename T>
void List<T>::push_back(const T& rhs)
{
    Node<T>* temp = new Node<T>(rhs);
    tail->prev->next = temp;
    temp->prev = tail->prev;
    tail->prev = temp;
    temp->next = tail;
    ++list_size;
}

// delete the last element
template <typename T>
void List<T>::pop_back()
{
    if (empty())
        return;
    else {
        Node<T>* temp = tail->prev;
        temp->prev->next = tail;
        tail->prev = temp->prev;
        delete temp;
        --list_size;
    }
}

// insert at the first
template <typename T>
void List<T>::push_front(const T& rhs)
{
    Node<T>* temp = new Node<T>(rhs);
    temp->next = head->next;
    head->next->prev = temp;
    head->next = temp;
    temp->prev = head;
    ++list_size;
}

// delete the first element
template <typename T>
void List<T>::pop_front()
{
    if (empty())
        return;
    else {
        Node<T>* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        --list_size;
    }
}

// delete all the node (expect the head and tail)
template <typename T>
void List<T>::clear()
{
    while (!empty())
        pop_back();
}

// return the first element's content
template <typename T>
const T& List<T>::front()
{
    if (!empty())
        return head->next->data;
}

// return the last element's content
template <typename T>
const T& List<T>::back()
{
    if (!empty())
        return tail->prev->data;
}

// find the numth element and return its iterator
template <typename T>
Iterator<T> List<T>::find(Iterator<T> first, Iterator<T> last, const T& obj)
{
    while (first != last) {
        if (*first == obj)
            break;
        first++;
    }
    return first;
}

// find the iterator and insert before it
template <typename T>
Iterator<T> List<T>::insert(const Iterator<T>& it, T obj)
{
    Node<T>* temp = it.current;
    Node<T>* p = new Node<T>(obj);
    temp->prev->next = p;
    p->prev = temp->prev;
    p->next = temp;
    temp->prev = p;
    ++list_size;
    return it--;
}

// find the first content and delete that node
template <typename T>
Iterator<T> List<T>::remove(const T& obj)
{
    Iterator<T> it = find(begin(), end(), obj);
    if (empty())
        return end();
    else
        if (it == end())
            return end();
        else {
            Node<T>* temp = it.current;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            it++;
            delete temp;
            temp = nullptr;
            --list_size;
        }
    return it;
}

template <typename T>
Iterator<T> List<T>::remove(Iterator<T>& it)
{
    Node<T>* temp = it.current;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    it++;
    delete temp;
    temp = nullptr;
    --list_size;
    return it;
}

template<typename T>
void List<T>::print()
{
    for (Iterator<T> it = this->begin(); it != this->end(); it++) {
        cout << *it << endl;
    }
}
#endif