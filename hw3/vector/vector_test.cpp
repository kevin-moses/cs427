#include <iostream>
#include <vector>

#include "vector.hpp"

// a slightly shorter name of a vector of ints
using ivector427527 = cs427_527::Vector<int>;

/**
 * Prints the contents of the given vector of ints to standard output.
 */
void printVector(const ivector427527& v);

/**
 * Prints the contents of the given view to standard output.
 */
void printView(const ivector427527::skip_view& v);

/**
 * Prints the contents of the given container/view to standard output.
 *
 * @param Container an iterable container or view type with printable elements
 * @param c the container to print
 */
template<typename Container>
void printContainer(const Container& c);

/**
 * Sets the element the given iterator is positioned at to the
 * given value.
 */
template<typename Iter, typename T>
void setViaIterator(const Iter& i, const T& value);

int main(int argc, char **argv)
{
  // create a vector containing 0, ..., 9
  ivector427527 v1;
  for (int i = 0; i < 10; i++)
    {
      v1.push_back(i);
    }

  // create another such vector...
  ivector427527 v2;
  for (int i = 0; i < 9; i++)
    {
      v2.push_back(i);
    }
  // ...and then set each element to the square of what it used to be
  for (auto i = v2.begin(); i != v2.end(); ++i)
    {
      *i = *i * *i;
    }

  // print the vectors
  std::cout << "=== Two vectors ===" << std::endl;
  printVector(v1);
  printVector(v2);
  std::cout << "=== Evens and Odds ===" << std::endl;
  printView(v2.evens());
  printView(v2.odds());
  // we shouldn't need to write two separate functions for that -- template
  // functions to the rescue!
  std::cout << "=== Using template function ===" << std::endl;
  printContainer(v1);
  printContainer(v2);
  printContainer(v2.evens());
  printContainer(v2.odds());

  // initialize a STL vector using initializer list
  std::vector<int> v = {1, 2, 3};
  // note that the element a const iterator is at can be modified!
  // (const-ness for STL iterators refers to whether the iterators
  // can be moved from where they are; an iterator through a container
  // of const elements is a const_iterator)
  setViaIterator(v.begin(), 42);
  std::cout << "=== STL vector after setting through const iterator ===" << std::endl;
  printContainer(v);

  // ours work the same way as the STL's (but we haven't implemented
  // initialization via initializer lists; and note that unlike this
  // vector implementation, the Assignment #3 Matrix const iterators should
  // not allow modification of the element they are positioned at
  // (I have come to regret that decision)
  cs427_527::Vector<int> w;
  w.push_back(1);
  w.push_back(2);
  w.push_back(3);
  std::cout << "=== Ours after setting through const iterator ===" << std::endl;
  setViaIterator(w.begin(), 42);
  printContainer(w);
}

void printView(const ivector427527::skip_view& view)
{
  std::cout << "[";
  for (auto i = view.begin(); i != view.end(); ++i)
    {
      std::cout << " " << *i;
    }
  std::cout << " ]" << std::endl;
}

void printVector(const ivector427527& v)
{
  std::cout << "[";
  for (auto i = v.begin(); i != v.end(); ++i)
    {
      std::cout << " " << *i;
    }
  std::cout << " ]" << std::endl;
}

// did you notice how the bodies of the above two functions were
// exactly the same?  how about we have the compiler write them for
// us?
template<typename Container>
void printContainer(const Container& c)
{
  std::cout << "[";
  for (auto i = c.begin(); i != c.end(); ++i)
    {
      std::cout << " " << *i;
    }
  std::cout << " ]" << std::endl;
}

template<typename Iter, typename T>
void setViaIterator(const Iter& i, const T& value)
{
  *i = value;
}