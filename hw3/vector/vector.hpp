#ifndef __CS427527_VECTOR_HPP__
#define __CS427527_VECTOR_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include <utility>
namespace cs427_527
{

  /**
   * An iterable random-access container.
   *
   * @param T a printable type
   */
  template <typename T>
  class Vector
  {
  public:
    /**
     * An iterator that advances through a vector a fixed number of
     * elements per increment.
     */
    class SkippingIterator
    {
    public:
      /**
       * Creates an iterator in the given container starting at the
       * given index and advancing the given number of elements per increment.
       *
       * @param t a vector
       * @param i an index into that vector, or the size of the vector
       * @param st a positive integer
       */
      SkippingIterator(Vector<T>& t, int i, int st) : target{t}
      { curr = i; step = st; }

      /**
       * Returns a reference to the element this iterator is positioned at.
       *
       * @return a reference to the element this iterator is positioned at
       */
      T& operator *() const { return target[curr]; }

      /**
       * Advances this iterator.
       *
       * @return a reference to this iterator
       */
      SkippingIterator& operator++() { curr += step; return *this; }

      /**
       * Determines if this iterator is positioned at the same
       * element in the same container as the given iterator.
       *
       * @param rhs an iterator
       * @return true if and only if this iterator is positioned at the
       * same element in the same container as rhs
       */
      bool operator==(const SkippingIterator& rhs) const
      { return &target == &(rhs.target) && curr == rhs.curr; }

      /**
       * Determines if this iterator is positioned at the same
       * element in the same container as the given iterator.
       *
       * @param rhs an iterator
       * @return false if and only if this iterator is positioned at the
       * same element in the same container as rhs
       */
      bool operator!=(const SkippingIterator& rhs) const
      { return !(*this == rhs); }

    private:
      /**
       * The container this iterator iterates through.
       */
      Vector<T>& target;

      /**
       * The current index of this iterator in target.
       */
      int curr;

      /**
       * The amount to advance this iterator by on each increment.
       */
      int step;
    };

    /**
     * An read-only iterator that advances through a vector a fixed number of
     * elements per increment.
     */
    class ConstSkippingIterator
    {
    public:
      /**
       * Creates an iterator in the given container starting at the
       * given index and advancing the given number of elements per increment.
       *
       * @param t a vector
       * @param i an index into that vector, or the size of the vector
       * @param st a positive integer
       */
      ConstSkippingIterator(const Vector<T>& t, int i, int st) : target{t}
      { curr = i; step = st; }

      /**
       * Returns a reference to the element this iterator is positioned at.
       *
       * @return a reference to the element this iterator is positioned at
       */
      const T& operator *() const { return target[curr]; }

      /**
       * Advances this iterator.
       *
       * @return a reference to this iterator
       */
      ConstSkippingIterator& operator++() { curr += step; return *this; }

      /**
       * Determines if this iterator is positioned at the same
       * element in the same container as the given iterator.
       *
       * @param rhs an iterator
       * @return true if and only if this iterator is positioned at the
       * same element in the same container as rhs
       */
      bool operator==(const ConstSkippingIterator& rhs) const { return &target == &(rhs.target) && curr == rhs.curr; }

      /**
       * Determines if this iterator is positioned at the same
       * element in the same container as the given iterator.
       *
       * @param rhs an iterator
       * @return false if and only if this iterator is positioned at the
       * same element in the same container as rhs
       */
      bool operator!=(const ConstSkippingIterator& rhs) const { return !(*this == rhs); }

    private:
      /**
       * The container this iterator iterates through.
       */
      const Vector<T>& target;

      /**
       * The current index of this iterator in target.
       */
      int curr;

      /**
       * The amount to advance this iterator by on each increment.
       */
      int step;
    };

    using iterator = SkippingIterator;
    using const_iterator = ConstSkippingIterator;

    /**
     * A view into a container that sees every other element.
     * Modifications to the elements seen through the view are
     * made to the elements in the underlying container.
     */
    class SkipView
    {
    public:
      /**
       * Creates a view of the given container that sees every other
       * element starting with the one at the given index.
       *
       * @param t a vector
       * @param start an index into that container
       */
      SkipView(Vector<T>& t, int start) : target(t) { this->start = start; }

      /**
       * Returns an iterator positioned at the beginning of this view.
       *
       * @return an iterator positioned at the beginning of this view
       */
      iterator begin() { return SkippingIterator{target, start, 2}; }

      /**
       * Returns an iterator positioned at the end of this view.
       *
       * @return an iterator positioned at the end of this view
       */
      iterator end() { return SkippingIterator{target, target.size() + (start % 2 != target.size() % 2 ? 1 : 0), 2}; }

      /**
       * Returns a read-only iterator positioned at the beginning of this view.
       *
       * @return a read-only iterator positioned at the beginning of this view
       */
      const_iterator begin() const
      { return ConstSkippingIterator{target, start, 2}; }

      /**
       * Returns a read-only iterator positioned at the end of this view.
       *
       * @return a read-only iterator positioned at the end of this view
       */
      const_iterator end() const
      { return ConstSkippingIterator{target, target.size() + (start % 2 != target.size() % 2 ? 1 : 0), 2}; }

