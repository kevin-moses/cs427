#ifndef __CS427527_MATRIX_HPP__
#define __CS427527_MATRIX_HPP___
#include <iostream>
#define FINAL

namespace cs427527 {
  template <typename T>
  class Matrix {
  public:
    class SkippingIterator {
    public:
      // * Creates an iterator in the given container starting at the given index and advancing the given number of elements per increment.
      SkippingIterator(T* t, int i, int st): target{t}{
        curr = i;
        step = st;
      }
      // an operator T& operator*() to return the element the iterator is currently positioned at;
      T& operator *() const {
        return target[curr];
      }
      // an operator iterator& operator++() to advance an iterator and return a reference to it, provided that it is not already positioned past the last element in the slice;
      SkippingIterator& operator++() {
        curr+=step;
        return *this;
      }
      SkippingIterator& operator=(const SkippingIterator rhs) {
        copy(rhs);
      }
      void copy(const SkippingIterator& toCopy) {
        target = toCopy.target;
        step = toCopy.step;
        curr = toCopy.curr;
      }
      // operators bool operator==(const iterator& rhs) and bool operator!=(const iterator& rhs) to compare two iterators to check whether they are positioned at the same element in the same matrix or both positioned past the last element in the same slice (both iterators must be the same type – both iterators or both const_iterators – but see below for graduate credit requirements);
      bool operator==(const SkippingIterator& rhs) const {
        return (target == (rhs.target) && (curr == rhs.curr));
      }
      bool operator!=(const SkippingIterator& rhs) const {
        return !(*this==rhs);
      }
    private:
      // pointer to 1d matrix array, current iterator and skip value
      T* target;
      int curr;
      int step;
    };
    class ConstSkippingIterator {
    public:
      ConstSkippingIterator(const T* t, int i, int st) : target{t}
      {
        curr = i;
        step = st;
      }
      ConstSkippingIterator& operator=(const ConstSkippingIterator rhs) const {
        copy(rhs);
      }
      void copy(const ConstSkippingIterator& toCopy) {
        target = toCopy.target;
        step = toCopy.step;
        curr = toCopy.curr;
      }

      const T& operator *() const {
        return target[curr];
      }

      ConstSkippingIterator& operator++() {

        this->curr += step;
        return *this;
      }

      bool operator==(const ConstSkippingIterator& rhs) const {
        return (target == (rhs.target)) && (curr == rhs.curr);
      }
      bool operator!=(const ConstSkippingIterator& rhs) const {
        return !(*this == rhs);
      }
    private:
      const T* target;
      int curr;
      int step;
    };

    using iterator = SkippingIterator;
    using const_iterator = ConstSkippingIterator;

    class SkipView {
    public:
      SkipView(T *t, int start, int skip, int l, int length) : target(t) {
        this->start = start;
        this->skip = skip;
        this->last = l;
        this->length = length;
      }
      /*
      an operator T& operator[](int i) that takes an index into the slice and returns a reference to the element at that index, or throws a std::out_of_range exception if the index is invalid;
      */
      T& operator[](int i);
      const T& operator[](int i) const;
      /*
      a method iterator begin() to return an iterator positioned at the beginning of the slice;
      */
      iterator begin() { return SkippingIterator{target, start, skip}; }
      const_iterator begin() const { return ConstSkippingIterator{target, start, skip};}
       /*
      a method iterator end() to return an iterator positioned past the last element in the slice;
      */
      iterator end() { return SkippingIterator{target, last, skip}; }
      const_iterator end() const {
        if (skip == 1) {
        }
        return ConstSkippingIterator{target, last, skip};}
      /*
      whatever is necessary to make the slices copy-constructable.
      */

    private:
      // pointer to 1d array, start value, end value, amount to skip by to get from start to end, and length of the slice
      T* target;
      int start;
      int skip;
      int last;
      int length;
    };
    class ConstSkipView {
    public:
      ConstSkipView(T* t, int start, int skip, int l, int length) : target(t) {
        this->start = start;
        this->skip = skip;
        this->last = l;
        this->length = length;
      }
      /*
      an operator T& operator[](int i) that takes an index into the slice and returns a reference to the element at that index, or throws a std::out_of_range exception if the index is invalid;
      */
      const T& operator[](int i) const;
      /*
      a method iterator begin() to return an iterator positioned at the beginning of the slice;
      */
      const_iterator begin() const { return ConstSkippingIterator{target, start, skip};}
       /*
      a method iterator end() to return an iterator positioned past the last element in the slice;
      */
      const_iterator end() const { return ConstSkippingIterator{target, last, skip};}
      /*
      whatever is necessary to make the slices copy-constructable.
      */

    private:
      T* target;
      int start;
      int skip;
      int last;
      int length;
    };
    using slice = SkipView;
    using const_slice = ConstSkipView;

    // YOU ARE HERE
    /*
    an operator slice operator[](int row) that takes a row index and returns a slice representing that row, or throws a std::out_of_range exception if the index is invalid;
    */
    slice operator[](int row);
    const_slice operator[](int row) const;

    /*
    a method slice column(int col) that takes a column index and returns a slice representing that column, or throws a std::out_of_range exception if the index is invalid;
    */
    slice column(int col);
    const_slice column(int col) const;

    /*
    A constructor Matrix(int h, int w) that creates a matrix of the given size. That size is then fixed for the life of the matrix.
    */
    Matrix(int height, int width);

    /*
    A copy constructor Matrix(const Matrix& other) that creates a deep copy of the given matrix, assuming that the elements' copy constructor and assignment operator create deep copies of the elements.
    */
    Matrix(const Matrix& other);

    /*
    A move constructor Matrix(const Matrix&& other) that runs in O(1) time.
    */
    Matrix(Matrix&& other);

    /*
    A copy assignment operator to create a deep copy of an object, assuming that the elements' copy constructor and assignment operator create deep copies of the elements..
    */
    Matrix<T>& operator=(const Matrix &rhs);

    /*
    A move assignment operator that runs in O(1) time.
    */
    Matrix<T>& operator=(Matrix&& rhs);

    /*
    Methods int height() and int width() to return the size in each dimension of a matrix.
    */

    int height() const;
    int width() const;

    /*
    A method T& at(int r, int c) that returns a reference to the element at the given location in the matrix, or throws a std::out_of_range exception if the row index or column index are invalid. There must also be a version of this method that works on const matrices, returning const references to the elements.
    */
    T& at(int r, int c);
    T& at(const int r, const int c) const;

    /*
    Matrix Destructor method which deallocates space
    */
    ~Matrix();

  private:
    // 1d dynamically allocated array of elements, capacity (width*height), move constructor, copy constructor, deconstructor
    T *elements;
    int capacity = 0;
    int w = 0;
    int h = 0;
    void move(Matrix& toMove);
    void copy(const Matrix& toCopy);
    void deallocate();
  };
}
#include "matrix.cpp"
#endif
