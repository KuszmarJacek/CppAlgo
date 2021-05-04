#pragma once
#include <cstdint>
#include <string>
#include <cassert>
#include <iostream>
#include <utility>
#include <string>
#include <stdexcept>
#include <list>
#include <vector>
#define assertm(exp, msg) assert((msg, exp))

template<typename ArrayList>
class ArrayListIterator
{
public:
	using ValType = typename ArrayList::ValType;
	using PtrType = ValType*;
	using RefType = ValType&;

private:
	PtrType ptr;

public:
	ArrayListIterator(PtrType ptr)
		: ptr{ ptr }
	{}

	ArrayListIterator& operator++()
	{
		ptr++;
		return *this;
	}

	ArrayListIterator operator++(int)
	{
		ArrayListIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ArrayListIterator& operator--()
	{
		ptr--;
		return *this;
	}

	ArrayListIterator operator--(int)
	{
		ArrayListIterator iterator = *this;
		--(*this);
		return iterator;
	}

	RefType operator[](int index)
	{
		return *(ptr + index);
	}

	PtrType operator->()
	{
		return ptr;
	}

	RefType operator*()
	{
		return *ptr;
	}

	bool operator==(const ArrayListIterator& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const ArrayListIterator& other) const
	{
		return !(*this == other);
	}
};

template <typename T>
class ArrayList
{
public:
	using ValType = T;
	using Iterator = ArrayListIterator<ArrayList<T>>;

private:
	T* data;
	size_t size;
	size_t sizeCap;
	const int8_t growthFactor;

	void resize(size_t newSizeCap)
	{
		//Use new and delete expressions
		T* newData = (T*)::operator new(newSizeCap * sizeof(T));

		if(newSizeCap < size)
		{
			size = newSizeCap;
		}

#pragma warning( disable : 6385 )
		for(size_t i = 0; i < size; ++i)
		{
			newData[i] = std::move(data[i]);
		}
#pragma warning( default : 6385 )

		for(size_t i = 0; i < size; ++i)
		{
			data[i].~T();
		}

		::operator delete(data, sizeCap * sizeof(T));
		data = newData;
		sizeCap = newSizeCap;
	}

public:
	ArrayList()
		: data{ nullptr }
		, size{ 0 }
		, sizeCap{ 0 }
		, growthFactor{ 2 }
	{
		resize(10);
	}

	~ArrayList()
	{
		clear();
		::operator delete(data, sizeCap * sizeof(T));
	}

	size_t getSize() const
	{
		return size;
	}

	Iterator begin()
	{
		return Iterator(data);
	}

	Iterator end()
	{
		return Iterator(data + size);
	}

	const T& operator[](size_t index) const
	{
		assertm(index < size, "Index out of bounds");
		if(index > size)
		{
			throw std::out_of_range("Index out of bounds");
		}
		return data[index];
	}

	T& operator[](size_t index)
	{
		assertm(index < size, "Index out of bounds");
		if(index > size)
		{
			throw std::out_of_range("Index out of bounds");
		}
		return data[index];
	}

	template<typename ...Args>
	T& emplaceBack(Args&&... args)
	{
		if(size >= sizeCap)
		{
			resize(growthFactor * sizeCap);
		}

		new(&data[size]) T(std::forward<Args>(args)...);
		return data[size++];
	}

	void clear()
	{
		for(size_t i = 0; i < size; ++i)
		{
			data[i].~T();
		}

		size = 0;
	}

	void sort()
	{
		for(int i = 0; i < size; ++i)
		{
			bool swapped = false;
			for(int j = 0; j < size - i - 1; ++j)
			{
				if(data[j] > data[j + 1])
				{
					std::swap(data[j], data[j + 1]);
					swapped = true;
				}
			}

			if(!swapped)
			{
				return;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& out, ArrayList<T>& al)
	{
		for(auto& val : al)
		{
			out << val << '\n';
		}

		return out;
	}
};

