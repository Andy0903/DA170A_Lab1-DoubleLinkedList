#pragma once
#include <iostream>
#include <assert.h>

//TODO const correctness

template<class T>
class List;

template <class  T>
class Link
{
	Link *next;
	Link *prev;
	friend class List<T>;

public:
	Link() : next(nullptr), prev(nullptr) {}

	virtual ~Link() = default;

	T* Next()
	{
		return static_cast<T*>(next);
	}

	T* Prev()
	{
		return static_cast<T*>(prev);
	}

	T* InsertAfter(T *TToInsert)
	{
		if (next == nullptr)
		{
			next = TToInsert;
		}
		else
		{
			Link *previouslyNext = next;
			next = TToInsert;
			TToInsert->next = previouslyNext;
		}

		assert(next->prev == this && prev->next == this);
		return Next();
	}

	T* InsertBefore(T *TToInsert)
	{
		Link *previousPrev = prev;
		prev = TToInsert;
		TToInsert->next = previousPrev;

		assert(next->prev == this && prev->next == this);
		return Prev();
	}

	T* DeleteAfter()
	{
		Link *toDelete = next;
		next = next->next;
		delete toDelete;
		toDelete = nullptr;
		assert(next->prev == this && prev->next == this);
		return Next();
	}

	bool Invariant()
	{
		if (next != nullptr && next->prev != nullptr)
		{
			return (next->prev == this && prev->next == this);
		}
	}

	template<class Arg>
	//Uses the function "Match" in T.
	T* FindNext(const Arg &searchFor)
	{
		T *current = static_cast<T*>(this);
		if (current->Match(searchFor))
		{
			return current;
		}
		else if (this->next != nullptr)
		{
			this->Next()->FindNext(searchFor);
		}

		return nullptr;
	}

	virtual std::ostream& Print(std::ostream &cout) { return cout; }
};

template<class T>
class List : public Link<T>
{
	std::ostream& Print(std::ostream& cout) override
	{
		//Link<T> *current = static_cast<Link<T>*>(this);
		this->Link<T>::Print(cout);

		if (this->next != nullptr) //this var current vvv
		{
			return this->next->Print(cout);
		}
		else
		{
			this->Link<T>::Print(cout);
		}
	}

public:
	List() = default;

	T* First()
	{
		Link<T> *current = static_cast<Link<T>*>(this);
		while (current->prev != nullptr)
		{
			current = current->prev;
		}
		return static_cast<T*>(current);
	}

	T* Last()
	{
		Link<T> *current = static_cast<Link<T>*>(this);
		while (current->next != nullptr)
		{
			current = current->next;
		}
		return static_cast<T*>(current);
	}

	T* PushFront(T *item)
	{
		T* front = First();
		item->next = front;
		front->prev = item;
		return item;
	}

	T* PopFront()
	{
		T* front = First();
		front->next->prev = nullptr;
		front->next = nullptr;
		return front;
	}

	T* PushBack(T *item)
	{
		T* back = Last();
		back->next = item;
		item->prev = back;
		return item;
	}

	template<class Arg>
	T* FindFirst(const Arg& searchFor) { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream &cout, List &list) { return list.Print(cout); }

	//void Check() {}
};