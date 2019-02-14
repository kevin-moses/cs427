namespace cs427_527
{
  // we defined these in the .cpp just to show how it would be done
  
  template<typename T>
  T& Vector<T>::SkipView::operator[](int i)
  {
    return target[start + 2 * i];
  }
  
  template<typename T>
  const T& Vector<T>::SkipView::operator[](int i) const
  {
    return target[start + 2 * i];
  }

  template<typename T>
  const T& Vector<T>::ConstSkipView::operator[](int i) const
  {
    return target[start + 2 * i];
  }

  template<typename T>
  Vector<T>::Vector()
  {
    capacity = INITIAL_CAPACITY;
    count = 0;
    elements = (T*)::operator new(sizeof(T) * capacity);
  }
      
  template<typename T>
  Vector<T>::Vector(const Vector& toCopy)
  {
    copy(toCopy);
  }
      
  template<typename T>
  Vector<T>::Vector(Vector&& toMove)
  {
    move(toMove);
  }
      
  template<typename T>
  Vector<T>::~Vector()
  {
    deallocate();
  }

  template<typename T>
  Vector<T>& Vector<T>::operator=(const Vector& rhs)
  {
    if (this != &rhs)
      {
	deallocate();
	copy(rhs);
      }
    return *this;
  }
      
  template<typename T>
  Vector<T>& Vector<T>::operator=(Vector&& rhs)
  {
    if (this != &rhs)
      {
	deallocate();
	move(rhs);
      }

    return *this;
  }
      
  template<typename T>
  T& Vector<T>::operator[](int i)
  {
    return elements[i];
  }
      
  template<typename T>
  const T& Vector<T>::operator[](int i) const
  {
    return elements[i];
  }
      
  template<typename T>
  int Vector<T>::size() const
  {
    return count;
  }
      
  template<typename T>
  void Vector<T>::push_back(const T& item)
  {
    if (count == capacity)
      {
	embiggen();
      }
	
    new (elements + count) T(item);
    count++;
  }
      
  template<typename T>
  std::string Vector<T>::toString() const
  {
    std::ostringstream out;
	  
    out << "[";
    for (int i = 0; i < count; i++)
      {
	if (i > 0)
	  {
	    out << ", ";
	  }
	out << elements[i];
      }
    out << "]";
	  
    return out.str();
  }

  template<typename T>
  typename Vector<T>::iterator Vector<T>::begin()
  {
    return SkippingIterator{*this, 0, 1};
  }

  template<typename T>
  typename Vector<T>::iterator Vector<T>::end()
  {
    return SkippingIterator{*this, count, 1};
  }

  template<typename T>
  typename Vector<T>::const_iterator Vector<T>::begin() const
  {
    return ConstSkippingIterator{*this, 0, 1};
  }
  template<typename T>
  typename Vector<T>::const_iterator Vector<T>::end() const
  {
    return ConstSkippingIterator{*this, count, 1};
  }

  template<typename T>
  typename Vector<T>::skip_view Vector<T>::evens()
  {
    return SkipView{*this, 0};
  }

  template<typename T>
  typename Vector<T>::skip_view Vector<T>::odds()
  {
    return SkipView{*this, 1};
  }

  template<typename T>
  typename Vector<T>::const_skip_view Vector<T>::evens() const
  {
    return ConstSkipView{*this, 0};
  }

  template<typename T>
  typename Vector<T>::const_skip_view Vector<T>::odds() const
  {
    return ConstSkipView{*this, 1};
  }

  /**
   * Destroys the elements in this vector and releases the array used
   * to hold them.
   */
  template<typename T>
  void Vector<T>::deallocate()
  {
    for (int i = 0; i < count; i++)
      {
	elements[i].~T();
      }
    ::operator delete(elements);
  }

  /**
   * Copies the elements from the given vector to this one.
   */
  template<typename T>
  void Vector<T>::copy(const Vector& toCopy)
  {
    capacity = toCopy.capacity;
    count = toCopy.count;
	
    elements = (T*)::operator new(capacity * sizeof(T));
    for (int i = 0; i < count; i++)
      {
	new (elements + i) T{toCopy.elements[i]};
      }
  }

  /**
   * Moves the elements from the given vector to this one.
   */
  template<typename T>
  void Vector<T>::move(Vector& toMove)
  {
    capacity = toMove.capacity;
    count = toMove.count;
    elements = toMove.elements;
	
    toMove.capacity = 0;
    toMove.count = 0;
    toMove.elements = nullptr;
  }

  /**
   * Resizes the array held by this container.
   */
  template<typename T>
  void Vector<T>::embiggen()
  {
    int newCapacity = capacity * 2;
    T *larger = (T*)::operator new(newCapacity * sizeof(T));
    for (int i = 0; i < count; i++)
      {
	new (larger + i) T{std::move(elements[i])};
      }
    deallocate();
    elements = larger;
    capacity = newCapacity;
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
  {
    return os << v.toString();
  }
}