#pragma once
#include "searchable_bag.hpp"
#include "array_bag.hpp"

class	searchable_array_bag : public searchable_bag, public array_bag
{
	public:
		bool	has(int) const;
};



bool	searchable_array_bag::has(int val) const
{
	for (int i = 0; i < this->size; ++i)
		if (data[i] == val)
			return true;
	return false;
}

