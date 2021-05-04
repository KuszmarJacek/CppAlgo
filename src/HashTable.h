#pragma once

#include <string>
#include <list>
#include <vector>
#include <iostream>

#define DEBUG

template <typename T>
class HashTable
{
public:
	using Pair = std::pair<std::string, T>;
	using List = std::list<Pair>;
	using Vec = std::vector<List>;

	size_t pairCnt{ 0 };
	Vec vec{ 16 };

	int hash(std::string key)
	{
		unsigned long long int sum = 0;

		for(int i = 0; i < key.length(); i++)
		{
			sum += key[i] * pow(31, key.length() - i - 1);
		}

		return sum % vec.size();
	}

	//Do the rehash
	void insert(std::string key, T val)
	{
		if((double)pairCnt / (double)vec.size() >= 0.75)
		{
			rehash();
#ifdef DEBUG
			std::cout << "[INFO] Rehashing at \"" << pairCnt << "\" elements" << std::endl;
#endif
		}

		int index = hash(key);
		bool hasKey = false;
		auto& listAtIndex = vec[index];

		for(auto it = begin(listAtIndex); it != end(listAtIndex); it++)
		{
			if(it->first == key)
			{
				hasKey = true;
				it->second = val;

#ifdef DEBUG
				std::cout << "[INFO] Replaced at index: \"" << index << "\"" << std::endl;
#endif 

				break;
			}
		}

		if(!hasKey)
		{
			listAtIndex.emplace_back(key, val);

#ifdef DEBUG
			std::cout << "[INFO] Inserted pair: ( " << key << " ; " << val << " )" << " at index: \"" << index << "\"" << std::endl;;
#endif

			pairCnt++;
		}

		return;
	}

	bool remove(std::string key)
	{
		int index = hash(key);
		bool hasKey = false;
		auto& listAtIndex = vec[index];

		for(auto it = begin(listAtIndex); it != end(listAtIndex); it++)
		{
			if(it->first == key)
			{
				hasKey = true;
				//erase return an iterator to the next item
				it = listAtIndex.erase(it);
#ifdef DEBUG
				std::cout << "[INFO] Removing at index: \"" << index << "\"" << std::endl;
#endif 

				pairCnt--;
				return true;
			}
		}

		if(!hasKey)
		{
#ifdef DEBUG
			std::cout << "[INFO] Element with key: \"" << key << "\" wasn't removed, doesn't exist" << std::endl;
#endif 

			return false;
		}
	}

	void print()
	{
		for(auto& list : vec)
		{
			if(list.empty())
			{
				continue;
			}

			for(auto& pair : list)
			{
				std::cout << "key: \"" << pair.first << "\" val: \"" << pair.second << "\"" << std::endl;
			}
		}
	}

	Pair* search(std::string key)
	{
		int index = hash(key);
		auto& listAtIndex = vec[index];

		//O(1) for cases without conflict 
		for(auto& pair : listAtIndex)
		{
			if(pair.first == key)
			{
				return &pair;
			}
		}

		return nullptr;
	}

	void clean()
	{
		pairCnt = 0;
		vec.clear();
		vec.resize(10);
		vec.shrink_to_fit();
	}

	void rehash()
	{
		Vec newVec{ 2 * vec.size() };
		int index = 0;

		for(auto& list : vec)
		{
			if(list.empty())
			{
				continue;
			}

			for(auto& pair : list)
			{
				index = hash(pair.first);
				newVec[index].emplace_back(pair.first, pair.second);
			}
		}

		vec = std::move(newVec);
	}
};
