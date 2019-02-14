#include <iostream>
using std::cout;
using std::endl;
namespace cs427527 {
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
      // elements{};
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
    Matrix<T>::Matrix(const Matrix&& other) {
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
    /*
    A method T& at(int r, int c) that returns a reference to the element at the given location in the matrix, or throws a std::out_of_range exception if the row index or column index are invalid. There must also be a version of this method that works on const matrices, returning const references to the elements.
    */
    template<typename T>
    T& Matrix<T>::at(int r, int c) {
      int index = (r*w) + (c);  
      return elements[index];
    }
    template<typename T>
    T& Matrix<T>::at(const int r, const int c) const {
      int index = (r)*w + (c);
      return elements[index];
    }

    /*
    Copy constructor -- creating a deep copy
    */
    template<typename T>
    void Matrix<T>::copy(const Matrix& toCopy) {
      capacity = toCopy.capacity;

      // alloc uninitialized space with global new
      elements = (T*)::operator new(capacity*sizeof(T));
      for (int i = 0; i < capacity; i++) {
        new (elements + i) T{toCopy.elements[i]};
      }
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
    Move constructor --reroutes pointers
    */
    template<typename T>
    void Matrix<T>::move(Matrix& toMove) {
      // switch pointers
      capacity = toMove.capacity;
      elements = toMove.elements;
      // set other pointers null
      toMove.capacity = 0;
      toMove.elements = nullptr;
    }

    /*
    Matrix Destructor method which deallocates space 
    */
    template<typename T>
    Matrix<T>::~Matrix() {
      deallocate();
    }
    
}
