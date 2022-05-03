#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include <cstring>
#include <memory> // allocator class 사용, 메모리관리, allocator가 메모리 관리 
// #include <cstddef> // C헤더파일 <stddef.h>와 <stdlib.h>의 새로운 버전으로, 공통상수, 매크로, 타입, 함수들을 정의하고 있다.
// #include "ReverseIterator.hpp"
#include "utils.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef T*  pointer;
            typedef T&  reference;
            
        public :
            random_access_iterator() : _ptr()
            {}
            random_access_iterator (pointer it) : _ptr(it)
            {}
            random_access_iterator(const random_access_iterator &other) :_ptr(other._ptr)
            {}
            random_access_iterator &operator=(const random_access_iterator &x)
            {
                _ptr = x._ptr;
                return (*this);
		    }
            virtual ~random_access_iterator() {}
            pointer base() const
            {
                return (_ptr);
            }
            random_access_iterator& operator++()
            {
                _ptr++;
                return (*this);
            }
            operator random_access_iterator<const value_type>() const
            {
                return random_access_iterator<const value_type>(_ptr);
            }
            random_access_iterator operator++(int)
            {
                random_access_iterator tmp(*this);
                _ptr++;
                return (tmp);
            }
            random_access_iterator& operator--()
            {
                _ptr--;
                return (*this);
            } 
            random_access_iterator operator--(int)
            {
                random_access_iterator tmp(*this);
                _ptr--;
                return (tmp);
            }
            reference operator[](difference_type n) const
            {
                return (*(operator+(n)));
            }
            pointer operator->()
            {
                return (_ptr);
            }
            reference operator*()
            {
                return *(_ptr);
            }
            random_access_iterator operator-(const difference_type n) const 
            {
                return (random_access_iterator(_ptr - n));
            }
            random_access_iterator operator+(const difference_type n) const
            {
                return (random_access_iterator(_ptr + n));
            }
            random_access_iterator& operator+=(const difference_type n)
            {
                _ptr += n;
                return (*this);
            }
            random_access_iterator& operator-=(const difference_type n)
            {
                _ptr -= n;
                return (*this);
            }
        protected :
            pointer _ptr;
    };
    template <class T>
    bool operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template<class T_L, class T_R>
    bool operator==(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T>
    bool operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template<class T_L, class T_R>
    bool operator!=(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class T>
    bool operator<  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template<class T_L, class T_R>
    bool operator <(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base()  < rhs.base());
    }
    template <class T>
    bool operator<=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template<class T_L, class T_R>
    bool operator<=(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class T>
    bool operator>  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template<class T_L, class T_R>
    bool operator>(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class T>
    bool operator>=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template<class T_L, class T_R>
    bool operator>=(const random_access_iterator<T_L> lhs, const random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class T>
    ft::random_access_iterator<T> operator+ (typename ft::random_access_iterator<T>::difference_type n, const random_access_iterator<T>& _it)
    {
        return (_it + n);
    }
    template <class TL, class TR>
    typename ft::random_access_iterator<TL>::difference_type operator+ (const ft::random_access_iterator<TL>& lhs, const ft::random_access_iterator<TR>& rhs)
    {
        return (lhs.base() + rhs.base());
    }
    template <class T>
    typename ft::random_access_iterator<T>::difference_type operator- (const ft::random_access_iterator<T>& lhs, const ft::random_access_iterator<T>& rhs)
    {
        return (lhs.base() - rhs.base());
    }
    template <class TL, class TR>
    typename ft::random_access_iterator<TL>::difference_type operator- (const ft::random_access_iterator<TL>& lhs, const ft::random_access_iterator<TR>& rhs)
    {
        return (lhs.base() - rhs.base());
    }
    

    template< class T, class Alloc = std::allocator<T> >
    class vector
    {
        public :
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef ft::random_access_iterator<value_type> iterator;
            typedef ft::random_access_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename allocator_type::size_type size_type;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        public :
            explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc),_start(nullptr), _size(0), _capacity(0)
            {}
            vector(const vector& x) : _start(nullptr), _size(0), _capacity(0)
            {
                *this = x;
            }
            explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc),_start(nullptr), _size(0), _capacity(0)
            {
                _start = _alloc.allocate(n);
                _size = n;
                _capacity = n;
                size_type i = 0;
                while (i < n)
                {
                    _alloc.construct(_start+i, value);
                    i++;
                }    
            }
            template<class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator >::type* = 0) :_alloc(alloc), _start(nullptr), _size(0), _capacity(0)
            {
                pointer tmp;
                difference_type n = ft::distance(first, last);
                _start = _alloc.allocate(n);
                tmp = _start;
                _size = n;
                _capacity = n;
                while (n--)
                {
                    _alloc.construct(tmp, *first++);
					tmp++;
                }
            }
            ~vector()
            {
                this->clear();
                _alloc.deallocate(_start, _capacity);
            }
            vector& operator=(const vector& x)
            {
                this->clear();
                _alloc.deallocate(_start, _capacity);
                if (_capacity < x.capacity())
                {
                    _start = _alloc.allocate(x._size);
                    _capacity = x._size;
                }
                _size = x._size;
                for (size_type i = 0; i < x._size; i++)
                    _alloc.construct(_start + i, x[i]);
			    return (*this);
            }

            const_reference operator[](size_type n) const
            {
                return (*(_start + n));
            }
            reference operator[](size_type n)
            {
                return (*(_start + n));
            }
            void    push_back(const value_type& val)
            {
                if (_capacity == 0)
                    reserve(1);
                else if (_capacity == _size)
                    reserve(_capacity * 2);
                _alloc.construct(_start + _size, val);
                _size++;
            }
            size_type  size() const {return (_size);}
            void    pop_back() 
            {
                _alloc.destroy(_start + _size - 1);
                _size--;
            }
            void    clear() 
            {
                size_type i = 0;
                while (i < _size)
                {
                    _alloc.destroy(_start+i);
                    i++;
                }
                _size = 0;
            }
            iterator begin() {return (iterator(_start));}
            allocator_type get_allocator() const { return (_alloc); }
            iterator end()  {return (iterator(_start + _size));}
            const_iterator begin() const {return (const_iterator(_start));}
            const_iterator end()  const {return (const_iterator(_start + _size));}
            const_reverse_iterator rbegin() const {return (const_reverse_iterator(iterator(_start + _size)));}
            const_reverse_iterator rend()  const {return (const_reverse_iterator(iterator(_start)));}
            reverse_iterator rbegin() {return (reverse_iterator(end()));}
            reverse_iterator rend() {return (reverse_iterator(begin()));}
            size_type  capacity() const { return(_capacity);}
            size_type  max_size() const { return (_alloc.max_size());}
            bool    empty() const
            {
                if (_size == 0)
                    return (1);
                return (0);
            }
            reference  at(size_type n)
            {
                if (n > _size)
                    throw std::out_of_range("Out of Range error");
                return ((*this)[n]);
            }
            const_reference  at(size_type n) const
            {
                if (n > _size)
                    throw std::out_of_range("Out of Range error");
                return ((*this)[n]);
            }
            reference  front() {return(*_start);}
            const_reference  front() const {return(*_start);}
            reference  back() {return(*(_start+_size-1));}
            const_reference  back() const {return(*(_start+_size-1));}
            void    assign(size_type n, const value_type& val)
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_start + i);
                if (_capacity < n)
                {
                    _alloc.deallocate(_start, _capacity);
                    _start = _alloc.allocate(n);
                    _capacity = n;
                }
                _size = n;
			    std::uninitialized_fill(_start, _start + n, val);
            }
            template<class InputIterator>
            void assign (InputIterator first, InputIterator last,  typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type* = 0)
            {
                size_type i = ft::distance(first, last);
                this->clear();
				if (i <= _capacity)
				{
					while (first != last)
					{
						_alloc.construct(_start+_size , *first);
                        first++;
                        _size++;
					}
				}
				else
				{
					_alloc.deallocate(_start, this->capacity());
					_start = _alloc.allocate(i);
					_capacity = i;
					while (first != last)
					{
						_alloc.construct(_start+_size , *first);
                        first++;
                        _size++;
					}
				}
            }
            iterator insert(iterator position, const value_type& val)
            {
                if (_capacity == 0)
				    _capacity = 1;
                else if (_size == _capacity)
                    _capacity *= 2;
                pointer tmp = _alloc.allocate(_capacity);
                size_type len = position - begin();
                std::uninitialized_copy(begin(), position, tmp);
                _alloc.construct(tmp + len, val);
                std::uninitialized_copy(position, end(), tmp + len + 1);
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_start + i);
                _alloc.deallocate(_start, _size);
                _size++;
                _start = tmp;
                return (iterator(_start + len));
            }
            void    insert(iterator position, size_type n, const value_type& val)
            {
                size_type saved_capa = _capacity;
                if (_capacity == 0)
                    _capacity = n;
                else if (_capacity < _size + n && _size + n < _capacity * 2)
                    _capacity *= 2;
                else if (_size + n > _capacity * 2)
                    _capacity = _size + n;
                pointer tmp = _alloc.allocate(_capacity);
                difference_type len = position - begin();
                std::uninitialized_copy(begin(), position, tmp);
                std::uninitialized_fill(tmp+len, tmp+len+n, val);
                std::uninitialized_copy(position, end(), tmp+len+n);
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_start + i);
                _alloc.deallocate(_start, saved_capa);
                _start = tmp;
                _size += n;
            }
            template<class InputIterator>
            void    insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type* = 0)
            {
                difference_type d = ft::distance(first, last);
                size_type new_capa = _capacity;
                if (_capacity * 2 > _size + d)
                    new_capa = _capacity * 2;
                else if(_size + d > _capacity)
                    new_capa = _size + d; 
                pointer tmp = _alloc.allocate(new_capa);
                difference_type len = position - begin();
                std::uninitialized_copy(begin(), position, tmp);
                std::uninitialized_copy(first, last , tmp+len);
                std::uninitialized_copy(position, end(), tmp+len+d);
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_start + i);
                _alloc.deallocate(_start, _capacity);
                _size += d;
                _capacity = new_capa;
                _start = tmp;
            }
            void    resize(size_type n, value_type val = value_type())
            {
                if (n > _size)
                {
                    if (n > _capacity)
                    {
                        reserve(n);
                        for (; _size < n ; _size++)
                            _alloc.construct(_start + _size, val);
                    }
                    else
                    {
                        for (; _size < n ; _size++)
                            _alloc.construct(_start + _size, val);
                    }
                }   
                else
                {
                    for (size_type i = 0; i+n < _size; i++)
                        _alloc.destroy(_start+i+n);
                    _size = n;
                }
            }
            void    reserve(size_type n)
            {
                if (n <= _capacity)
				    return ;
                pointer tmp = _alloc.allocate(n);
                size_type i = 0;
                while (i < _size)
                {
                    _alloc.construct(tmp + i, *(_start + i));
                    i++;
                }
                if (_capacity > 0)
                    _alloc.deallocate(_start, _capacity);
                _start = tmp;
                _capacity = n;
            }
            iterator    erase(iterator position)
            {
                
                size_type i = 0;
                while (position + i != this->end())
                {
                    _alloc.destroy(position.base() + i);
                    _alloc.construct(position.base() + i, *(position + i + 1));
                    i++;
                }
                _alloc.destroy(position.base() + i);
                _size--;
                return (iterator(_start) + (position - this->begin()));
            }
            iterator    erase(iterator first, iterator last)
            {
                size_type i = 0;
                while (first + i != this->end())
                {
                    _alloc.destroy(first.base() + i);
                    _alloc.construct(first.base() + i, *(last + i));
                    i++;
                }
                size_type d = ft::distance(first, last);
                _size -= d;
                return (iterator(_start) + (first - this->begin()));
            }
            void    swap(vector& x)
            {

                pointer tmp_start = x._start;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;
				allocator_type tmp_alloc = x._alloc;

				x._start = this->_start;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._alloc = this->_alloc;

				this->_start = tmp_start;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_alloc = tmp_alloc;
            }
        private :
            Alloc       _alloc;
            pointer     _start;
            size_type   _size;
            size_type   _capacity;  
    };

    template<class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template<class T1, class T2, class Alloc>
    bool operator== (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template<class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template<class T1, class T2, class Alloc>
    bool operator!= (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template<class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T1, class T2, class Alloc>
    bool operator<  (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template<class T1, class T2, class Alloc>
    bool operator>  (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template<class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T1, class T2, class Alloc>
    bool operator<= (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T1, class T2, class Alloc>
    bool operator>= (const vector<T1,Alloc>& lhs, const vector<T2,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    void    swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y);}
    
    
}
#endif