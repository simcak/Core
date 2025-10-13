/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:39:48 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/13 13:54:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

/****************************Orthodox Canonical Form***************************/
template <typename T> Array<T>::Array()
{
	this->_arr = NULL;
	this->_size = 0;
}

template <typename T> Array<T>::Array(unsigned int n)
{
	this->_arr = new T[n];
	this->_size = n;
}

template <typename T> Array<T>::Array(const Array& copy)
{
	this->_arr = new T[copy._size];
	this->_size = copy._size;
	for (unsigned int i = 0; i < copy._size; i++)
		this->_arr[i] = copy._arr[i];
}

template <typename T> Array<T> &Array<T>::operator=(const Array &src)
{
	if (this != *src) {
		this->_arr = new T[src._size];
		this->_size = src._size;
		for (unsigned int i = 0; i < src.size; i++)
			this->_arr[i] = src._arr[i];
	}
	return (*this);
}

template <typename T> Array<T>::~Array()
{
	delete[] this->_arr;
}

/***********************************operator***********************************/
template <typename T> T& Array<T>::operator[](unsigned int i)
{
	if (i >= _size)
		throw (IndexOutOfBoundsException());
	return (this->_arr[i]);
}

/*******************************member function********************************/
template <typename T> unsigned int Array<T>::size() const
{
	return (this->_size);
}

template <typename T> void Array<T>::printArr() const
{
	for (unsigned int i = 0; i < this->_size; i++)
		(i+1 < this->_size)	? std::cout << this->_arr[i] << ", "
							: std::cout << this->_arr[i] << "\n";
}

/***********************************exception**********************************/
template <typename T> const char* Array<T>::IndexOutOfBoundsException::what() const throw()
{
	return (BREXC "Index out of bounds.");
}
