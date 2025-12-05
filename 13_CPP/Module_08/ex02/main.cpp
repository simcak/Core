#include "MutantStack.hpp"

template <typename T>
static void	_print_info(MutantStack<T> &mstack, std::string text)
{
	typename MutantStack<T>::iterator ms_begin = mstack.begin();
	typename MutantStack<T>::iterator ms_end   = mstack.end();

	++ms_begin;
	--ms_begin;

	std::cout << text << "\n";

	std::cout << "Iterator: [ ** ";
	while (ms_begin != ms_end)
		std::cout << *ms_begin++ << " ** ";
	std::cout << "]\n\n";

	std::cout << "Size:  " << mstack.size() << std::endl;
	std::cout << "Empty: " << (mstack.empty() ? TRUE : FALSE) << std::endl;
}

int	main()
{
	std::cout << BY "42subject test" RST << std::endl;
	{
		MutantStack<int>	mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << "top:  " << mstack.top() << std::endl;

		mstack.pop();

		std::cout << "size: " << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);

		MutantStack<int>::iterator	it = mstack.begin();
		MutantStack<int>::iterator	ite = mstack.end();

		++it;
		--it;

		while (it != ite)
		{
			std::cout << "it:   " << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
		std::cout << std::endl;
	}

	std::cout << BY "\nMy test - String" RST << std::endl;
	{
		MutantStack<std::string> mstack_str;
		mstack_str.push("Five");
		mstack_str.push("Seventeen");
		mstack_str.pop();
		mstack_str.push("Three");
		mstack_str.push("Fourty two");
		mstack_str.push("Four");
		mstack_str.push("Two");
		mstack_str.push("Seven hundred thirty-seven");
		mstack_str.pop();

		_print_info(mstack_str, BB "↓↓↓ String Stack Information ↓↓↓" RST);

		MutantStack<std::string>::iterator str_iter_begin = mstack_str.begin();
		MutantStack<std::string>::iterator str_iter_end = mstack_str.end();

		str_iter_begin = mstack_str.begin();
		while (str_iter_begin++ != str_iter_end)
			mstack_str.pop();

		_print_info(mstack_str, BB "↓↓↓ String After Poping ↓↓↓" RST);
	}

	std::cout << BY "\nMy test - Int" RST << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		mstack.pop();
		mstack.push(3);
		mstack.push(42);
		mstack.push(4);
		mstack.push(2);
		mstack.push(737);
		mstack.pop();

		_print_info(mstack, BB "↓↓↓ Int Stack Information ↓↓↓" RST);

		/**********************************************************************/
		std::cout << BB "\n↓↓↓ Const Int Stack Information ↓↓↓\n" RST;

		const MutantStack<int> const_mstack = mstack;

		MutantStack<int>::const_iterator const_iter_s = const_mstack.begin();
		MutantStack<int>::const_iterator const_iter_e = const_mstack.end();

		std::cout << "Const Int Iterator: [ ** ";
		while (const_iter_s != const_iter_e)
			std::cout << *const_iter_s++ << " ** ";

		std::cout << "]\n\nSize:  " << const_mstack.size() << "\n";
		std::cout << "Empty: " << (const_mstack.empty() ? TRUE : FALSE);
	}

	return 0;
}
