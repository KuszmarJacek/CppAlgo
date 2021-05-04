#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>

template<typename T>
class MaxHeap
{
private:
	using Vec = std::vector<T>;

	Vec vec;

	int parent(int index)
	{
		return (index - 1) / 2;
	}

	int leftChild(int index)
	{
		return 2 * index + 1;
	}

	int rightChild(int index)
	{
		return 2 * index + 2;
	}

	void heapUp(int index)
	{
		if(index && vec[parent(index)] < vec[index])
		{
			std::swap(vec[index], vec[parent(index)]);
			heapUp(parent(index));
		}
	}

	void heapDown(int index)
	{
		int left = leftChild(index);
		int right = rightChild(index);
		int biggest = index;

		if(left < vec.size() && vec[left] > vec[index])
		{
			biggest = left;
		}

		if(right < vec.size() && vec[right] > vec[biggest])
		{
			biggest = right;
		}

		if(biggest != index)
		{
			std::swap(vec[index], vec[biggest]);
			heapDown(biggest);
		}
	}

	void heapDown(int index, int size)
	{
		int left = leftChild(index);
		int right = rightChild(index);
		int biggest = index;

		if(left < size && vec[left] > vec[index])
		{
			biggest = left;
		}

		if(right < size && vec[right] > vec[biggest])
		{
			biggest = right;
		}

		if(biggest != index)
		{
			std::swap(vec[index], vec[biggest]);
			heapDown(biggest, size);
		}
	}
public:

	enum FixMethod : bool
	{
		Williams = true,
		Floyd = false
	};

	MaxHeap(std::vector<T>* v, bool fixMethod)
	{
		vec = std::move(*v);
		if(fixMethod)
		{
			williamsFix();
		}
		else
		{
			floydFix();
		}
	}

	//O(n * log(n)) 
	void williamsFix()
	{
		for(int i = 0; i < vec.size(); ++i)
		{
			heapUp(i);
		}
	}

	//O(n)
	void floydFix()
	{
		for(int i = vec.size() - 1 / 2; i >= 0; --i)
		{
			heapDown(i);
		}
	}

	MaxHeap() = default;

	void clear()
	{
		vec.clear();
	}

	void push(T val)
	{
		vec.push_back(val);
		heapUp(vec.size() - 1);
	}

	T removeTop()
	{
		try
		{
			if(vec.empty())
			{
#ifdef DEBUG
				std::cout << "[INFO] vector is empty << std::endl";
#endif

					throw "Empty vec";
			}
		}
		catch(...)
		{
			std::cout << "ow noooo so sad empty vec...";
		}

		T res = vec.front();
		vec.front() = vec.back();
		vec.pop_back();

		heapDown(0);

		return res;
	}

	void print()
	{
		for(T val : vec)
		{
			std::cout << val << std::endl;
		}
		std::cout << std::endl;
	}


	void sort()
	{
		floydFix();

		for(int i = vec.size() - 1; i > 0; --i)
		{
			std::swap(vec.front(), vec.at(i));
			heapDown(0, i);
		}
	}
};

void countingSortNatural(std::vector<int>& a, int nmax)
{
	std::vector<int> c(nmax, 0);
	std::vector<int> b(a.size(), 0);

	for(int i = 0; i < a.size(); ++i)
	{
		c.at(a.at(i) - 1)++;
	}

	for(int i = 1; i < nmax; ++i)
	{
		c.at(i) += c.at(i - 1);
	}

	for(int i = a.size() - 1; i >= 0; --i)
	{
		b.at(c.at(a.at(i) - 1) - 1) = a.at(i);
		c.at(a.at(i) - 1)--;
	}

	a = b;
}

void countingSortInteger(std::vector<int>& a, const int& size, const int& max, const int& min)
{
	std::vector<int> c(max - min + 1, 0);
	std::vector<int> b(size);

	for(int i = 0; i < size; ++i)
	{
		c[a[i] - min]++;
	}

	for(auto it = c.begin() + 1; it != c.end(); ++it)
	{
		*it += *(it - 1);
	}

	for(int i = size - 1; i >= 0; i--)
	{
		b[c[a[i] - min] - 1] = a[i];
		c[a[i] - min]--;
	}

	a = b;
}


template<size_t size>
void bucketSort(double arr[], double max)
{
	std::vector<double> buckets[size];
	double width = max / size;


	for(int i = 0; i < size; ++i)
	{
		int index = arr[i] / width;
		buckets[index].push_back(arr[i]);
	}

	for(auto& bucket : buckets)
	{
		std::sort(bucket.begin(), bucket.end());
	}

	int index = 0;
	for(auto bucket : buckets)
	{
		for(double d : bucket)
		{
			arr[index++] = d;
		}
	}
}

template <typename T, size_t size>
void bucketSort(T arr[], double max, std::function<bool(const T& lhs, const T& rhs)> comparator)
{
	std::vector<T> buckets[size];
	double width = max / size;


	for(int i = 0; i < size; ++i)
	{
		int index = arr[i] / width;
		buckets[index].push_back(arr[i]);
	}

	for(auto& bucket : buckets)
	{
		std::sort(bucket.begin(), bucket.end(), comparator);
	}

	int index = 0;
	for(auto bucket : buckets)
	{
		for(T d : bucket)
		{
			arr[index++] = d;
		}
	}
}
