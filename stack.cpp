#include "node.h"
#include "stack.h"
#include <iostream>

template <class T>
Stack<T>::Stack()
{
    len = 0;
	cap = 0;
	array = new T[len];
}

template <class T>
Stack<T>::~Stack()
{
	delete[] array;
}

template <class T>
void Stack<T>::push(T it)
{
	T* new_array = new T[len + 1];
	for (int i = 0; i < len; ++i)
	{
		new_array[i] = array[i]; 
	}
	new_array[len] = it;
	delete[] array;
	array = new_array;
    len++;
	cap++;
}

template <class T>
T& Stack<T>::top()
{
    return array[len - 1];
}

// template <class T>
// T Stack<T>::top_ptr()
// {
// 	cap--;
//     return array[len - 1];
// }

// template <class T>
// T Stack<T>::top()
// {
// 	delete[] array[cap - 1];
// 	cap--;
// }

template <class T>
T& Stack<T>::pop(int num)
{
	T& ans = top();
	if (len - num >= 0)
	{
		len -= num;
	}
	return ans;
}

template <class T>
bool Stack<T>::empty()
{
    if (len == 0)
    {
        return true;
    }
    return false;
}

template <class T>
int Stack<T>::size()
{
    return len;
}

template <class T>
int Stack<T>::capacity()
{
    return cap;
}

template <class T>
void Stack<T>::print()
{
	// for (int i = len - 1; i >= 0; i--)
	// {
	// 	std::cout << array[i] << " ";
	// }
	std::cout << "\n";
}

template <class T>
T& Stack<T>::get(int index)
{
	if (index < len)
	{
		return array[index];
	}
}

template class Stack<int>;
template class Stack<Node*>;
template class Stack<Rule*>;
template class Stack<char*>;
