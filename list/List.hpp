/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   List.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 15:50:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 19:38:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <limits>

# include "traits.hpp"
# include "IteratorFunctions.hpp"
# include "BidirectionalIterator.hpp"
# include "ReverseBidirectionalIterator.hpp"
# include "GenericFunctions.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class	list
	{
		private:
			class node
			{
				public:
					node() : prev(NULL), next(NULL) {}
					node(const T& element, node *prev = NULL, node *next = NULL) : element(element), prev(prev), next(next) {}
					node& operator = (const node& other)
					{
						if (this != &other)
						{
							this->element = other.element;
							this->prev = other.prev;
							this->next = other.next;
						}
						return (*this);
					}
					~node() {}
					T		element;
					node	*prev;
					node	*next;
			};
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef T&														reference;
			typedef const T& 												const_reference;
			typedef T*														pointer;
			typedef const T*												const_pointer;
			typedef BidirectionalIterator<node, T*, T&>						iterator;
			typedef BidirectionalIterator<node, const T*, const T&>			const_iterator;
			typedef ReverseBidirectionalIterator<node, T&, const T&>		reverse_iterator;
			typedef ReverseBidirectionalIterator<node, const T*, const T&>	const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;

//-------------------------------------------------------CONSTRUCTOR-----------------------------------------------------

			//DEFAULT
			explicit list(const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
			}
			//FILL
			explicit list(size_t n, const T& val = T(), const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
				this->assign(n, val);
			}
			//RANGE
			template<class InputIterator>
			list(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
				this->assign(first, last);
			}
			//COPY
			list(const list& other) : len(0), head(new node()), tail(new node()), alloc(other.alloc)
			{
				head->next = tail;
				tail->prev = head;
				this->assign(other.begin(), other.end());
			}

//-------------------------------------------------------DESTRUCTOR-----------------------------------------------------

			~list()
			{
				clear();
				delete this->head;
				delete this->tail;
			}

//-------------------------------------------------------ASSIGNMENT OPERATOR-----------------------------------------------------

			list& operator = (const list& other)
			{
				if (this != &other)
					this->assign(other.begin(), other.end());
				return (*this);
			}

//-------------------------------------------------------ITERATORS-----------------------------------------------------

			iterator begin()
			{
				return (iterator(this->head->next));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->head->next));
			}

			iterator end()
			{
				return (iterator(this->tail));
			}
			const_iterator end() const
			{
				return (const_iterator(this->tail));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->tail->prev));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->tail->prev));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->head));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->head));
			}

//-------------------------------------------------------CAPACITY-----------------------------------------------------

			bool empty() const
			{
				return (!this->len);
			}
			size_t size() const
			{
				return (this->len);
			}
			size_t max_size() const
			{
				return (alloc.max_size());
			}

//-------------------------------------------------------ELEMENT ACCESS-----------------------------------------------------

			T& front()
			{
				return (this->head->next->element);
			}
			const T& front() const
			{
				return (this->head->next->element);
			}

			T& back()
			{
				return (this->tail->prev->element);
			}
			const T& back() const
			{
				return (this->tail->prev->element);
			}

//-------------------------------------------------------MODIFIERS-----------------------------------------------------

			//RANGE
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL)
			{
				clear();
				this->insert(this->begin(), first, last);
			}
			//FILL
			void assign(size_t n, const T& val)
			{
				clear();
				this->insert(this->begin(), n, val);
			}

			void push_front(const T& val)
			{
				newNode(val, 0);
			}
			void pop_front()
			{
				delNode(0);
			}
			void push_back(const T& val)
			{
				newNode(val);
			}
			void pop_back()
			{
				delNode();
			}

			//SINGLE ELEMENT
			iterator insert(iterator position, const T& val)
			{
				size_t pos = ft::distance(this->begin(), position);
				return (iterator(newNode(val, pos)));
			}
			//FILL
			void insert(iterator position, size_t n, const T& val)
			{
				size_t pos = ft::distance(this->begin(), position);

				for (size_t i = 0; i < n; i++)
					newNode(val, pos + i);
			}
			//RANGE
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL)
			{
				size_t pos = ft::distance(this->begin(), position);

				for (; first != last; first++)
					newNode(*first, pos++);
			}

			//SINGLE ELEMENT
			iterator erase(iterator position)
			{
				size_t pos = ft::distance(this->begin(), position);

				position++;
				delNode(pos);
				return (position);
			}
			//RANGE
			iterator erase(iterator first, iterator last)
			{
				size_t pos = ft::distance(this->begin(), first);
				size_t length = ft::distance(first, last);
				last++;
				for (size_t i = 0; i < length ; i++)
					delNode(pos);
				return (last);
			}

			void swap(list& x)
			{
				ft::swap(this->head, x.head);
				ft::swap<size_t>(this->len, x.len);
				ft::swap(this->tail, x.tail);
			}
			void resize(size_t n, const T& val = T())
			{
				size_t len = this->len;
				if (this->len == n)
					return ;
				if (this->len > n)
				{
					for (size_t i = 0 ; i < (len - n); i++)
						delNode();
				}
				else
				{
					for (; len < n; len++)
						newNode(val);
				}
			}
			void clear()
			{
				this->erase(this->begin(), this->end());
			}

