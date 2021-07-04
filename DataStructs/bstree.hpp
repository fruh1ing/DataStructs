#pragma once
#include <stack>
#include <iostream>
#include <utility>
using std::stack;
using std::cout;
using std::endl;
using std::pair;

namespace datastruct {

	struct tree_node
	{
		typedef tree_node* node_ptr;
		node_ptr parent_, left_, right_;
		int key_;
		int value_;
		tree_node(int k, int v) :key_(k), value_(v), parent_(nullptr), left_(nullptr), right_(nullptr) {}
		tree_node(int k) :tree_node(k, 0) {}
	};


	struct bstree
	{
		tree_node* root;
		bstree() :root(nullptr) {}
	};

	void inorder(tree_node* node)
	{
		if (node != nullptr)
		{
			inorder(node->left_);
			cout << node->key_ << endl;
			inorder(node->right_);
		}
	}

	void inorder_stack(tree_node* node)
	{
		stack<pair<tree_node*, bool>*> nodes;
		stack<int> record;
		nodes.push(new pair<tree_node*, bool>(node, false));

		while (!nodes.empty())
		{
			pair<tree_node*, bool>* n = nodes.top();
			if (n->first->left_ != nullptr && n->second == false)
			{
				nodes.push(new pair<tree_node*, bool>(n->first->left_, false));
				n->second = true;
				continue;
			}
			nodes.pop();
			cout << n->first->key_ << endl;
			if (n->first->right_ != nullptr)
			{
				nodes.push(new pair<tree_node*, bool>(n->first->right_, false));
				continue;
			}
		}
	}

	void preorder(tree_node* node)
	{
		if (node != nullptr)
		{
			cout << node->key_ << endl;
			preorder(node->left_);
			preorder(node->right_);
		}
	}

	void postorder(tree_node* node)
	{
		if (node != nullptr)
		{
			postorder(node->left_);
			postorder(node->right_);
			cout << node->key_ << endl;
		}
	}

	tree_node* search(tree_node* node, int k)
	{
		if (node == nullptr || node->key_ == k)
		{
			return node;
		}
		if (node->key_ < k)
			return search(node->left_, k);
		else
			return search(node->right_, k);
	}

	tree_node* iterative_search(tree_node* node, int k)
	{
		while (node != nullptr && node->key_ != k)
		{
			if (node->key_ < k)
				node = node->left_;
			else
				node = node->right_;
		}
		return node;
	}

	tree_node* tree_minimum(tree_node* node)
	{
		while (node->left_ != nullptr)
		{
			node = node->left_;
		}
		return node;
	}

	tree_node* tree_maxmum(tree_node* node)
	{
		while (node->right_ != nullptr)
		{
			node = node->right_;
		}
		return node;
	}

	tree_node* tree_successor(tree_node* node)
	{
		if (node->right_ != nullptr)
		{
			return tree_minimum(node->right_);
		}
		tree_node* y = node->parent_;
		while (y != nullptr && node == y->right_)
		{
			node = y;
			y = y->parent_;
		}
		return y;
	}

	tree_node* tree_predecessor(tree_node* node)
	{
		if (node->left_ != nullptr)
		{
			return tree_maxmum(node->left_);
		}
		tree_node* y = node->parent_;
		while (y != nullptr && node == y->left_)
		{
			node = y;
			y = y->parent_;
		}
		return y;
	}

	void tree_insert(bstree* t, tree_node* node)
	{
		tree_node* y = nullptr;
		tree_node* x = t->root;
		while (x != nullptr)
		{
			y = x;
			if (node->key_ < x->key_)
				x = x->left_;
			else
				x = x->right_;
		}
		node->parent_ = y;
		if (y == nullptr)
			t->root = node;
		else if (node->key_ < y->key_)
			y->left_ = node;
		else
			y->right_ = node;
	}

	void transplant(bstree t, tree_node* u, tree_node* v)
	{
		if (u->parent_ == nullptr)
			t.root = v;
		else if (u == u->parent_->left_)
			u->parent_->left_ = v;
		else
			u->parent_->right_ = v;
		if (v != nullptr)
			v->parent_ = u->parent_;
	}

	void tree_delete(bstree t, tree_node* node)
	{
		if (node->left_ == nullptr)
			transplant(t, node, node->right_);
		else if (node->right_ == nullptr)
			transplant(t, node, node->left_);
		else
		{
			tree_node* y = tree_minimum(node->right_);
			if (y->parent_ != node)
			{
				transplant(t, y, y->right_);
				y->right_ = node->right_;
				y->right_->parent_ = y;
			}
			transplant(t, node, y);
			y->left_ = node->left_;
			y->left_->parent_ = y;
		}
	}
}
