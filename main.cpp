#include <iostream>
#include "Skiplist.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <queue>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

struct node
{
	int key_value;
	node *left;
	node *right;
};

class btree
{
public:
	btree();
	~btree() {
		destroy_tree();
	}

	void insert(int key);
	node *search(int key);
	void destroy_tree();

private:
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);

	node *root;
};

btree::btree()
{
	root = NULL;
}

void btree::destroy_tree(node *leaf)
{
	if (leaf != NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node *leaf)
{
	if (key< leaf->key_value)
	{
		if (leaf->left != NULL)
			insert(key, leaf->left);
		else
		{
			leaf->left = new node;
			leaf->left->key_value = key;
			leaf->left->left = NULL;    //Sets the left child of the child node to null
			leaf->left->right = NULL;   //Sets the right child of the child node to null
		}
	}
	else if (key >= leaf->key_value)
	{
		if (leaf->right != NULL)
			insert(key, leaf->right);
		else
		{
			leaf->right = new node;
			leaf->right->key_value = key;
			leaf->right->left = NULL;  //Sets the left child of the child node to null
			leaf->right->right = NULL; //Sets the right child of the child node to null
		}
	}
}

node *btree::search(int key, node *leaf)
{
	if (leaf != NULL)
	{
		if (key == leaf->key_value)
			return leaf;
		if (key<leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}

void btree::insert(int key)
{
	if (root != NULL)
		insert(key, root);
	else
	{
		root = new node;
		root->key_value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

node *btree::search(int key)
{
	return search(key, root);
}

void btree::destroy_tree()
{
	destroy_tree(root);
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{

	Skiplist<int> tmp(50,0.65);
	btree tree;

	clock_t begin;
	int SIZE = 1000000;
	
	//SIZE = 15;

	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		tmp.insert(rand()%SIZE);
	}
	
	if (SIZE <= 15) {
		tmp.insert(5);
		tmp.search(5);
		tmp.print();
		printf("Press ENTER to leave...\n");
		getchar();
		return 0;
	}

	cout << "Building..." << endl;
	cout << "Running time in seconds: \t" << double(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;


	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		tmp.search(rand()%SIZE);
	}
	cout << "Searching..." << endl;
	cout << "Running time in seconds: \t" << double(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;

	
	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		tmp.remove(rand()%SIZE);
	}
	cout << "Removing..." << endl;
	cout << "Running time in seconds: \t" << double(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;
	

	cout << endl;

	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		tree.insert(rand()%SIZE);
	}
	cout << "Tree insert..." << endl;
	cout << "Running time in seconds: \t" << double(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;

	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		tree.search(rand()%SIZE);
	}
	cout << "Tree search..." << endl;
	cout << "Running time in seconds: \t" << double(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;

	cout << endl;
	return 0;
}