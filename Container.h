#pragma once
#include<stddef.h>
#include<string>


template <class T> class Container
{
private:
	struct Element
	{
		Element* next;
		Element* previous;
		T value;
	};
	Element* head;
	Element* last_el;
	Element* iter;

public:
	Container() {};

	Container(Container container) :
		head(NULL),
		last_el(NULL)
	{
		for (auto e = container.head; NULL != e; e = e->next) {
			AddFirst(e->value);
		}
	}

	void AddFirst(const T& data)
	{
		Element* to_add = new Element();
		to_add->value = data;
		to_add->next = head;
		to_add->previous = NULL;
		head = to_add;
		if (head == NULL)
		{
			last_el = to_add;
		}
	}

	void AddLast(const T& data)
	{
		if (head != NULL)
		{
			Element *to_add = new Element();
			last_el->next = to_add;
			to_add->content = data;
			to_add->next = NULL;
			to_add->previous = last_el;
			last_el = to_add;
		}
		else this->AddFirst(data);
	}

	void DeleteFirst()
	{
		if (head == NULL)
			return;
		else
		{
			Element* pointer = head;
			head = head->next;
			head->previous = NULL;
			delete pointer;
		}
	}

	void DeleteLast()
	{
		if (head == NULL)
			return;
		if (head->next == NULL)
		{
			delete head;
			head = NULL;
		}
		else
		{
			Element* pointer = last_el;
			last_el = last_el->previous;
			last_el->next = NULL;
			delete pointer;
		}
	}

	T GetFirst()
	{
		return head->value;
	}

	T GetLast()
	{
		return last_el->value;
	}

	void MoveToFirst()
	{
		iter = head;
	}

	T GoOver()
	{
		if (iter->next != NULL)
		{
			iter = iter->next;
			return &iter->value;
		}
		else
			return NULL;
	}

	bool IsEmpty()
	{
		if (this->head == NULL)
			return true;
		else
			return false;
	}

	int Count()
	{
		if (IsEmpty())
			return 0;
		else
		{
			Element* counter = head;
			int i = 1;
			while (counter->next)
			{
				i++;
				counter = counter->next;
			}
			return i;
		}
	}

	void ExeptionCheck()
	{
		if (this->IsEmpty())
		{
			throw noexcept("EmptinessExeption");
		}
	}
	void ExeptionCheck(Element* el)
	{
		if (el == NULL)
		{
			throw noexcept("OutOfRangeExeption");
		}
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			this->DeleteFirst();
		}
	}
};
