#pragma once
#include <iostream>
#include <assert.h>

//const correctness & Link<T>

template<class T>
class List;

template <class  T>
class Link
{
	Link *next;
	Link *prev; //Link<T>
	friend class List<T>;

public:
	Link() : next(nullptr), prev(nullptr) {}
	virtual ~Link() = default;

	T* Next() { return static_cast<T*>(next); }
	T* Prev() { return static_cast<T*>(prev); }

	const T* Next() const { return static_cast<const T*>(next); }
	const T* Prev() const { return static_cast<const T*>(prev); }

	T* InsertAfter(T *TToInsert)
	{
		if (next != nullptr)
		{
			next->prev = TToInsert;
			TToInsert->next = next;
		}

		next = TToInsert;
		TToInsert->prev = this;

		assert(Invariant());
		return Next();
	}

	T* InsertBefore(T *TToInsert)
	{
		if (prev != nullptr)
		{
			prev->next = TToInsert;
			TToInsert->prev = prev;
		}

		prev = TToInsert;
		TToInsert->next = this;

		assert(Invariant());
		return Prev();
	}

	T* DeleteAfter()
	{
		T *toDelete = Next();

		if (toDelete == nullptr)
		{
			return nullptr;
		}

		next = next->next;

		if (next != nullptr)
		{
			next->prev = this;
		}

		toDelete->next = nullptr;
		toDelete->prev = nullptr;
		assert(Invariant());
		return toDelete;
	}

	virtual bool Invariant() const
	{
		return (next == nullptr || next->prev == this) && (prev == nullptr || prev->next == this);
	}

	template<class Arg>
	//Uses the function "Match" in T.
	const T* FindNext(const Arg &searchFor) const
	{
		if (next != nullptr)
		{
			if (Next()->Match(searchFor))
			{
				return Next();
			}
			return Next()->FindNext(searchFor);
		}

		return nullptr;
	}

	template<class Arg>
	//Uses the function "Match" in T.
	T* FindNext(const Arg &searchFor)
	{
		if (next != nullptr)
		{
			if (Next()->Match(searchFor))
			{
				return Next();
			}
			return Next()->FindNext(searchFor);
		}

		return nullptr;
	}

	virtual std::ostream& Print(std::ostream &cout) const
	{
		return cout;
	}
};

template<class T>
class List : public Link<T>
{
	std::ostream& Print(std::ostream& cout) const override
	{
		Link<T> *current = next;
		while (current != nullptr && current != this)
		{
			T *currentNode = static_cast<T*>(current);
			currentNode->Print(cout);
			current = current->next;
		}

		return cout;
	}

public:
	List() = default;
	~List()
	{
		T *toDelete = PopFront();
		while (toDelete != nullptr)
		{
			delete toDelete;
			toDelete = PopFront();
		}
	}

	T* First() { return Next(); }
	T* Last() { return Prev(); }

	const T* First() const { return Next(); }
	const T* Last() const { return Prev(); }

	T* PushFront(T *item)
	{
		if (next != nullptr)
		{
			next->prev = item;
			item->next = next;
		}

		if (prev == nullptr)
		{
			prev = item;
		}

		next = item;

		assert(Invariant());
		return item;
	}

	T* PopFront()
	{
		return DeleteAfter();
	}

	T* PushBack(T *item)
	{
		if (prev != nullptr)
		{
			prev->next = item;
			item->prev = prev;
		}

		if (next == nullptr)
		{
			next = item;
		}

		prev = item;

		assert(Invariant());
		return item;
	}

	bool Invariant() const override
	{
		Link<T> *current = next;
		while (current != nullptr)
		{
			if (!current->Invariant())
			{
				return false;
			}
			current = current->next;
		}

		return true;
	}

	template<class Arg>
	const T* FindFirst(const Arg& searchFor) const
	{
		return FindNext(searchFor);
	}

	template<class Arg>
	T* FindFirst(const Arg& searchFor)
	{
		return FindNext(searchFor);
	}

	friend std::ostream& operator<<(std::ostream &cout, List &list)
	{
		return list.Print(cout);
	}
};