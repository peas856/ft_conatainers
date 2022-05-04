#ifndef MAP_HPP
#define MAP_HPP
#include "vector.hpp"
#include "utils.hpp"

namespace ft
{
    template <class T, class Node, class Compare, class tree>
    class map_iterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category         iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type                value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type           difference_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer                   pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference                 reference;
        public :
            map_iterator() : _ptr(), _tree() , _cmp(){}
            map_iterator(Node* node, const tree *tre) : _ptr(node), _tree(tre) {}
            map_iterator(map_iterator const&other) { *this = other; }
            ~map_iterator() {}
            Node* base() const { return (_ptr); }
            map_iterator& operator= (map_iterator const& x)
            {
                _ptr = x._ptr;
                _tree = x._tree;
                _cmp = x._cmp;
                return (*this);
            }
            operator map_iterator<const T, const Node, Compare, tree>() const
            {
                return map_iterator<const T, const Node, Compare, tree>(_ptr, _tree);
            }
            T* operator->() const
            {
                return (_ptr->data);
            }
            T& operator*() const
            {
                return (*_ptr->data);
            }
            map_iterator& operator++()
            {
                Node* p;
                Node* tmp;
                tmp = _tree->getRoot();
                if (_ptr == nullptr)
                {
                    while(tmp->left != nullptr)
                        tmp = tmp->left;
                    return (*this = map_iterator(tmp, _tree));
                }
                while (tmp->right != nullptr)
                    tmp = tmp->right;
                if (_ptr == tmp)
                    return (*this = map_iterator(nullptr, _tree));
                if (_ptr->right != nullptr)
                {
                    _ptr = _ptr->right;
                    while (_ptr->left != nullptr)
                        _ptr= _ptr->left;
                }
                else
                {
                    p = _ptr->parent;
                    while (p != nullptr && _ptr == p->right)
                    {
                        _ptr = p;
                        p = p->parent;
                    }
                    _ptr = p;
                }
                return (*this);
            }
            map_iterator operator++(int)
            {
                map_iterator tmp(*this);
                operator++();
                return (tmp);
            }
            map_iterator& operator--()
            {
                Node* p;
                Node* tmp;
                tmp = _tree->getRoot();
                if (_ptr == nullptr)
                {
                    while (tmp->right != nullptr)
                        tmp = tmp->right;
                    _ptr = tmp;
                }
                else
                {
                   if (_ptr->left != nullptr)
                    {
                        _ptr = _ptr->left;
                        while (_ptr->right != nullptr)
                            _ptr= _ptr->right;
                    }
                    else
                    {
                        p = _ptr->parent;
                        while (p != nullptr && _ptr == p->left)
                        {
                            _ptr = p;
                            p = p->parent;
                        }
                        _ptr = p;
                    }
                }
                return (*this);
            }
            map_iterator operator--(int)
            {
                map_iterator tmp(*this);
                operator--();
                return (tmp);
            }
            friend bool	operator==(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr == rhs._ptr); }
            friend bool	operator!=(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr != rhs._ptr); }
        private :
            Node            *_ptr;
            tree  const     *_tree;
            Compare         _cmp;
    };
    
    template<class T>
    class NODE
    {
        public :
            typedef T       value_type;
        
        public :
            int               balance_f;
            int               h;
            value_type     *data;
            NODE<T>        *left;
            NODE<T>        *right;
            NODE<T>        *parent;

        public :
            NODE() : h(0), data(nullptr), left(nullptr), right(nullptr), parent(nullptr)
            {}
            NODE(value_type val) : data(val), left(nullptr), h(0), right(nullptr), parent(nullptr)
            {}
            NODE(const NODE& node) : data(node.data), left(node.left), right(node.right), h(node.h), balance_f(node.balance_f), parent(node.parent)
            {}
            ~NODE()
            {};
            NODE& operator=(const NODE& node)
            {
                data = node.data;
                left = node.left;
                right = node.right;
                balance_f = node.balance_f;
                h = node.h;
                parent = node.parent;
                return (*this);
            }
    };
    template<class T>
    bool  operator== (const NODE<T>&lhs, const NODE<T>&rhs)
    {
        if (lhs->data == nullptr && rhs->data == nullptr)
            return true;
        return (lhs->data == rhs->data);
    }
    template<class T>
    bool operator!=(const NODE<T>&lhs, const NODE<T>&rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class AVL
    {
        public:
            typedef T value_type;
            typedef ft::NODE<const T> const_node;
            typedef typename Alloc::size_type    size_type;
            typedef Alloc pair_alloc;
            typedef typename Alloc::template rebind<ft::NODE<T> >::other node_alloc;
            typedef ft::map_iterator<T, ft::NODE<T>, Compare, AVL> iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::map_iterator<const T, const ft::NODE<T>, Compare, AVL> const_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename value_type::first_type key;
            typedef typename value_type::second_type value;

        public:
            AVL() : _root(nullptr), _size(0) {}
            AVL(const AVL &x) : _root(nullptr) 
            {
                *this = assign(x);
            }
            ~AVL() 
            {
            }
            
            AVL&    assign (AVL const& x)
            {
                deleteTree(_root);
                p_alloc = x.p_alloc;
                n_alloc = x.n_alloc;
                _comp = x._comp;
                for (const_iterator it = x.begin(); it != x.end(); it++)
                    insert(*it);
                return (*this);
            }
            void clear()
            {
                _size = 0;
            }
            size_type size() const
            { 
                return (_size); 
            }
            bool empty() const
            {

                return (_size==0);
            }
            void delTree()
            {
                deleteTree(_root);
            }
            void deleteTree(ft::NODE<T> * node)
            {
                if (node == nullptr)
                    return ;
                deleteTree(node->left);
                deleteTree(node->right);
                deleteNode(node);
                return ;
            }
            void deleteNode(ft::NODE<T> * node)
            {
                // if (node->parent->left == node)
                //     node->parent->left = nullptr;
                // else if (node->parent->right == node)
                //     node->parent->right = nullptr;
                p_alloc.destroy(node->data);
                p_alloc.deallocate(node->data, 1);
                node->data = nullptr;
                n_alloc.destroy(node);
                n_alloc.deallocate(node, 1);
                node = nullptr;
                _size--;
                return ;
            }
            iterator begin()
            {
                ft::NODE<T> *first = find(findMin(_root).first);
                return (iterator(first, this));
            }
            iterator end() 
            {
                return (iterator(nullptr, this)); 
            }
            const_iterator begin() const 
            { 
                ft::NODE<T> *first = find(findMin(_root).first);
                return (iterator(first, this));
            }
            const_iterator end() const 
            { 
                return (iterator(nullptr, this)); 
            }

            reverse_iterator rbegin() { return reverse_iterator(end()); }
            reverse_iterator rend() { return (reverse_iterator(begin())); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

            int height()
            {
                if (_root == nullptr)
                    return (0);
                return (height(_root) - 1);
            }

            bool insert(T value)
            {
                if (!contains(_root, value.first))
                {
                    _root = insert(_root, value);
                    _root->parent = nullptr;
                    return true;
                }
                return false;
            }

            bool remove(key val)
            {
                if (contains(_root, val))
                {
                    _root = remove(_root, val);
                    return true;
                }
                return false;
            }

            ft::NODE<T>* find(key val)
            {
                if (contains(_root, val))
                    return (find(_root, val));
                return nullptr;
            }
            ft::NODE<T>* find(key val) const
            {
                if (contains(_root, val))
                    return (find(_root, val));
                return nullptr;
            }

            iterator bound(key val, int op)
            {
                iterator it = this->begin();
                if (op == 1)
                {
                    while (it != this->end())
                    {
                        if (!(_comp(it->first, val)))
                            return (it);
                        it++;
                    }
                }
                else if (op == 2)
                {
                    while (it != this->end())
                    {
                        if ((_comp(val, it->first)))
                            return (it);
                        it++;
                    }
                }
                return (it);
            }
            
            const_iterator bound(const key val, int op) const
            {
                const_iterator it = this->begin();
                if (op == 1)
                {
                    while (it != this->end())
                    {
                        if (!(_comp(it->first, val)))
                            return (it);
                        it++;
                    }
                }
                else if (op == 2)
                {
                    while (it != this->end())
                    {
                        if ((_comp(val, it->first)))
                            return(it);
                        it++;
                    }
                }
                return (it);
            }
            size_t get_alloc() const { return (n_alloc.max_size()); }
            node_alloc get_allocator() const { return (n_alloc); }

            ft::NODE<T>* getRoot( void ) const 
            { 
                return (_root); 
            }
            
            bool contains(ft::NODE<T>* node, key k) const  // OK
            {
                if (node == nullptr)
                    return (false);
                bool cmp = _comp(node->data->first, k);
                bool cmp1 = _comp(k, node->data->first);
                if ( !cmp1 && !cmp)
                    return (true);
                if (!cmp)
                    return (contains(node->left, k));
                if (cmp)
                    return (contains(node->right, k));
                return (true);
            }
        private:
            int height(ft::NODE<T>* node)   // OK
            {
                if (node == nullptr)
                    return -1;
                int leftHeight = height(node->left) + 1;
                int rightHeight = height(node->right) + 1;
                if (leftHeight > rightHeight)
                    return leftHeight;
                return rightHeight;
            }
            ft::NODE<T>* insert(ft::NODE<T>* node, T val) 
            {
                if (node == nullptr)
                {
                    ft::NODE<T>* tmp = n_alloc.allocate(1);
                    n_alloc.construct(tmp);
                    tmp->data = p_alloc.allocate(1);
                    p_alloc.construct(tmp->data, val);
                    _size++;
                    return (tmp);
                }
                bool cmp = _comp(val.first, node->data->first);
                if (cmp)
                {
                    node->left = insert(node->left, val);
                    node->left->parent = node;
                }
                else if (!cmp)
                {
                    node->right = insert(node->right, val);
                    node->right->parent = node;
                }
                update(node);
                return (balance(node));
            }

            void update(ft::NODE<T>* node)
            {
                int left = -1;
                int right = -1;
                if (node->left != nullptr)
                    left = node->left->h;
                if (node->right != nullptr)
                    right = node->right->h;
                node->h = 1 + std::max(left, right);
                node->balance_f = right - left;
            }

            ft::NODE<T>* balance(ft::NODE<T>* node)
            {
                if (node->balance_f == -2)
                {
                    if (node->left->balance_f <= 0)
                        return llCase(node);
                    else
                        return lrCase(node);
                }
                else if (node->balance_f == 2)
                {
                    if (node->right->balance_f >= 0)
                        return rrCase(node);
                    else
                        return rlCase(node);
                }
                return node;
            }

            ft::NODE<T>* llCase(ft::NODE<T>* node) 
            { 
                return rightRotation(node); 
            }
            ft::NODE<T>* lrCase(ft::NODE<T>* node)
            {
                node->left = leftRotation(node->left);
                return llCase(node);
            }
            ft::NODE<T>* rrCase(ft::NODE<T>* node) 
            { 
                return leftRotation(node); 
            }
            ft::NODE<T>* rlCase(ft::NODE<T>* node)
            {
                node->right = rightRotation(node->right);
                return rrCase(node);
            }
            ft::NODE<T>* leftRotation(ft::NODE<T>* node)
            {
                ft::NODE<T>* tmp = node->right;
                node->right = tmp->left;
                tmp->left = node;
                treeReset(node, tmp);
                update(node);
                update(tmp);
                return tmp;
            }
            ft::NODE<T>* rightRotation(ft::NODE<T>* node)
            {
                ft::NODE<T>* tmp = node->left;
                node->left = tmp->right;
                tmp->right = node;
                treeReset(node, tmp);
                update(node);
                update(tmp);
                return tmp;
            }

            void treeReset(ft::NODE<T>* past, ft::NODE<T>* cur) const
            {
                if (!(past->parent))
                {
                    cur->parent = nullptr;
                    if (past->left)
                        past->left->parent = past;
                    if (past->right)
                        past->right->parent = past;
                    past->parent = cur;
                    return ;
                }
                cur->parent = past->parent;
                past->parent = cur;
                if (past->left)
                    past->left->parent = past;
                if (past->right)
                    past->right->parent = past;
            }

            void printmap(ft::NODE<T>* node, int level)
            {
                if (node)
                    std::cout <<"key:"<< node->data->first<<"level:"<< level << std::endl;   
                if (node->left)
                    printmap(node->left, level + 1);
                if (node->right)
                    printmap(node->right, level + 1);

            }

            ft::NODE<T>* remove(ft::NODE<T>* node, key val)
            {
                if (node == nullptr)
                    return nullptr;
                int cmp = _comp(val, node->data->first);
                bool cmp1 = _comp(node->data->first, val);
                if (!cmp && !cmp1)
                {
                    if (node->left == nullptr && node->right == nullptr)
                    {
                        deleteNode(node);
                        return nullptr;
                    }
                    else if (node->left == nullptr&& node->right!= nullptr)
                    {
                        ft::NODE<T>* tmp = node->right;
                        tmp->parent = node->parent;
                        deleteNode(node);
                        return tmp;
                    }
                    else if (node->right == nullptr&& node->left != nullptr)
                    {
                        ft::NODE<T>* tmp = node->left;
                        tmp->parent = node->parent;
                        deleteNode(node);
                        return tmp;
                    }
                    else
                    {
                        if (height(node->left) > height(node->right))
                        {
                            T Svalue = findMax(node->left);
                            p_alloc.destroy(node->data);
                            p_alloc.deallocate(node->data, 1);
                            node->data = p_alloc.allocate(1);
                            p_alloc.construct(node->data, Svalue);
                            node->left = remove(node->left, Svalue.first);
                        }
                        else
                        {
                            T Svalue = findMin(node->right);
                            p_alloc.destroy(node->data);
                            p_alloc.deallocate(node->data, 1);
                            node->data = p_alloc.allocate(1);
                            p_alloc.construct(node->data, Svalue);
                            node->right = remove(node->right, Svalue.first);
                        }
                    }
                }
                else if (cmp)
                    node->left = remove(node->left, val);
                else if (!cmp)
                    node->right = remove(node->right, val);
                update(node);
                return (balance(node));
            }

            ft::NODE<T>* find(ft::NODE<T>* node, key val)
            {
                if (node == nullptr)
                    return nullptr;
                bool cmp = _comp(node->data->first, val);
                if (!cmp && !(_comp(val, node->data->first)))
                    return node;
                if (!cmp)
                    return (find(node->left, val));
                else if (cmp)
                    return (find(node->right, val));
                return node;
            }

            ft::NODE<T>* find(ft::NODE<T>* node, key val) const
            {
                if (node == nullptr)
                    return nullptr;
                bool cmp = _comp(node->data->first, val);
                if (!cmp && !(_comp(val, node->data->first)))
                    return node;
                if (!cmp)
                    return (find(node->left, val));
                else if (cmp)
                    return (find(node->right, val));
                return node;
            }

            T findMin(ft::NODE<T>* node) 
            {
                if (node == nullptr)
                    return (ft::make_pair(key(), value()));
                while (node->left != nullptr)
                    node = node->left;
                return (*(node->data));
            }
            T findMax(ft::NODE<T>* node) 
            {
                if (node == nullptr)
                    return (ft::make_pair(key(), value()));
                while (node->right != nullptr)
                    node = node->right;
                return (*(node->data));
            }
            T findMin(ft::NODE<T>* node) const
            {
                if (node == nullptr)
                    return (ft::make_pair(key(), value()));
                while (node->left != nullptr)
                    node = node->left;
                return (*(node->data));
            }
            T findMax(ft::NODE<T>* node) const
            {
                if (node == nullptr)
                    return (ft::make_pair(key(), value()));
                while (node->right != nullptr)
                    node = node->right;
                return (*(node->data));
            }
        private:
            ft::NODE<T>* _root;
            node_alloc n_alloc;
            pair_alloc p_alloc;
            size_type _size;
            Compare _comp;
        };

    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public :
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef ft::pair<const key_type, mapped_type>       value_type;
            typedef Compare                                     key_compare;
            typedef class value_compare : std::binary_function<value_type,value_type,bool>
            {   
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            }    value_compare;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef ft::AVL<value_type, Compare, Alloc>         tree;
            typedef typename ft::AVL<value_type, Compare, Alloc>::iterator iterator;
            typedef typename ft::AVL<value_type, Compare, Alloc>::const_iterator   const_iterator;
            typedef typename ft::AVL<value_type, Compare, Alloc>::reverse_iterator reverse_iterator;
            typedef typename ft::AVL<value_type, Compare, Alloc>::const_reverse_iterator   const_reverse_iterator;
            typedef std::ptrdiff_t                              difference_type;
            typedef size_t                                      size_type;
        public :
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
            {}
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
            {   
                while (first != last){
                    _avl.insert(*first);
                    first++;
                }
            }
            map (const map& x){ *this = x; }
            ~map() 
            {
                _avl.delTree();
            }
            map& operator= (const map& x)
            {
                this->clear();
                this->_alloc = x._alloc;
                this->_cmp= x._cmp;
                this->_avl.assign(x._avl);
                return (*this);
            }
            iterator begin() { return(_avl.begin()); }
            const_iterator begin() const { return(_avl.begin()); }
            reverse_iterator rbegin() { return(_avl.rbegin()); }
            const_reverse_iterator rbegin() const { return(_avl.rbegin()); }
            iterator end() { return(_avl.end()); }
            const_iterator end() const { return(_avl.end()); }
            reverse_iterator rend() { return (_avl.rend()); }
            const_reverse_iterator rend() const { return (_avl.rend()); }
            bool empty() const {
                return (_avl.empty());
            }
            size_type size() const { return (_avl.size());}
            size_type max_size() const { return (_avl.get_alloc()); }
            key_compare key_comp() const { return (_cmp); }
            value_compare value_comp() const { return (value_compare(_cmp));}
            mapped_type& operator[] (const key_type& k)
            {
                    return  ((insert(ft::make_pair(k,mapped_type())).first)->second);
            }
            ft::pair<iterator, bool> insert(const value_type& x)
            {
                bool sec = _avl.insert(x);
                iterator first = iterator(_avl.find(x.first), &_avl);
                ft::pair<iterator, bool> ret = ft::make_pair(first, sec);
                return (ret);
            }
            iterator insert(iterator position, const value_type& x)
            {
                (void)position;
                _avl.insert(x);
                return (iterator(_avl.find(x.first), &_avl));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                for (; first != last; first++)
                    _avl.insert(*first);
                return ;
            }
            void erase(iterator position)
            {
                key_type x = position->first;
                _avl.remove(x);
                return ;
            }
            size_type erase(const key_type& x)
            {
                return (_avl.remove(x));
            }
            void erase(iterator first, iterator last)
            {
                iterator tmp;
                key_type x;
                while (first != last)
                {
                    tmp = first;
                    first++;
                    if (first == last)
                    {
                        erase(tmp);
                        break;
                    }
                    x = (*first).first;
                    erase(tmp);
                    first = find(x);
                }
            }
            void swap(map& x)
            {
                std::swap(this->_alloc, x._alloc);
                std::swap(this->_cmp, x._cmp);
                tree          tmp_avl;

                tmp_avl = x._avl;
                x._avl = _avl;
                _avl = tmp_avl;

                return ;
            }
            void clear() 
            { 
                this->erase(this->begin(), this->end());
            }
            iterator find(const key_type& x)
            {
                return (iterator(_avl.find(x),&_avl));
            }
            const_iterator find(const key_type& x) const
            {
                return (iterator(_avl.find(x), &_avl));
            }

            size_type count(const key_type& x) const
            {
                return (_avl.contains(_avl.getRoot(), x));
            }

            iterator lower_bound(const key_type& x)
            {
                return (_avl.bound(x, 1));
            }
            const_iterator lower_bound(const key_type& x) const
            {
                return (_avl.bound(x, 1));
            }

            iterator upper_bound(const key_type& x)
            {
                return (_avl.bound(x, 2));
            }
            const_iterator upper_bound(const key_type& x) const
            {
                return (_avl.bound(x, 2));
            }
            
            ft::pair<iterator,iterator> equal_range(const key_type& x)
            {
                ft::pair<iterator,iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
                return (ret);
            }
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const
            {
                ft::pair<const_iterator,const_iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
                return (ret);
            }

            allocator_type get_allocator() const { return (_avl.get_allocator()); }
        private :
            tree                                    _avl;
            allocator_type                          _alloc;
            key_compare                             _cmp;
    };
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator> ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=  ( const map<Key,T,Compare,Alloc>& lhs,  const map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,  const map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}
#endif