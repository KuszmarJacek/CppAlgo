#pragma once

#include <iostream>
#include <stack>
#include <assert.h>
#include <functional>

template<typename T>
class RBT
{
public:
	enum Color { black, red };

	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		Color color;
		T val;
	};
private:
	Node* root = nullptr;

	Node* parent(Node* n)
	{
		if(n == nullptr)
		{
			return nullptr;
		}

		return n->parent;
	}

	Node* grandParent(Node* n)
	{
		return parent(parent(n));
	}

	Node* sibling(Node* n)
	{
		Node* p = parent(n);

		if(p == nullptr)
		{
			return nullptr;
		}

		if(n == p->left)
		{
			return p->right;
		}
		else
		{
			return p->left;
		}
	}

	Node* uncle(Node* n)
	{
		Node* p = parent(n);

		return sibling(p);
	}

	void rotLeft(Node* n)
	{
		Node* nnew = n->right;
		Node* p = parent(n);

		n->right = nnew->left;
		nnew->left = n;
		n->parent = nnew;

		if(n->right != nullptr)
		{
			n->right->parent = n;
		}

		if(p != nullptr)
		{
			if(n == p->left)
			{
				p->left = nnew;
			}
			else if(n == p->right)
			{
				p->right = nnew;
			}
		}
		nnew->parent = p;
	}

	void rotRight(Node* n)
	{
		Node* nnew = n->left;
		Node* p = parent(n);
		assert(nnew != nullptr);  // Since the leaves of a red-black tree are empty,
								  // they cannot become internal nodes.

		n->left = nnew->right;
		nnew->right = n;
		n->parent = nnew;

		if(n->left != nullptr)
		{
			n->left->parent = n;
		}

		if(p != nullptr)
		{
			if(n == p->left)
			{
				p->left = nnew;
			}
			else if(n == p->right)
			{
				p->right = nnew;
			}
		}
		nnew->parent = p;
	}

	void insertHelper(Node* root, Node* n)
	{
		if(root != nullptr)
		{
			if(n->val < root->val)
			{
				if(root->left != nullptr)
				{
					insertHelper(root->left, n);
					return;
				}
				else
				{
					root->left = n;
				}
			}
			else
			{
				if(root->right != nullptr)
				{
					insertHelper(root->right, n);
					return;
				}
				else
				{
					root->right = n;
				}
			}
		}

		n->parent = root;
		n->left = nullptr;
		n->right = nullptr;
		n->color = red;
	}

	//For less than comparator returns 1
	void insertHelper(Node* root, Node* n, std::function<int(T, T)> comparator)
	{
		if(root != nullptr)
		{
			if(comparator(n->val, root->val))
			{
				if(root->left != nullptr)
				{
					insertHelper(root->left, n, comparator);
					return;
				}
				else
				{
					root->left = n;
				}
			}
			else
			{
				if(root->right != nullptr)
				{
					insertHelper(root->right, n, comparator);
					return;
				}
				else
				{
					root->right = n;
				}
			}
		}

		n->parent = root;
		n->left = nullptr;
		n->right = nullptr;
		n->color = red;
	}

	void repairTree(Node* n)
	{
		if(parent(n) == nullptr)
		{
			n->color = black;
		}
		else if(parent(n)->color == black)
		{
			return;
		}
		else if(uncle(n) != nullptr && uncle(n)->color == red)
		{
			parent(n)->color = black;
			uncle(n)->color = black;
			grandParent(n)->color = red;
			repairTree(grandParent(n));
		}
		else
		{
			Node* p = parent(n);
			Node* g = grandParent(n);

			if(n == p->right && p == g->left)
			{
				rotLeft(p);
				n = n->left;
			}
			else if(n == p->left && p == g->right)
			{
				rotRight(p);
				n = n->right;
			}

			p = parent(n);
			g = grandParent(n);

			if(n == p->left)
			{
				rotRight(g);
			}
			else
			{
				rotLeft(g);
			}

			p->color = black;
			g->color = red;
		}
	}

	void inOrderHelper(Node* start)
	{
		if(!start)
		{
			return;
		}

		inOrderHelper(start->left);
		std::cout << start->val << " ";
		inOrderHelper(start->right);
	}

	void preOrderHelper(Node* start)
	{
		if(!start)
		{
			return;
		}

		std::cout << start->val << " ";
		preOrderHelper(start->left);
		preOrderHelper(start->right);
	}

	void printHelper(Node* start)
	{
		if(!start)
		{
			return;
		}

		std::cout << start->val << "." << start->color << "\n";
		printHelper(start->left);
		printHelper(start->right);
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

	Node* findHelper(Node* current, T val)
	{
		if(!current)
		{
			return nullptr;
		}
		if(val == current->val)
		{
			return current;
		}
		if(val < current->val)
		{
			return findHelper(current->left, val);
		}
		if(val > current->val)
		{
			return findHelper(current->right, val);
		}
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
	void insert(T val)
	{
		Node* n = new Node{ nullptr, nullptr, nullptr, red, val };

		insertHelper(root, n);
		repairTree(n);

		root = n;
		while(parent(root) != nullptr)
		{
			root = parent(root);
		}
	}

	void insert(T val, std::function<int(T, T)> comparator)
	{
		Node* n = new Node{ nullptr, nullptr, nullptr, red, val };

		insertHelper(root, n, std::forward<std::function<int(T, T)> >(comparator));
		repairTree(n);

		root = n;
		while(parent(root) != nullptr)
		{
			root = parent(root);
		}
	}

	void inOrder()
	{
		inOrderHelper(root);
	}

	void preOrder()
	{
		preOrderHelper(root);
	}

	void print()
	{
		printHelper(root);
		std::cout << depth(root);
	}

	void clear()
	{
		clearHelper(root);
		root = nullptr;
	}

	Node* find(T val)
	{
		return findHelper(root, val);
	}

	int depth()
	{
		return depth(root);
	}
};
