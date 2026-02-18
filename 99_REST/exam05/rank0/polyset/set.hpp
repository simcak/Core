#pragma once 

#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set
{
	private:
		searchable_bag	&m_sb;

	public:
		set(searchable_bag &sb);
		~set();

		void	insert(int);
		void	insert(int*, int);
		bool	has(int val) const	{ return m_sb.has(val); }
		void	print() const		{ m_sb.print(); }
		void	clear()				{ m_sb.clear(); }

		searchable_bag&	get_bag() { return m_sb; }
};

set::set(searchable_bag &sb) : m_sb(sb) {}

set::~set() {}

void set::insert(int val)
{
	if (this->has(val) == false)
		m_sb.insert(val);
}

void set::insert(int *array, int size)
{
	for (int i = 0; i < size; ++i)
		if (m_sb.has(array[i]) == false)
			m_sb.insert(array[i]);
}
