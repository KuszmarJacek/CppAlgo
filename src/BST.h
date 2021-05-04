#pragma once

#include <iostream>
#include <functional>

template <typename T>
class BST
{
public:
	struct Node
	{
		T data;
		Node* left, * right;
	};

	Node* root = nullptr;

private:
	Node* findHelper(Node* current, T val)
	{
		if(!current)
		{
			return nullptr;
		}
		if(val == current->data)
		{
			return current;
		}
		if(val < current->data)
		{
			return findHelper(current->left, val);
		}
		if(val > current->data)
		{
			return findHelper(current->right, val);
		}
	}

	void insertHelper(Node* current, T val)
	{
		if(val < current->data)
		{
			if(!current->left)
			{
				current->left = new Node{ val, nullptr, nullptr };
			}
			else
			{
				insertHelper(current->left, val);
			}
		}
		else
		{
			if(!current->right)
			{
				current->right = new Node{ val, nullptr, nullptr };
			}
			else
			{
				insertHelper(current->right, val);
			}
		}
	}

	void insertHelper(Node* current, T val, std::function<int(T, T)> comparator)
	{
		//executed if comparator returns anything but 0
		if(comparator(val, current->data))
		{
			if(!current->left)
			{
				current->left = new Node{ val, nullptr, nullptr };
			}
			else
			{
				insertHelper(current->left, val, comparator);
			}
		}
		//executed if comparator returns 0
		else
		{
			if(!current->right)
			{
				current->right = new Node{ val, nullptr, nullptr };
			}
			else
			{
				insertHelper(current->right, val, comparator);
			}
		}
	}

	void inOrderHelper(Node* first, bool out)
	{
		if(!first)
		{
			return;
		}

		inOrderHelper(first->left, out);

		if(out)
		{
			std::cout << first->data << " ";
		}

		inOrderHelper(first->right, out);
	}

	void preOrderHelper(Node* first, bool out)
	{
		if(!first)
		{
			return;
		}

		if(out)
		{
			std::cout << first->data << " ";
		}
		inOrderHelper(first->left, out);
		inOrderHelper(first->right, out);
	}

	Node* findReplacement(Node* first)
	{
		Node* current = first->right;

		while(current && current->left)
		{
			current = current->left;
		}

		return current;
	}

	Node* deleteHelper(Node* first, T val)
	{
		//leaf
		if(!first)
		{
			return nullptr;
		}
		if(val < first->data)
		{
			first->left = deleteHelper(first->left, val);
		}
		else if(val > first->data)
		{
			first->right = deleteHelper(first->right, val);
		}
		else
		{
			//one or none
			if(!first->left)
			{
				Node* tmp = first->right;
				delete first;
				return tmp;
			}
			if(!first->right)
			{
				Node* tmp = first->left;
				delete first;
				return tmp;
			}

			//two 
			Node* replacement = findReplacement(first);
			first->data = replacement->data;

			first->right = deleteHelper(first->right, replacement->data);
		}

		return first;
	}

	void clearHelper(Node* first)
	{
		if(!first)
		{
			return;
		}

		clearHelper(first->left);
		clearHelper(first->right);

		delete first;
	}

	int depth(Node* first)
	{
		if(!first)
		{
			return 0;
		}
		else
		{
			int leftDepth = depth(first->left);
			int rightDepth = depth(first->right);

			if(leftDepth >= rightDepth)
			{
				return leftDepth + 1;
			}
			else
			{
				return rightDepth + 1;
			}
		}
	}

public:
	Node* find(T val)
	{
		return findHelper(root, val);
	}

	void insert(T val)
	{
		if(!root)
		{
			root = new Node{ val, nullptr, nullptr };
		}
		else
		{
			insertHelper(root, val);
		}
	}

	void inOrder(bool out = false)
	{
		inOrderHelper(root, out);
	}

	void deleteVal(T val)
	{
		root = deleteHelper(root, val);
	}

	void clear()
	{
		clearHelper(root);
		//Yikes cringe...
		root = nullptr;
	}

	int depth()
	{
		return depth(root);
	}
};
