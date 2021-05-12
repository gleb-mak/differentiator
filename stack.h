#pragma once

template <class T>
class Stack
{
public:
    Stack();
	~Stack();
    void push(T it);
    T& top();
    T& pop(int num = 1);
    bool empty();
    int size();
	int capacity();
	void print();
	T& get(int index);
private:
    T* array;
    int len;
	int cap;
};


