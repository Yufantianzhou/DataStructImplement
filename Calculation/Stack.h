#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>

template<class T>
class Stack {   //栈类
private:
	struct Node {
		T data;
	    Node* next;
		Node() { next = nullptr; };
		Node(T c_data) { data = c_data; next = nullptr; };
	};
	Node* top;
	int len;
public:
	Stack();
	~Stack();
	bool Clear();  //清空栈
	bool Empty();  //判断栈是否为空，为空返回true
	bool GetTop(T& elem) const;   //获取栈顶元素，若栈为空则返回false
	T GetTop()const;  //在已经确定栈不为空的前提下直接返回栈顶元素
	bool Push(const T elem); //将elem入栈，len+1；
	T Pop();  //在已经确定栈不为空的前提下出栈
	bool Pop(T& elem);   //出栈
	int Len()const; //返回栈的长度
	bool PrintStack(); //从栈顶开始，打印栈中的内容
};

template<class T>
Stack<T>::Stack() {
	top = nullptr;
	len = 0;
}

template<class T>
Stack<T>::~Stack() {
	Node* p = top;
	while (top != nullptr) {
		top = top->next;
		delete p;
		p = top;
	}
	top = nullptr;
}

template<class T>
bool Stack<T>::Clear() {
	if (top == nullptr)
		return true;

	Node* p = top;
	while (top != nullptr) {
		delete p;
		top = top->next;
		p = top;
	}
	len = 0;
	top = nullptr;
	return true;
}

template<class T>
bool Stack<T>::Empty() {
	if (top == nullptr)
		return true;
	else
		return false;
}

template<class T>
bool Stack<T>::GetTop(T& elem) const{
	if (top != nullptr) {
		elem = top->data;
		return true;
	}
	return false;
}

template<class T>
T Stack<T>::GetTop()const {
	return top->data;
}

template<class T>
bool Stack<T>::Push(const T elem) {
	Node* newNodePtr = new Node(elem);
	if (top != nullptr)
		newNodePtr->next = top;
	top = newNodePtr;
	len++;
	return true;
}

template<class T>
T Stack<T>::Pop() {
	T elem=top->data;
	Node* p = top;
	top = top->next;
	delete p;
	len--;
	return elem;
}

template<class T>
bool Stack<T>::Pop(T& elem) {
	if (top == nullptr) {
		return false;
	}
	elem = top->data;
	Node* p = top;
	top = top->next;
	delete p;
	len -= 1;
	return true;
}

template<class T>
int Stack<T>::Len()const {
	return len;
}

template <class T>
bool Stack<T>::PrintStack() {
	Node* p = top;
	if (p == nullptr)
		return false;

	while (p != nullptr) {
		std::cout << p->data << ' ';
		p = p->next;
	}
	std::cout << std::endl;
	return true;
}

#endif