//-------------------------------------------------------OPERATIONS-----------------------------------------------------

			//ENTIRE LIST
			void splice (iterator position, list& x)
			{
				splice(position, x, x.begin(), x.end());
			}
			//SINGLE ELEMENT
			void splice (iterator position, list& x, iterator i)
			{
				splice(position, x, i, ++iterator(i));
			}
			//ELEMENT RANGE
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				if (first == last)
					return ;
				size_t len = ft::distance(first, last);

				connect(--iterator(position), first--);
				connect(first, last--);
				connect(last, position);

				this->len += len;
				x.len -= (len > x.len) ? x.len : len;
			}

			void remove (const T& val)
			{
				for (iterator it = this->begin(); it != this->end();)
				{
					if (*it == val)
						it = erase(it);
					else
						it++;
				}
			}
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				for (iterator it = this->begin(); it != this->end();)
				{
					if (pred(*it))
						it = erase(it);
					else
						it++;
				}
			}
			void unique()
			{
				for (iterator it = this->begin(); it != this->end(); it++)
				{
					iterator jt = it;
					jt++;
					for (; *jt == *it && jt != this->end(); jt++)
						erase(jt);
				}
			}
			template <class BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				iterator it = this->begin();
				for (iterator it = this->begin(); it != this->end(); it++)
				{
					for (iterator jt = ++iterator(it); jt != this->end() && binary_pred(*it, *jt); jt++)
						erase(jt);
				}
			}
			void	merge(list& x)
			{
				iterator orig = this->begin();
				for (iterator it = x.begin(); it != x.end();)
				{
					for (; *it > *orig && orig != this->end(); orig++) {}
					splice(orig, x, it++);
				}
			}
			template<class Compare>
			void	merge(list& x, Compare comp)
			{
				iterator orig = this->begin();
				for (iterator it = x.begin(); it != x.end();)
				{
					for (; comp(*orig, *it) && orig != this->end(); orig++) {}
					splice(orig, x, it++);
				}
			}
			void	sort()
			{
				if (this->size() == 1)
					return ;
				iterator middle = this->begin();
				for (size_t i = 0; i < this->size() / 2; i++)
					middle++;
				list<T>	right;
				list<T>	left;
				right.splice(right.begin(), *this, this->begin(), middle);
				left.splice(left.begin(), *this);
				right.sort();
				left.sort();
				right.merge(left);
				this->splice(this->begin(), right);
			}
			template <class Compare>
			void	sort(Compare comp)
			{
				if (this->size() == 1)
					return ;
				iterator middle = this->begin();
				for (size_t i = 0; i < this->size() / 2; i++)
					middle++;
				list<T>	right;
				list<T>	left;
				right.splice(right.begin(), *this, this->begin(), middle);
				left.splice(left.begin(), *this);
				right.sort(comp);
				left.sort(comp);
				right.merge(left, comp);
				this->splice(this->begin(), right);
			}
			void	reverse()
			{
				for (iterator it = ++(this->begin()); it != this->end();)
					splice(this->begin(), *this, it++);
			}
		private:
			void	connect(iterator front, iterator back)
			{
				front.ptr->next = back.ptr;
				back.ptr->prev = front.ptr;
			}
			void	delNode(size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->head->next;

				if (!this->len)
					return ;
				for (size_t i = 0; i < pos && ptr != NULL && ptr->next != this->tail; i++) //skip to the right position
					ptr = ptr->next;
				if (!ptr || ptr == this->tail)
					return ;
				node *prev = ptr->prev;
				ptr->prev->next = ptr->next;
				ptr->next->prev = prev;
				--this->len;
				delete ptr;
			}
			node	*newNode(const T& value, size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->head;

				for (size_t i = 0; i < pos && ptr && ptr->next != this->tail; i++)
					ptr = ptr->next;
				if (!ptr)
					return (NULL);
				ptr->next = new node(value, ptr, ptr->next);
				ptr->next->next->prev = ptr->next;
				this->len++;
				return (ptr->next);
			}
			size_t	len;
			node	*head;
			node	*tail;
			Alloc	alloc;
	};

//-------------------------------------------------------RELATIONAL OPERATORS-----------------------------------------------------

	template <class T>
	bool	operator == (const list<T>& src, const list<T>& other)
	{
		if (src.size() != other.size())
			return (false);
		return (ft::equal(src.begin(), src.end(), other.begin()));
	}

	template <class T>
	bool	operator != (const list<T>& src, const list<T>& other)
	{
		return !(src == other);
	}

	template <class T>
	bool	operator < (const list<T>& src, const list<T>& other)
	{
		return (ft::lexicographical_compare(src.begin(), other.begin(), src.end(), other.end()));
	}

	template <class T>
	bool	operator > (const list<T>& src, const list<T>& other)
	{
		return (other < src);
	}

	template <class T>
	bool	operator >= (const list<T>& src, const list<T>& other)
	{
		return !(src < other);
	}

	template <class T>
	bool	operator <= (const list<T>& src, const list<T>& other)
	{
		return !(other < src);
	}

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		return (x.swap(y));
	}

}

#endif
