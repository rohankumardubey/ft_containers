/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_header.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 13:35:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 18:35:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HEADER_HPP
# define TEST_HEADER_HPP

#ifndef FT
 #define FT 1
 #include "Vector.hpp"
 #include "List.hpp"
 #include "Map.hpp"
 #include "Stack.hpp"
 #include "Queue.hpp"
  using namespace ft;
#elif FT == 1
 #include "Vector.hpp"
 #include "List.hpp"
 #include "Map.hpp"
 #include "Stack.hpp"
 #include "Queue.hpp"
  using namespace ft;
#else
 #include <vector>
 #include <list>
 #include <map>
 #include <stack>
 #include <queue>
  using namespace std;
#endif

# include <iostream>
# include <string>
# include <stdio.h>

#include <vector> //see line 129

#define WHITE "\033[37;01m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[m"

template <typename Container>
void	capacity_information(Container c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
	std::cout << "Capacity of " << title << " is " << c.capacity() << std::endl;
}

void	print_version()
{
	static const std::string versions[] = {
	"STANDARD",
	"FT",
	};

	std::cout << "THE VERSION BEING RAN IS: " << versions[FT] << std::endl;
}

void	container_header(std::string name)
{
	size_t padding = 66 - name.size();

	std::cout << "******************************************************************" << std::endl;
	std::cout << std::string(padding / 2, ' ');
	std::cout << name;
	std::cout << std::string((padding / 2) + padding % 2, ' ') << std::endl;
	std::cout << "******************************************************************" << std::endl;
}

void	subject_title(std::string name)
{
	size_t padding = 66 - name.size();
	std::cout << std::endl << "------------------------------------------------------------------" << std::endl;
	std::cout << std::string(padding / 2, ' ');
	std::cout << name;
	std::cout << std::string((padding / 2) + padding % 2, ' ');
	std::cout << std::endl << "------------------------------------------------------------------" << std::endl << std::endl;
}

template <typename Container>
void	comparison_operator_container(Container a, Container b, std::string a_title, std::string b_title) {
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << a_title << YELLOW << " operator == " << RESET << b_title << " = " << ((a == b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << a_title << YELLOW << " operator != " << RESET << b_title << " = " << ((a != b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << a_title << YELLOW << " operator <  " << RESET << b_title << " = " << ((a < b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << a_title << YELLOW << " operator <= " << RESET << b_title << " = " << ((a <= b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << a_title << YELLOW << " operator >  " << RESET << b_title << " = " << ((a > b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << a_title << YELLOW << " operator >= " << RESET << b_title << " = " << ((a >= b) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << b_title << YELLOW << " operator == " << RESET << a_title << " = " << ((b == a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << b_title << YELLOW << " operator != " << RESET << a_title << " = " << ((b != a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << b_title << YELLOW << " operator <  " << RESET << a_title << " = " << ((b < a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << b_title << YELLOW << " operator <= " << RESET << a_title << " = " << ((b <= a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << b_title << YELLOW << " operator >  " << RESET << a_title << " = " << ((b > a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << b_title << YELLOW << " operator >= " << RESET << a_title << " = " << ((b >= a) ? GREEN "True" : RED "False") << RESET << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
}

template <class Key, class Value>
void	print_content(const pair<Key, Value>& content)
{
	std::cout << content.first << " : " << content.second;
}

template <class T>
void	print_content(const T& content)
{
	std::cout << content;
}

template <typename Container>
void	const_operator_print_container(const Container& c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using const [] operator element access" << std::endl;

	for (size_t i = 0; i < c.size() ; i++)
	{
		print_content(c[i]);
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <typename Container, class Key>
void	operator_print_container(Container c, std::string title, const std::vector<Key>& keys, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using [] operator element access" << std::endl;

	for (size_t i = 0; i < keys.size(); i++)
	{
		print_content(c[keys[i]]);
		if (i + 1 < keys.size())
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
		print_content(c[i]);
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <class Container>
void	is_empty(const Container& c, std::string title)
{
	std::cout << "container " << title << " is " << ((c.empty()) ? "empty" : "not empty") << std::endl;
}

//iterator print functions

template <typename Container>
void	iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'iterator'" << std::endl;
	typename Container::iterator it = c.begin();

	for (;it != c.end();)
	{
		print_content(*it);
		if (++it == c.end())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	const_iter_print_container(const Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'const_iterator'" << std::endl;
	typename Container::const_iterator it = c.begin();

	for (;it != c.end();)
	{
		print_content(*it);
		if (++it == c.end())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	reverse_iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'reverse_iterator'" << std::endl;
	typename Container::reverse_iterator it = c.rbegin();

	for (;it != c.rend();)
	{
		print_content(*it);
		if (++it == c.rend())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	const_reverse_iter_print_container(const Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'const_reverse_iterator'" << std::endl;
	typename Container::const_reverse_iterator it = c.rbegin();

	for (;it != c.rend();)
	{
		print_content(*it);
		if (++it == c.rend())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

#endif
