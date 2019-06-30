#pragma once

#include "engine_Graph.h"
#include <iostream>

template <typename T>
class Node
{
public:
	T *Object;
	Node *Next;
public:
	Node(T &object) :
		Object(&object){};
};

template <typename T>
class List
{
private:
	Node<T> *Head = NULL;
public:
	List();
	bool AddItemtoHead(T &object);
	bool AddItemtoEnd(T &object);
	//bool DeleteItem(T &object);

	template <typename T>
	friend ostream &operator<<(ostream &outstream,const List<T> &list);

	~List();
};

template <typename T>
List<T>::List()
{
	this->Head = NULL;
}

template <typename T>
bool List<T>::AddItemtoHead(T &object)
{
	Node<T> *Item = new Node<T>(object);
	Item->Next = this->Head;
	this->Head = Item;
	return 1;
}

template <typename T>
bool List<T>::AddItemtoEnd(T &object)
{
	Node<T> *Item = new Node<T>(object);
	Item->Next = NULL;
	if(this->Head == NULL)
	{
		this->Head = Item;
		return 1;
	}
	for (Node<T> *pointer = this->Head; pointer != NULL; pointer = pointer->Next)
	{
		if(pointer->Next == NULL)	// is the Last Item
		{
			pointer->Next = Item;
			return 1;
		}
	}
	return 0;
}

/*
template <typename T>
bool List<T>::DeleteItem(T &object)
{
	if(this->Head = NULL)	// List is empty
	{
		return 0;
	}
}
*/

template <typename T>
ostream &operator<<(ostream &outstream, const List<T> &list)
{
	int Count = 0;
	for (Node<T> *pointer = list.Head; pointer != NULL; pointer = pointer->Next)
	{
		std::cout<<"-- ID:"<<Count++<<"\n     | CT:"<<*(pointer->Object)<<endl;
	}
	std::cout<<endl;
	return outstream;
}

template <typename T>
List<T>::~List()
{
	Node<T> *pointer;
	while(this->Head->Next != NULL)
	{
		pointer = this->Head->Next;
		delete this->Head;
		this->Head = pointer;
	}
	delete this->Head;
}
