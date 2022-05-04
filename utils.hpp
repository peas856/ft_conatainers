#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft 
{
  template <typename T> struct is_integral{static const bool value = false;};
  template <> struct is_integral<bool>{static const bool value = true;};
  template <> struct is_integral<char>{static const bool value = true;};
  template <> struct is_integral<char16_t>{static const bool value = true;};
  template <> struct is_integral<char32_t>{static const bool value = true;};
  template <> struct is_integral<wchar_t>{static const bool value = true;};
  template <> struct is_integral<signed char>{static const bool value = true;};
  template <> struct is_integral<short int>{static const bool value = true;};
  template <> struct is_integral<int>{static const bool value = true;};
  template <> struct is_integral<long int>{static const bool value = true;};
  template <> struct is_integral<long long int>{static const bool value = true;};
  template <> struct is_integral<unsigned char>{static const bool value = true;};
  template <> struct is_integral<unsigned short int>{static const bool value = true;};
  template <> struct is_integral<unsigned int>{static const bool value = true;};
  template <> struct is_integral<unsigned long int>{static const bool value = true;};
  template <> struct is_integral<unsigned long long int>{static const bool value = true;};

  template<bool B, class T = void> struct enable_if {};
  template<class T> struct enable_if<true, T> { typedef T type; };

  template<class InputIt1, class InputIt2>
  bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
  {
    while (first1 != last1) 
    {
      if (!(*first1 == *first2))
        return false;
      ++first1;
      ++first2;
    }
    return true;
  };

  template <class InputIt1, class InputIt2, class BinaryPredicate>
  bool equal ( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred)
  {
    while (first1!=last1) {
      if (!pred(*first1, *first2))
        return false;
      ++first1;
      ++first2;
    }
    return true;
  };

  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
  {
    while (first1!=last1)
    {
      if (first2==last2 || *first2<*first1) 
        return false;
      else if (*first1<*first2) 
        return true;
      ++first1;
      ++first2;
    }
    return (first2!=last2);
  };

  template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
  {
    while(first1 != last1)
    {
      if (comp(*first1, *first2)) 
        return true;
      else if (first2 == last2 || comp(*first2, *first1))
        return false;
      ++first1;
      ++first2;
    }
    return (first2 != last2);
  };

  template <class T1, class T2>
  struct pair
  {
    public:
      typedef T1 first_type;
      typedef T2 second_type;

      first_type first;
      second_type second;
      pair() : first() , second() 
      {}
      template< class U, class V>
      pair(const pair<U,V>& pr) : first(pr.first), second(pr.second)
      {}
      pair(const first_type& a, const second_type& b) : first(a), second(b) 
      {}
      pair& operator= (const pair& pr)
      {
        this->first = pr.first;
        this->second = pr.second;
        return (*this);
      }
  };
  template <class T1, class T2>
  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (lhs.first == rhs.first && lhs.second == rhs.second);
  }
  template <class T1, class T2>
  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (!(lhs == rhs));
  }
  template <class T1, class T2>
  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second));
  }
  template <class T1, class T2>
  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (rhs<lhs);
  }
  template <class T1, class T2>
  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return !(rhs<lhs);
  }
  template <class T1, class T2>
  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return !(lhs<rhs);
  }
  template<class T1, class T2>
  ft::pair<T1, T2> make_pair(T1 x, T2 y)
  {
    return (ft::pair<T1, T2>(x, y));
  }

  template <class Iterator> 
  struct iterator_traits
  {
      typedef typename Iterator::difference_type       difference_type;
      typedef typename Iterator::value_type            value_type;
      typedef typename Iterator::pointer               pointer;
      typedef typename Iterator::reference             reference;
      typedef typename Iterator::iterator_category     iterator_category;
  };

  template <class T>
  struct iterator_traits<T*>
  {
      typedef ptrdiff_t                       difference_type;
      typedef T                               value_type;
      typedef T*                              pointer;
      typedef T&                              reference;
      typedef std::random_access_iterator_tag  iterator_category;
  };

  template <class T>
  class iterator_traits<const T*>
  {
      typedef ptrdiff_t                       difference_type;
      typedef T                               value_type;
      typedef const T*                        pointer;
      typedef const T&                        reference;
      typedef std::random_access_iterator_tag  iterator_category;
  };

  template<class InputIterator>
  typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
  {
      typename iterator_traits<InputIterator>::difference_type len = 0;
      while (first != last)
      {
          first++;
          len++;
      }
      return (len);
  };

  template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  class iterator
  {
      public:
          typedef T           value_type;
          typedef Distance    difference_type;
          typedef Pointer     pointer;
          typedef Reference   reference;
          typedef Category    iterator_category;
  };

  template <class T>
  class bidirectional_iterator : ft::iterator<std::bidirectional_iterator_tag, T>
  {
      typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
      typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type            value_type;
      typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type       difference_type;
      typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer               pointer;
      typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference             reference;
      
      private:
        pointer _ptr;
  };
  template<class Iterator>
    class reverse_iterator
    {
        public :
            typedef Iterator iterator_type;
            typedef typename ft::iterator_traits<Iterator>::value_type value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer pointer;
            typedef typename ft::iterator_traits<Iterator>::reference reference;
            typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

        public :
            reverse_iterator() : _iter()
            {}
            explicit reverse_iterator (iterator_type it) : _iter(it)
            {}
            template<class iter>
            reverse_iterator(const reverse_iterator<iter> & rev_it) : _iter(rev_it.base()) 
            {}
            virtual ~reverse_iterator() {}
            iterator_type base() const
            {
                return (_iter);
            }
            reference operator*() const
            {
                iterator_type tmp = _iter;
                tmp--;
                return (*tmp);
            }
            reverse_iterator operator+ (difference_type n) const
            {
                return (reverse_iterator(_iter - n));
            }
            reverse_iterator& operator++()
            {
                --_iter;
                return (*this);
            }
            reverse_iterator  operator++(int)
            {
                reverse_iterator tmp = *this;
                --_iter;
                return (tmp);
            }
            reverse_iterator& operator+= (difference_type n)
            {
                _iter -= n;
                return (*this);
            }
            reverse_iterator operator- (difference_type n) const
            {
                return (reverse_iterator(_iter + n));
            }
            reverse_iterator& operator--()
            {
                ++_iter;
                return (*this);
            }
            reverse_iterator operator--(int) 
            {
                reverse_iterator tmp = *this;
                ++_iter;
                return (tmp);
            }
            reverse_iterator& operator-= (difference_type n)
            {
                _iter += n;
                return (*this);
            }
            pointer operator->() const 
            {
                return &(operator*());
            }
            reference operator[] (difference_type n) const
            {
                return (_iter[-n-1]);
            }
            private :
                iterator_type _iter;
    };
    
    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class It1, class It2>
    bool operator== (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() == rhs.base()); 
    }
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class It1, class It2>
    bool operator!= (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() != rhs.base()); 
    }
    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class It1, class It2>
    bool operator< (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() > rhs.base()); 
    }
    template <class Iterator>
    bool operator<=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class It1, class It2>
    bool operator<= (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() >= rhs.base()); 
    }
    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class It1, class It2>
    bool operator> (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() < rhs.base()); 
    }
    template <class Iterator>
    bool operator>=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class It1, class It2>
    bool operator>= (const reverse_iterator<It1>& lhs,const reverse_iterator<It2>& rhs) 
    { 
        return (lhs.base() <= rhs.base()); 
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
    template <class It1, class It2>
    reverse_iterator<It1> operator+ (typename reverse_iterator<It1>::difference_type n, const reverse_iterator<It2>& rev_it)
    {
        return (rev_it + n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {   
        return (rhs.base() - lhs.base());
    }
    template <class It1, class It2>
    typename reverse_iterator<It1>::difference_type operator- (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
    {
        return (rhs.base() - lhs.base());
    }
}
#endif