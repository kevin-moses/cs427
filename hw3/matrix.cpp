#include <iostream>
using std::cout;
using std::endl;
namespace cs427527 {

    /*
    an operator slice operator[](int row) that takes a row index and returns a slice representing that row, or throws a std::out_of_range exception if the index is invalid;
    */
    template<typename T>
    typename Matrix<T>::slice Matrix<T>::operator[](int row)
    {
      if (row > this->w || row < 0) {
        throw std::out_of_range ("df");
      }
      int start = this->w * row;
      int end = (this->w) * (row+1);
      return SkipView{this->elements, start, 1, end, this->w};
    }
    template<typename T>
    typename Matrix<T>::const_slice Matrix<T>::operator[](int row) const
    {
      if (row > this->w || row < 0) {
        throw std::out_of_range ("sf");
      }
      int start = this->w * row;
      int end = (this->w) * (row+1);
      return ConstSkipView{this->elements, start, 1, end, this->w};
    }

    /*
    a method slice column(int col) that takes a column index and returns a slice representing that column, or throws a std::out_of_range exception if the index is invalid; and
    */
    template<typename T>
    typename Matrix<T>::slice Matrix<T>::column(int col) {
      if (col > this->w || col < 0) {
        throw std::out_of_range ("af");
      }
      int step = this->w;
      int end = col + (this->w * (this->h));
      return SkipView{this->elements, col, step, end, this->h};
    }
    template<typename T>
    typename Matrix<T>::const_slice Matrix<T>::column(int col) const {
      if (col > this->w || col < 0) {
        throw std::out_of_range ("we");
      }
      int step = this->w;
      int end = col + (this->w * (this->h));
      return ConstSkipView{this->elements, col, step, end, this->h};
    }


    /*
    an operator T& operator[](int i) that takes an index into the slice and returns a reference to the element at that index, or throws a std::out_of_range exception if the index is invalid;
    */
    template<typename T>
    T& Matrix<T>::SkipView::operator[](int i) {
      if (i > length ) {
        throw std::out_of_range ("out of fe");
      }
      return target[start + (skip*i)];
    }
    template<typename T>
    const T& Matrix<T>::SkipView::operator[](int i) const {
      if (i > length ) {
        throw std::out_of_range ("out we range");
      }
      return target[start + (skip*i)];
    }
    template<typename T>
    const T& Matrix<T>::ConstSkipView::operator[](int i) const {
      if (i > length ) {
        throw std::out_of_range ("as of range");
      }
      return target[start + (skip *i)];
    }

    /*
    A constructor Matrix(int h, int w) that creates a matrix of the given size. That size is then fixed for the life of the matrix.
    */
		template<typename T>
    Matrix<T>::Matrix(int height, int width) {
      capacity = height*width;
      w = width;
      h = height;
      // elements = new T[capacity]{};
      elements = (T*)::operator new(sizeof(T)*capacity);
      for (int i = 0; i < capacity; i++) {
        (elements[i]) = T{};
      }
    }
    /*
  	A copy constructor Matrix(const Matrix& other) that creates a deep copy of the given matrix, assuming that the elements' copy constructor and assignment operator create deep copies of the elements.
		*/
		template<typename T>
    Matrix<T>::Matrix(const Matrix& other) {
      copy(other);
    }
    /*
    A move constructor Matrix(const Matrix&& other) that runs in O(1) time.		*/
		template<typename T>
    Matrix<T>::Matrix(Matrix&& other) {
      move(other);
    }

    /*
		A copy assignment operator to create a deep copy of an object, assuming that the elements' copy constructor and assignment operator create deep copies of the elements..
		*/
		template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix &rhs) {
      if (this!= &rhs) {
        deallocate();
        copy(rhs);
      }

      return *this;
    }
    /*
    A move assignment operator that runs in O(1) time.
    */
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) {
      if (this != &rhs) {
        deallocate();
        move(rhs);
      }
      return *this;
    }
    /*
		Methods int height() and int width() to return the size in each dimension of a matrix.
		*/
		template<typename T>
    int Matrix<T>::height() const {
      return h;
    }
    template<typename T>
    int Matrix<T>::width() const {
      return w;
    }
    // getting location via 2d array

    /*
    A method T& at(int r, int c) that returns a reference to the element at the given location in the matrix, or throws a std::out_of_range exception if the row index or column index are invalid. There must also be a version of this method that works on const matrices, returning const references to the elements.
    */
    template<typename T>
    T& Matrix<T>::at(int r, int c) {
      if (r > h || c > w) {
        throw std::out_of_range ("index wrong");
      }
      int index = (r*w) + (c);
      return elements[index];
    }
    template<typename T>
    T& Matrix<T>::at(const int r, const int c) const {
      if (r > h || c > w) {
        throw std::out_of_range ("index wrong");
      }
      int index = (r)*w + (c);
      return elements[index];
    }

    /*
    Copy constructor -- creating a deep copy
    */

    template<typename T>
    void Matrix<T>::copy(const Matrix& toCopy) {
      capacity = toCopy.capacity;
			w = toCopy.w;
			h = toCopy.h;
      // alloc uninitialized space with global new
      elements = (T*)::operator new(capacity*sizeof(T));
      for (int i = 0; i < capacity; i++) {
        new (elements + i) T{toCopy.elements[i]};
      }
    }
		/*
		Move constructor --reroutes pointers
		*/
		template<typename T>
		void Matrix<T>::move(Matrix& toMove) {
			// switch pointers
			capacity = toMove.capacity;
			elements = toMove.elements;
			w = toMove.w;
			h = toMove.h;
			// set other pointers null
			toMove.capacity = 0;
			toMove.w = 0;
			toMove.h = 0;
			toMove.elements = nullptr;
		}

    /*
    Deallocate memory from 'this'
    */
    template<typename T>
    void Matrix<T>::deallocate() {
      // call destructor manually
      for (int i = 0; i < capacity; i++) {
        elements[i].~T();
      }
      // global delete to free space to match allocation with global new
      ::operator delete(elements);
    }


    /*
    Matrix Destructor method which deallocates space
    */
    template<typename T>
    Matrix<T>::~Matrix() {
      deallocate();
    }

}
