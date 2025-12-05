#include "MutantStack.hpp"

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
	}

	std::cout << BY "\nMy test" RST << std::endl;
	{
		std::cout << BB "↓↓↓ String Stack Information ↓↓↓\n\n" RST;

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

		MutantStack<std::string>::iterator str_iter_begin = mstack_str.begin();
		MutantStack<std::string>::iterator str_iter_end = mstack_str.end();

		++str_iter_begin;
		--str_iter_begin;

		std::cout << "String Iterator: [ ** ";
		while (str_iter_begin != str_iter_end)
			std::cout << *str_iter_begin++ << " ** ";

		std::cout << "]\n\nSize:  " << mstack_str.size() << "\n";
		std::cout << "Empty: " << (mstack_str.empty() ? TRUE : FALSE);

		str_iter_begin = mstack_str.begin();
		while (str_iter_begin++ != str_iter_end)
			mstack_str.pop();

		std::cout << "\n\n" BB "↓↓↓ String After Poping ↓↓↓\n" RST;
		std::cout << "Size:  " << mstack_str.size() << "\n";
		std::cout << "Empty: " << (mstack_str.empty() ? TRUE : FALSE);

		std::cout << "\n----------------------------------------------------\n";

		/**********************************************************************/
		std::cout << BB "↓↓↓ Int Stack Information ↓↓↓\n\n" RST;

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

		MutantStack<int>::iterator iter_begin = mstack.begin();
		MutantStack<int>::iterator iter_end = mstack.end();

		++iter_begin;
		--iter_begin;

		std::cout << "Int Iterator: [ ** ";
		while (iter_begin != iter_end)
			std::cout << *iter_begin++ << " ** ";

		std::cout << "]\nSize:  " << mstack.size() << "\n";
		std::cout << "Empty: " << (mstack.empty() ? TRUE : FALSE);

		/**********************************************************************/
		std::cout << BB "\n↓↓↓ Const Int Stack Information ↓↓↓\n\n" RST;

		const MutantStack<int> const_mstack = mstack;

		MutantStack<int>::const_iterator const_iter_s = const_mstack.begin();
		MutantStack<int>::const_iterator const_iter_e = const_mstack.end();

		std::cout << "Const Int Iterator: [ ** ";
		while (const_iter_s != const_iter_e)
			std::cout << *const_iter_s++ << " ** ";

		std::cout << "]\nSize:  " << const_mstack.size() << "\n";
		std::cout << "Empty: " << (const_mstack.empty() ? TRUE : FALSE);
	}

	return 0;
}
