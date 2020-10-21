/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 19:16:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 21:33:20 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <IteratorFunctions.hpp>

#if FT == 1
 #include "Vector.hpp"
 #define vector ft::vector
#else
 #include <vector>
 #define vector std::vector
#endif

//[] operator element access print

template <typename Container>
void	const_operator_print_container(const Container& c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using const [] operator element access" << std::endl;

	for (size_t i = 0;i < c.size(); i++)
	{
		std::cout << c[i];
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <typename Container>
void	operator_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using [] operator element access" << std::endl;

	for (size_t i = 0;i < c.size(); i++)
	{
		std::cout << c[i];
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

//iterator print functions

template <typename Container>
void	iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'iterator'" << std::endl;
	typename Container::iterator it = c.begin();

	for (;it != c.end(); it++)
	{
		std::cout << *it;
		if (it + 1 < c.end())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <typename Container>
void	reverse_iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'reverse_iterator'" << std::endl;
	typename Container::reverse_iterator it = c.rbegin();

	for (;it != c.rend(); it++)
	{
		std::cout << *it;
		if (it + 1 < c.rend())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <typename Container>
void	capacity_information(Container c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
	std::cout << "Capacity of " << title << " is " << c.capacity() << std::endl;
}

int	main(void)
{
	static const std::string versions[] = {
	"STANDARD",
	"FT",
	};

	std::cout << "THE VERSION BEING RAN IS: " << versions[FT] << std::endl;

	//Constructors
	std::cout << "\n----CONSTRUCTORS----\n" << std::endl;

	vector<int>	vec_default;
	vector<int> vec_fill(100, 5);
	vector<int> vec_range(vec_fill.begin(), vec_fill.begin() + 5);
	vector<int> vec_copy(vec_fill);
	iter_print_container<vector<int> >(vec_default, "vec_default");
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_range, "vec_range");
	iter_print_container<vector<int> >(vec_copy, "vec_copy");

	//Modifiers
	std::cout << "\n----MODIFIERS----\n" << std::endl;

	vec_default.push_back(5);
	vec_default.pop_back();

	//Capacity
	std::cout << "\n----CAPACITY----\n" << std::endl;

	std::cout << "Max Size of " << "vector" << " is " << vec_default.max_size() << std::endl;

	std::cout << "vec_default" << " is empty? " << (vec_default.empty() ? "TRUE" : "FALSE") << std::endl;
	vec_default.push_back(5);
	std::cout << "vec_default" << " is empty? " << (vec_default.empty() ? "TRUE" : "FALSE") << std::endl;
	vec_default.pop_back();
	vec_default.push_back(1);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(0);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(1);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(5);
	capacity_information<vector<int> >(vec_default, "vec_default");

	std::cout << std::endl;

	vector<int> vec_fill_big(1000000, 10);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.reserve(5000000);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.resize(5000000);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.push_back(5);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");

	//Iterators
	std::cout << "\n----ITERATORS----\n" << std::endl;


	for (vector<int>::iterator it = vec_range.begin(); it != vec_range.end(); it++)
		*it = ft::distance(vec_range.begin(), it);

	iter_print_container<vector<int> >(vec_range, "vec_range");
	reverse_iter_print_container<vector<int> >(vec_range, "vec_range");

	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.resize(3);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.resize(0);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");

	vector<int> vec_size(100);
	capacity_information<vector<int> >(vec_size, "vec_size");
	capacity_information<vector<int> >(vec_fill, "vec_fill");
	vec_fill.pop_back();
	capacity_information<vector<int> >(vec_fill, "vec_fill");

	vec_default.resize(20);
	capacity_information<vector<int> >(vec_default, "vec_default");
	iter_print_container<vector<int> >(vec_default, "vec_default");

	//Element Access
	vector<int> const vec_const(5, 10);
	std::cout << "\n----OPERATOR OVERLOAD ELEMENT ACCESS----\n" << std::endl;

	operator_print_container<vector<int> >(vec_default, "vec_default");
	const_operator_print_container<vector<int> >(vec_const, "vec_const");
	return (0);
}
