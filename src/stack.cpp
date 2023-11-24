#include <iostream>
#include <stdexcept>

#include "raylib/raylib.h"
#include "tower.h"

template <typename T>
Stack<T>::Stack(int cap)
{
    stack = new T[cap];
    this->cap = cap;
    length = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] stack;
}

template <typename T>
void Stack<T>::push(T object)
{
    if(isFull())
        throw std::invalid_argument("Stack full!");

    stack[length++] = object;
}

template <typename T>
T Stack<T>::pop()
{
    if(isEmpty())
        throw std::invalid_argument("Stack empty!");

    return stack[--length];
}

template <typename T>
T Stack<T>::remove(int index)
{
    T output = stack[index];

    T *temp = new T[cap];
    for(int i = 0; i < index; i++)
        temp[i] = stack[i];
    for(int i = index; i < length - 1; i++)
        temp[i] = stack[i + 1];
    length--;
    delete[] stack;
    stack = temp;
    return output;
}

template <typename T>
T Stack<T>::top()
{
    return stack[length - 1];
}

template <typename T>
T Stack<T>::get(int index)
{
    if(index < 0 || index >= length)
        throw std::invalid_argument("Index out of range!");

    return stack[index];
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return length <= 0;
}

template <typename T>
bool Stack<T>::isFull()
{
    return length >= cap;
}

template <typename T>
int Stack<T>::getLength()
{
    return length;
}

template <typename T>
int Stack<T>::getCapacity()
{
    return cap;
}

template class Stack<Disk*>;