      /**
       * Returns a reference to the given element in this view.
       *
       * @param i the index of an element in this view
       * @return a reference to that element
       */
      T& operator[](int i);

      /**
       * Returns a reference to the given element in this view.
       *
       * @param i the index of an element in this view
       * @return a reference to that element
       */
      const T& operator[](int i) const;

    private:
      /**
       * The container this view sees.
       */
      Vector<T>& target;

      /**
       * The index of the first element this view sees.
       */
      int start;
    };

    /**
     * A read-only view into a container that sees every other element.
     * Modifications to the elements seen through the view are
     * made to the elements in the underlying container.
     */
    class ConstSkipView
    {
    public:
      /**
       * Creates a read-only view of the given container that sees every other
       * element starting with the one at the given index.
       *
       * @param t a vector
       * @param start an index into that container
       */
      ConstSkipView(const Vector<T>& t, int start) : target(t)
      { this->start = start; }

      /**
       * Returns a read-only iterator positioned at the beginning of this view.
       *
       * @return a read-only iterator positioned at the beginning of this view
       */
      const_iterator begin() const
      { return ConstSkippingIterator{target, start, 2}; }

      /**
       * Returns a read-only iterator positioned at the end of this view.
       *
       * @return a read-only iterator positioned at the end of this view
       */
      const_iterator end() const
      { return ConstSkippingIterator{target, target.size() + (start % 2 != target.size() % 2 ? 1 : 0), 2}; }

      /**
       * Returns a reference to the given element in this view.
       *
       * @param i the index of an element in this view
       * @return a reference to that element
       */
      const T& operator[](int i) const;

    private:
      /**
       * The container this view sees.
       */
      Vector<T>& target;

      /**
       * The index of the first element this view sees.
       */
      int start;
    };

    using skip_view = SkipView;
    using const_skip_view = ConstSkipView;

    /**
     * Creates an empty vector.
     */
    Vector();

    /**
     * Creates an vector containing copies of the elements in the given vector.
     *
     * @param toCopy a vector
     */
    Vector(const Vector& toCopy);

    /**
     * Creates a vector by moving elements from the given vector and
     * emptying that vector.
     *
     * @param toMove a vector
     */
    Vector(Vector&& toMove);

    /**
     * Destroys this vector.
     */
    ~Vector();

    /**
     * Removes the elements in this vector and replaces them with
     * copies of elements from the given vector.
     *
     * @param rhs a vector
     * @return a reference to this vector
     */
    Vector& operator=(const Vector& rhs);

    /**
     * Removes the elements in this vector and replaces them by moving
     * the elements from the given vector.  That vector is emptied.
     *
     * @param rhs a vector
     * @return a reference to this vector
     */
    Vector& operator=(Vector&& rhs);

    /**
     * Returns a reference to the element at the given index in this vector.
     *
     * @param i the index of an element in this vector
     * @return a reference to that element
     */
    T& operator[](int i);

    /**
     * Returns a reference to the element at the given index in this vector.
     *
     * @param i the index of an element in this vector
     * @return a reference to that element
     */
    const T& operator[](int i) const;

    /**
     * Returns the number of elements in this vector.
     *
     * @return the number of elements in this vector
     */
    int size() const;

    /**
     * Adds the given element to the end of this vector.
     *
     * @param T an element
     */
    void push_back(const T& item);

    /**
     * Returns a printable representation of this vector.
     *
     * @return a printable representation of this vector
     */
    std::string toString() const;

    /**
     * Returns an iterator positioned at the first element in this vector.
     *
     * @return an iterator positioned at the first element in this vector
     */
    iterator begin();

    /**
     * Returns an iterator positioned past the last element in this vector.
     *
     * @return an iterator positioned past the last element in this vector
     */
    iterator end();

    /**
     * Returns a read-only iterator positioned at the first element in this
     * vector.
     *
     * @return a read-only iterator positioned at the first element in this
     * vector
     */
    const_iterator begin() const;

    /**
     * Returns a read-only iterator positioned at past the last element in this
     * vector.
     *
     * @return a read-only iterator positioned past the last element in this
     * vector
     */
    const_iterator end() const;

    /**
     * Returns a view of the elements at even indices in this vector.
     *
     * @return a view of the elements at even indices in this vector
     */
    skip_view evens();

    /**
     * Returns a view of the elements at odd indices in this vector.
     *
     * @return a view of the elements at odd indices in this vector
     */
    skip_view odds();

    /**
     * Returns a read-only view of the elements at even indices in this vector.
     *
     * @return a read-only view of the elements at even indices in this vector
     */
    const_skip_view evens() const;

    /**
     * Returns a read-only view of the elements at odd indices in this vector.
     *
     * @return a read-only view of the elements at odd indices in this vector
     */
    const_skip_view odds() const;

  private:
    void deallocate();

    void copy(const Vector& toCopy);

    void move(Vector& toMove);

    void embiggen();

    int capacity;
    int count;
    T* elements;

    const int INITIAL_CAPACITY = 2;
  };

  /**
   * Outputs the given container to the given stream.
   *
   * @param v a vector
   * @param os an output stream
   * @return that output stream
   */
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& v);

}

#include "vector.cpp"

#endif
