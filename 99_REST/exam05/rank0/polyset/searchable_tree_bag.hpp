#pragma once
#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class	searchable_tree_bag : public searchable_bag, public tree_bag
{
	public:
		bool	search(node *node, const int value) const;
		bool	has(int) const;
};



bool	searchable_tree_bag::search(node *node, const int value) const
{
	if(node == nullptr)
		return false;
	if(node->value == value)
		return true;
	else if(value < node->value)
		return search(node->l, value);
	else
		return search(node->r, value);
}

bool	searchable_tree_bag::has(int value) const
{
	return search(this->tree, value);
}
