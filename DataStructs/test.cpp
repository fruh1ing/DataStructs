#pragma once
//#include "bstree.hpp"
#include "rbtree.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace datastruct;


//void test1()
//{
//	bstree tree;
//	vector<int> vint{ 12,5,18,2,9,15,19,13,17 };
//	vector<tree_node*> nodes;
//	for (int i : vint)
//	{
//		tree_node* node = new tree_node(i);
//		nodes.push_back(node);
//		cout << node->key_ << endl;
//		tree_insert(&tree, node);
//	}
//
//	inorder(tree.root);
//	inorder_stack(tree.root);
//
//	for (tree_node* i : nodes)
//	{
//		delete i;
//	}
//}

void test2()
{
	rbtree tree;
	vector<int> vint{ 12,5,18,2,9,15,19,13,17 };
	vector<rbtree_node*> nodes;
	for (int i : vint)
	{
		rbtree_node* node = new rbtree_node(rbtree_node::color::red, i);
		nodes.push_back(node);
		cout << node->key << endl;
		tree.insert(node);
	}
	tree.inorder();
	for (rbtree_node* i : nodes)
	{
		delete i;
	}
}

int main()
{
	test2();
	return 0;
}
