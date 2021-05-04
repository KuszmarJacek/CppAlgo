#pragma once
#include <iostream>
#include <functional>
#include <chrono>

template<typename T>
class LinkedList
{
private:
public:
	struct Elem
	{
		T data;
		Elem* prev;
		Elem* next;

		Elem(T _data) : data(_data), prev(nullptr), next(nullptr) {}
	};
	unsigned size;

	Elem* head;
	Elem* tail;

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}

	void push_back(T _data)
	{
		Elem* elem = new Elem(_data);

		if(tail != nullptr)
		{
			elem->prev = tail;
			tail = elem;
			elem->prev->next = elem;
		}
		else
		{
			tail = elem;
			head = tail;
		}

		size++;
	}

	void push_front(T _data)
	{
		Elem* elem = new Elem(_data);

		if(head != nullptr)
		{
			elem->next = head;
			head = elem;
			elem->next->prev = elem;
		}
		else
		{
			head = elem;
			tail = head;
		}

		size++;
	}

	void pop_back()
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;

		size--;
	}

	void pop_front()
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;

		size--;
	}

	T elem_at(int index)
	{
		Elem* elem = head;

		for(int i = 0; i < index && elem != nullptr; ++i)
		{
			elem = elem->next;
		}

		if(elem == nullptr)
		{
			std::cerr << "Index is out of bounds";
			std::exit(EXIT_FAILURE);
		}

		return elem->data;
	}

	T& operator[] (unsigned index)
	{
		Elem* tmp = head;

		for(int i = 0; i < index && tmp != nullptr; ++i)
		{
			tmp = tmp->next;
		}

		if(tmp == nullptr)
		{
			std::cerr << "Index is out of bounds";
			std::exit(EXIT_FAILURE);
		}

		return tmp->data;
	};

	void erase()
	{
		while(head != tail)
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		delete tail;
		head = nullptr;
		tail = nullptr;

		size = 0;
	}

	//User doesnt need the element he should only have access to getting the value at element
	Elem* fetch_match(T _val) const
	{
		Elem* tmp = head;

		while(tmp != nullptr)
		{
			if(tmp->data == _val)
			{
				return tmp;
			}
			tmp = tmp->next;
		}

		return nullptr;
	}

	bool remove_match(T _val)
	{
		if(head->data == _val)
		{
			pop_front();
			return true;
		}
		else if(tail->data == _val)
		{
			pop_back();
			return true;
		}

		Elem* tmp = head->next;

		while(tmp != tail)
		{
			if(tmp->data == _val)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;

				delete tmp;
				tmp = nullptr;

				size--;

				return true;
			}
			tmp = tmp->next;
		}

		return false;
	}

	void ordered_insert(T _val)
	{
		Elem* tmp = head;

		while(tmp->data < _val && tmp != nullptr)
		{
			tmp = tmp->next;
		}

		if(tmp == nullptr || tmp->data == _val)
		{
			return;
		}

		Elem* newElem = new Elem(_val);
		newElem->prev = tmp->prev;
		newElem->next = tmp;
		newElem->prev->next = newElem;
		newElem->next->prev = newElem;

		size++;
	}

	//Must ensure that tmp points to an element with value higher than _val
	void ordered_insert(T _val, std::function<bool(T& lhs, T& rhs)> comparator)
	{
		Elem* tmp = head;

		while(comparator(tmp->data, _val) && tmp != nullptr)
		{
			tmp = tmp->next;
		}

		if(tmp == nullptr)
		{
			return;
		}

		Elem* newElem = new Elem(_val);
		newElem->prev = tmp->prev;
		newElem->next = tmp;
		newElem->prev->next = newElem;
		newElem->next->prev = newElem;

		size++;
	}

	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
	{
		LinkedList<T>::Elem* tmp = list.head;
		while(tmp != nullptr)
		{
			os << tmp->data;
			tmp = tmp->next;
		}

		return os;
	}
};

