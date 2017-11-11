#pragma once
#include <iostream>
#include <assert.h>

//TODO const correctness

//template<class T>
//class List;

template <class  T>
class Link
{
	Link *next;
	Link *prev;
	friend class Link<T>;

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
		return (next->prev == this && prev->next == this);
	}

	template<class Arg>
	//FindNext use the function Match in the T class to see if it is a hit.
	T* FindNext(const Arg &searchFor)
	{
		T *current = static_cast<T*>(this);
		if (current->Match(searchFor))
		{
			return current;
		}
		else if (this->next != nullptr)
		{
			this->FindNext(searchFor);
		}

		return nullptr;
	}

	virtual std::ostream& Print(std::ostream &cout) { return cout; }
};

template<class T>
class List : public Link<T>
{
	std::ostream& Print(std::ostream& cout)
	{
	}

public:
	List()
	{
	}

	T* First()
	{
	}

	T* Last()
	{
	}

	T* PushFront(T *item)
	{
	}

	T* PopFront()
	{
	}

	T* PushBack(T *item)
	{
	}

	template<class Arg>
	T* FindFirst(const Arg& searchFor) { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream &cout, List &list) { return list.Print(cout); }

	void Check()
	{
	}
};