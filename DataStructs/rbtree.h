#include <iostream>

using std::cout;
using std::endl;
namespace datastruct {
	struct rbtree_node
	{
		enum color {
			red,
			black
		};
		color color_;
		typedef rbtree_node* node_ptr;
		node_ptr p_, left_, right_;
		int key;
		rbtree_node(color c, int k) :color_(c), p_(nullptr), left_(nullptr),
			right_(nullptr), key(k) {}
		rbtree_node(color c) :rbtree_node(c, 0) {}
	};

	struct rbtree {
		rbtree_node* root;
		typedef typename rbtree_node::color color;
		rbtree_node* nil_node;

		rbtree() :nil_node(new rbtree_node(color::black)) { root = nil_node; }

		void help_inorder(rbtree_node* node)
		{
			if (node != this->nil_node)
			{
				help_inorder(node->left_);
				cout << node->key << endl;
				help_inorder(node->right_);
			}
		}

		void inorder()
		{
			help_inorder(this->root);
		}

		// 左旋
		void left_rotate(rbtree_node* x)
		{
			rbtree_node* y = x->right_;
			x->right_ = y->left_;
			if (y->left_ != this->nil_node)
				y->left_->p_ = x;
			y->p_ = x->p_;
			if (x->p_ == this->nil_node)
				this->root = y;
			else if (x == x->p_->left_)
				x->p_->left_ = y;
			else
				x->p_->right_ = y;
			y->left_ = x;
			x->p_ = y;
		}

		void right_rotate(rbtree_node* x)
		{
			rbtree_node* y = x->left_;
			x->left_ = y->right_;
			if (y->right_ != this->nil_node)
				y->right_->p_ = x;
			y->p_ = x->p_;
			if (x->p_ == this->nil_node)
				this->root = y;
			else if (x == x->p_->left_)
				x->p_->left_ = y;
			else
				x->p_->right_ = y;
			y->right_ = x;
			x->p_ = y;
		}

		rbtree_node* treee_minimum(rbtree_node* z)
		{
			rbtree_node* x = z;
			while (z != nil_node)
			{
				x = z;
				z = z->left_;
			}
			return x;
		}


		void insert(rbtree_node* z)
		{
			rbtree_node* y = this->nil_node;
			rbtree_node* x = this->root;
			while (x != this->nil_node)
			{
				y = x;
				if (z->key < x->key)
					x = x->left_;
				else
					x = x->right_;
			}
			z->p_ = y;
			if (y == this->nil_node)
				this->root = z;
			else if (z->key < y->key)
				y->left_ = z;
			else
				y->right_ = z;
			z->left_ = this->nil_node;
			z->right_ = this->nil_node;
			z->color_ = color::red;
			insert_fixup(z);
		}

		void insert_fixup(rbtree_node* z)
		{
			while (z->p_->color_ == color::red)
			{
				if (z->p_ == z->p_->p_->left_)
				{
					rbtree_node* y = z->p_->p_->right_;
					if (y->color_ == color::red)
					{
						z->p_->color_ = color::black;
						y->color_ = color::black;
						z->p_->p_->color_ = color::red;
						z = z->p_->p_;
					}
					else if (z == z->p_->right_)
					{
						z = z->p_;
						left_rotate(z);
					}
					else
					{
						z->p_->color_ = color::black;
						z->p_->p_->color_ = color::red;
						right_rotate(z->p_->p_);
					}
				}
				else
				{
					rbtree_node* y = z->p_->p_->left_;
					if (y->color_ == color::red)
					{
						z->p_->color_ = color::black;
						y->color_ = color::black;
						z->p_->p_->color_ = color::red;
						z = z->p_->p_;
					}
					else if (z == z->p_->left_)
					{
						z = z->p_;
						right_rotate(z);
					}
					else
					{
						z->p_->color_ = color::black;
						z->p_->p_->color_ = color::red;
						left_rotate(z->p_->p_);
					}
				}
			}
			this->root->color_ = color::black;
		}

		void rb_transplant(rbtree_node* u, rbtree_node* v)
		{
			if (u->p_ == nil_node)
				root = v;
			else if (u == u->p_->left_)
			{
				u->p_->left_ = v;
			}
			else
			{
				u->p_->right_ = v;
			}
			v->p_ = u->p_;
		}

		void rb_delete(rbtree_node* z)
		{
			rbtree_node* y = z;
			rbtree_node* x;
			color y_original_color = y->color_;
			if (z->left_ == nil_node)
			{
				x = z->right_;
				rb_transplant(z, z->right_);
			}
			else if (z->right_ == nil_node)
			{
				x = z->left_;
				rb_transplant(z, z->left_);
			}
			else
			{
				y = this->treee_minimum(z->right_);
				y_original_color = y->color_;
				x = y->right_;
				if (y->p_ == z)
					x->p_ = y;
				else
				{
					rb_transplant(y, y->right_);
					y->right_ = z->right_;
					y->right_->p_ = y;
				}
				rb_transplant(z, y);
				y->left_ = z->left_;
				y->left_->p_ = y;
				y->color_ = z->color_;
			}
			if (y_original_color == color::black)
				delete_fixup(x);
		}

		void delete_fixup(rbtree_node* x)
		{
			while (x != root && x->color_ == color::black)
			{
				if (x = x->p_->left_)
				{
					rbtree_node* w = x->p_->right_;
					if (x->color_ == color::red)
					{
						w->color_ = color::black;
						x->p_->color_ = color::red;
						left_rotate(x->p_);
						w = x->p_->right_;
					}
					else
					{
						if (w->left_->color_ == color::black && w->right_->color_ == color::black)
						{
							w->color_ = color::red;
							x = x->p_;
						}
						else if (w->right_->color_ == color::black)
						{
							w->color_ = color::red;
							w->left_->color_ = color::black;
							right_rotate(w);
							w = x->p_->right_;
						}
						else
						{
							w->color_ = x->p_->color_;
							x->p_->color_ = color::black;
							w->right_->color_ = color::black;
							left_rotate(x->p_);
							x = root;
						}
					}
				}
				else
				{
					rbtree_node* w = x->p_->left_;
					if (w->color_ == color::red)
					{
						w->color_ = color::black;
						x->p_->color_ = color::red;
						right_rotate(x->p_);
						w = x->p_->left_;
					}
					else
					{
						if (w->left_->color_ == color::black && w->right_->color_ == color::black)
						{
							w->color_ = color::red;
							x = x->p_;
						}
						else if (w->left_->color_ == color::black)
						{
							w->right_->color_ = color::black;
							w->color_ = color::red;
							left_rotate(w);
							w = x->p_->left_;
						}
						else
						{
							w->color_ = x->p_->color_;
							x->p_->color_ = color::black;
							w->left_->color_ == color::black;
							right_rotate(x->p_);
							x = root;
						}
					}
				}
			}
			x->color_ = color::black;
		}
	};
}
