#include <iostream>
#include <algorithm>

class Node
{
public:
	int val;
	Node *next;
	Node *prev;

    Node(int key = 0, Node *nxt = nullptr, Node *prv = nullptr) : val(key), next(nxt), prev(prv) {}
};
 
class CustomList
{
public:
	Node *head;
	Node *tail;
	Node *middle;
	int size;

    CustomList(Node * key_head = nullptr, Node * key_tail = nullptr, Node * key_middle = nullptr,int key_size = 0)
    : head(key_head), tail(key_tail), middle(key_middle), size(key_size) {}
};
 
void * pop_front(CustomList *root)
{
	if (root -> tail != nullptr) 
	{
		root -> tail = root -> tail -> prev;
	}
	if (root -> tail == nullptr)
	{
		root -> head = nullptr;
		root -> middle = nullptr;
	}
	else
	{
		root -> tail -> next = nullptr;
		if ((root -> size) % 2 == 1)
		{
			root -> middle = root -> middle -> prev;
		}
	}
	root -> size--;
	return root;
}
 
void * push_back(CustomList *root, int x)
{
	if (root -> head == nullptr) 
	{
		root -> head = new Node(x);
		root -> tail = root -> head;
		root -> middle = root -> head;
	}
	else 
	{
		Node *new_head = new Node(x, root -> head, nullptr);
		root -> head = new_head;
		root -> head -> next -> prev = root -> head;
		if ((root -> size) % 2 == 1)
		{
			root -> middle = root -> middle -> prev;
		}
	}
	root -> size++;
	return root;
};
 
void * push_middle(CustomList *root, int x)
{
	if (root -> middle == nullptr) 
	{
		root -> middle = new Node(x);
		root -> tail = root -> middle;
		root -> head = root -> middle;
	}
	else 
	{
		Node *new_middle;
		if ((root -> size) % 2 == 1)
		{
			new_middle = new Node(x, root -> middle, root -> middle -> prev);
		}
		else
		{
			new_middle = new Node(x, root -> middle -> next, root -> middle);
		}
		root -> middle = new_middle;
		if (root -> middle -> next != nullptr)
		{
			root -> middle -> next -> prev = root -> middle;
		}
		else
		{
			root -> tail = root -> middle;
		}
		if (root -> middle -> prev != nullptr)
		{
			root -> middle -> prev -> next = root -> middle;
		}
		else
		{
			root -> head = root -> middle;
		}
	}
	root -> size++;
	return root;
};
 
void print_straight(Node *root)
{
	if (root == nullptr) 
	{
		std::cout << std::endl;
		return;
	}
	else
	{
		std::cout << root -> val << " ";
		print_straight(root -> next); 
	}
}
 
int main() {
	int n;
	std::cin >> n;
	auto * lst = new CustomList();
    char b;
    int a;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> b;
		switch(b)
		{
			case '+':
				std::cin >> a;
				push_back(lst, a);
			    break;
			case '*':
				std::cin >> a;
				push_middle(lst, a);
			    break;
			case '-':
				std::cout << lst -> tail -> val << std::endl;
				pop_front(lst);
			    break;
		}
	}
	return 0;
}