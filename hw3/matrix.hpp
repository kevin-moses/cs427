#ifndef __MATRIX_HPP__
#define __MATRIX_HPP___

#include <iostream>

namespace cs427_527 {
  template <typename T>
	class Matrix {
	public:
		/*
		A constructor Matrix(int h, int w) that creates a matrix of the given size. That size is then fixed for the life of the matrix.
		*/
		Matrix(int h, int w);
    /*
  	A copy constructor Matrix(const Matrix& other) that creates a deep copy of the given matrix, assuming that the elements' copy constructor and assignment operator create deep copies of the elements.
		*/
		Matrix(const Matrix& other);

    /*
    A move constructor Matrix(const Matrix&& other) that runs in O(1) time.		*/
		Matrix(const Matrix&& other);

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

	private:
    T *elements;
    void move(Matrix& toMove);
    void copy(const Matrix& toCopy);
    void deallocate();
    int capacity;
    int width;
    int height;
	};
}

#endif
