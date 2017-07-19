#include <iterator>
#include <cassert>

template < typename ForwardIterator >
ForwardIterator my_advanceImpl(ForwardIterator it, int n, std::forward_iterator_tag)
{
    assert(n > -1 && "Can only move a forward iterator forward!");
    while (n--) ++it;
    return it;
}

template < typename RandomAccessIterator >
RandomAccessIterator my_advanceImpl(RandomAccessIterator it, int n, std::random_access_iterator_tag)
{
    it += n;
    return it;
}

template < typename Iterator >
Iterator my_advance(Iterator it, int n)
{
    using tag = typename std::iterator_traits<Iterator>::iterator_category;
    // We're doing this silly and not allowing input iterators, we should make a readable message
    static_assert(std::is_base_of<std::input_iterator_tag, tag>::value, "Can only advance ForwardIterators and their refinements.");

    return my_advanceImpl(it, n, tag{});
}

/*

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

 template < class Iterator > struct iterator_traits {
  typedef typename Iterator::value_type        value_type ;
  typedef typename Iterator::difference_type   difference_type ;
  typedef typename Iterator::pointer           pointer ;
  typedef typename Iterator::reference         reference ;
  typedef typename Iterator::iterator_category iterator_category ;
};

template < class T > struct iterator_traits <T* > {
  typedef T                          value_type ;
  typedef ptrdiff_t                  difference_type ;
  typedef T*                         pointer ;
  typedef T&                         reference ;
  typedef random_access_iterator_tag iterator_category ;
};

template < class T > struct iterator_traits <const T* > {
  typedef T                          value_type ;
  typedef ptrdiff_t                  difference_type ;
  typedef const T*                   pointer ;
  typedef const T&                   reference ;
  typedef random_access_iterator_tag iterator_category ;
};


 Defining own iterators :

 template < class Category , class Value , class Distance = ptrdiff_t ,
           class Pointer = Value*, class Reference = Value&>
struct iterator {
  typedef Category  category ;
  typedef Value     value_type ;
  typedef Distance  difference_type ;
  typedef Pointer   pointer ;
  typedef Reference reference ;
}

 struct my_iterator
    : std::iterator<forward_iterator_tag, int>
{
  ...
}
 */