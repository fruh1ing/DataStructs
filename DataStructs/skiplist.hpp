#pragma once
#include <ctime>
#include <random>
#include <memory>
#include <stack>

int filp()
{
	static std::default_random_engine eng(time(0));
	static std::uniform_int_distribution<int> distr(0, 2);
	distr(eng);
	return distr(eng);
}

template<typename K, typename V>
class sklist_node
{
public:
	sklist_node();
	sklist_node(const K& k, const V& v);
	//sklist_node(K k, V v);
	~sklist_node();
	K get_key();
	V get_value();
	sklist_node<K, V>* get_next();
	sklist_node<K, V>* get_down();
	void set_key(K& k);
	void set_value(V& v);
	void set_next(sklist_node<K, V>* n);
	void set_down(sklist_node<K, V>* d);
private:
	K key;
	V value;
	sklist_node<K, V>* next;
	sklist_node<K, V>* down;
};

template<typename K, typename V>
sklist_node<K, V>::sklist_node()
	: next(nullptr)
	, down(nullptr)
{

}

template<typename K, typename V>
sklist_node<K, V>::sklist_node(const K& k, const V& v)
	:key(k), value(v), next(nullptr), down(nullptr)
{

}

//template<typename K, typename V>
//sklist_node<K, V>::sklist_node(K k, V v)
//	:key(k), value(v), next(nullptr), down(nullptr)
//{
//
//}

template<typename K, typename V>
sklist_node<K, V>::~sklist_node()
{
	//if (next != nullptr)delete next;
	//if (down != nullptr)delete down;
}

template<typename K, typename V>
K sklist_node<K, V>::get_key()
{
	return key;
}

template<typename K, typename V>
V sklist_node<K, V>::get_value()
{
	return value;
}

template<typename K, typename V>
sklist_node<K, V>* sklist_node<K, V>::get_next()
{
	return next;
}

template<typename K, typename V>
sklist_node<K, V>* sklist_node<K, V>::get_down()
{
	return down;
}

template<typename K, typename V>
void sklist_node<K, V>::set_key(K& k)
{
	key = k;
}

template<typename K, typename V>
void sklist_node<K, V>::set_value(V& v)
{
	value = v;
}

template<typename K, typename V>
void sklist_node<K, V>::set_next(sklist_node<K, V>* n)
{
	next = n;
}

template<typename K, typename V>
void sklist_node<K, V>::set_down(sklist_node<K, V>* d)
{
	down = d;
}

template<typename K, typename V>
class sklist
{
public:
	sklist();
	~sklist();
	V search(K k);
	void insert(K k, V v);


private:
	sklist_node<K, V>* head;
};

template<typename K, typename V>
sklist<K, V>::sklist()
	:head(nullptr)
{

}

template<typename K, typename V>
sklist<K, V>::~sklist()
{
	if (head != nullptr)
		delete head;
}

template<typename K, typename V>
V sklist<K, V>::search(K k)
{
	sklist_node<K, V>* current = this->head;
	bool stop{ false };
	bool found{ false };
	while (!found && !stop)
	{
		if (current == nullptr)
			stop = true;
		else
		{
			if (current->get_next() == nullptr)
				current = current->get_down();
			else
			{
				if (current->get_next()->get_key() == k)
					found = true;
				else
				{
					if (current->get_next()->get_key() > k)
						current = current->get_down();
					else
						current = current->get_next();
				}
			}
		}
	}
	if (found)
		return current->get_next()->get_value();
	else
		return V();
}

template<typename K, typename V>
void sklist<K, V>::insert(K k, V v)
{
	if (head == nullptr)
	{
		head = new sklist_node<K, V>();
		sklist_node<K, V>* node = new sklist_node<K, V>(k, v);
		head->set_next(node);
		sklist_node<K, V>* top = node;
		while (filp() == 1)
		{
			node = new sklist_node<K, V>(k, v);
			sklist_node<K, V>* new_head = new sklist_node<K, V>();
			new_head->set_down(head);
			node->set_down(top);
			new_head->set_next(node);
			head = new_head;
			top = node;
		}
	}
	else
	{
		std::stack< sklist_node<K, V>*> tower_stack;
		sklist_node<K, V>* current = head;
		bool stop{ false };
		while (!stop)
		{
			if (current == nullptr)
			{
				stop = true;
			}
			else
			{
				if (current->get_next() == nullptr)
				{
					tower_stack.push(current);
					current = current->get_down();
				}
				else
				{
					if (current->get_next()->get_key() > k)
					{
						tower_stack.push(current);
						current = current->get_down();
					}
					else
						current = current->get_next();
				}
			}
		}
		sklist_node<K, V>* lowest_level = tower_stack.top();
		tower_stack.pop();
		sklist_node<K, V>* temp = new sklist_node<K, V>(k, v);
		temp->set_next(lowest_level->get_next());
		lowest_level->set_next(temp);
		sklist_node<K, V>* top = temp;
		while (filp() == 1)
		{
			if (tower_stack.empty())
			{
				sklist_node<K, V>* new_head = new sklist_node<K, V>();
				temp = new sklist_node<K, V>(k, v);
				temp->set_down(top);
				new_head->set_next(temp);
				new_head->set_down(head);
				head = new_head;
				top = temp;
			}
			else
			{
				temp = new sklist_node<K, V>(k, v);
				temp->set_down(top);
				sklist_node<K, V>* pre_node = tower_stack.top();
				tower_stack.pop();
				temp->set_next(pre_node->get_next());
				pre_node->set_next(temp);
				top = temp;
			}
		}
	}
}

template<typename K, typename V>
class skmap
{
public:
	skmap();
	~skmap();
	void put(K& key, V& val);
	void put(const K& key, const V& val);
	V get(K k);
private:
	sklist<K, V>* collection;
};

template<typename K, typename V>
skmap<K, V>::skmap() :collection(new sklist<K, V>())
{

}

template<typename K, typename V>
skmap<K, V>::~skmap()
{
	delete collection;
}

template<typename K, typename V>
void skmap<K, V>::put(K& key, V& val)
{
	collection->insert(key, val);
}


template<typename K, typename V>
void skmap<K, V>::put(const K& key, const V& val)
{
	collection->insert(key, val);
}

template<typename K, typename V>
V skmap<K, V>::get(K k)
{
	return collection->search(k);
}
