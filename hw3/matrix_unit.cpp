#include <iostream>

#include "matrix.hpp"

using std::cin;
using std::cout;
using std::endl;

using cs427527::Matrix;

// define symbols corresponding to lower levels of testing
#ifdef FINAL
#define ALL
#endif

#ifdef ALL
#define SLICE
#endif

#ifdef SLICE
#define MATRIXCOPY
#endif

#ifdef MATRIXCOPY
#define MATRIX
#endif


Matrix<int> makeMatrix(int h, int w);
void printMatrix(const Matrix<int>& m);
void printMatrixSlices(const Matrix<int>& m);
void printMatrixTransposed(const Matrix<int>& m);
void printMatrixIterators(const Matrix<int>& m);
void testCompareIterators(Matrix<int>& m1, const Matrix<int>& m2, Matrix<int> m);
template<typename Slice>
int sumSlice(const Slice& slice);
int sumMatrix(const Matrix<int>& m);

void testMatrix();
void testConstMatrix();
void testCopyMatrix1();
void testCopyMatrix2();
void testCopyMatrix3();
void testSlice1();
void testSlice2();
void testSlice3();
void testSlice4();
void testIterator1();
void testIterator2();
void testIterator3();
void testIterator3_const();
void testIterator4();
void testIterator5();
void testFinal();

int main(int argc, char **argv)
{
  int test;
  try
    {
      if (argc < 2)
	{
	  throw std::invalid_argument("no command-line arguments");
	}
      test = std::stod(std::string(argv[1]));
    }
  catch (...)
    {
      cout << "USAGE: " << argv[0] << " test-number" << endl;
      return 1;
    }

  
  switch (test)
    {
    case 0:
      testMatrix();
      break;

    case 1:
      testConstMatrix();
      break;

    case 2:
      testCopyMatrix1();
      break;
    
    case 3:
      testCopyMatrix2();
      break;
   
    case 4:
      testCopyMatrix3();
      break;
   
    case 5:
      testSlice1();
      break;
    
    case 6:
      testSlice2();
      break;
   
    case 7:
      testSlice3();
      break;
   
    case 8:
      testSlice4();
      break;

    case 9:
      testIterator1();
      break;
   
    case 10:
      testIterator2();
      break;
   
    case 11:
      testIterator3();
      break;

    case 12:
      testIterator3_const();
      break;

    case 13:
      testIterator4();
      break;
   
    case 14:
      testIterator5();
      break;

    case 15:
      testFinal();
      break;
      
    default:
      cout << argv[0] << ": invalid test number " << argv[1] << endl;
    }

  return 0;
}


void testMatrix() {
#ifdef MATRIX
    Matrix<int> small{2, 2};
    small.at(0, 0) = 1;
    small.at(1, 1) = 1;
    cout << "2x2 IDENTITY MATRIX" << endl;
    for (int r = 0; r < 2; r++)
        {
  	for (int c = 0; c < 2; c++)
  	  {
  	    cout << small.at(r, c) << " ";
  	  }
  	cout << endl;
        }
  #else
    cout << "matrix not implemented (try compiling with the symbol MATRIX defined" << endl;
#endif
}

void testConstMatrix() {
#ifdef MATRIX
    Matrix<int> small{2, 2};
    small.at(0, 0) = 1;
    small.at(1, 1) = 1;
    cout << "2x2 IDENTITY MATRIX" << endl;
    printMatrix(small);
#else
    cout << "matrix not implemented (try compiling with the symbol MATRIX defined" << endl;
#endif
}

void printMatrix(const Matrix<int>& m)
{
#ifdef MATRIX
  for (int r = 0; r < m.height(); r++)
    {
      for (int c = 0; c < m.width(); c++)
	{
	  cout << m.at(r, c) << " ";
	}
      cout << endl;
    }
#else
    cout << "matrix not implemented (try compiling with the symbol MATRIX defined" << endl;
#endif
}
    
void testCopyMatrix1() {
#ifdef MATRIXCOPY
    Matrix<int> m{3,4};
    m.at(0, 0) = 99;
    m.at(1, 1) = 98;

    auto copy = m;

    cout << "ORIGINAL" << endl;
    printMatrix(m);
    cout << "COPY" << endl;
    printMatrix(copy);
#else
    cout << "copy not implemented" << endl;
#endif
}

void testCopyMatrix2() {
#ifdef MATRIXCOPY
    Matrix<int> m{3,4};
    auto copy = m;

    copy.at(0, 0) = 99;
    copy.at(1, 1) = 98;
    cout << "ORIGINAL" << endl;
    printMatrix(m);
    cout << "MODIFIED COPY" << endl;
    printMatrix(copy);
#else
    cout << "not implemented" << endl;
#endif
}

void testCopyMatrix3() {
#ifdef MATRIXCOPY
    Matrix<int> m{3,4};
    auto copy = m;

    copy.at(0, 0) = 99;
    copy.at(1, 1) = 98;

    copy = m;
    cout << "RESET COPY TO ORIGINAL" << endl;
    printMatrix(copy);
#else
    cout << "not implemented" << endl;
#endif
}

void testSlice1() {
#ifdef SLICE
    Matrix<int> small = makeMatrix(3, 3);
    cout << "3x3 MULTIPLICATION TABLE" << endl;
    printMatrix(small);
#else
    cout << "slices not implemented" << endl;
#endif
}

void testSlice2() {
#ifdef SLICE
    auto m = makeMatrix(3, 4);
    m.at(1, 3) = 20; 
    
    auto middle = m[1];
    cout << "middle row, last column: " << middle[3] << endl;
#else
    cout << "slices not implemented" << endl;
#endif
}

void testSlice3() {
#ifdef SLICE
    auto m = makeMatrix(3, 4);

    m.at(0, 0) = 99;
    m.at(1, 1) = 98;

    cout << "PRINT USING SLICES" << endl;
    printMatrixSlices(m);
#else
    cout << "slices not implemented" << endl;
#endif
}

void testSlice4() {
#ifdef SLICE
    auto m = makeMatrix(3, 4);

    m.at(0, 0) = 99;
    m.at(1, 1) = 98;

    cout << "PRINT TRANSPOSED USING COLUMN SLICES" << endl;
    printMatrixTransposed(m);
#else
    cout << "slices not implemented" << endl;
#endif
}

Matrix<int> makeMatrix(int h, int w)
{
#ifdef SLICE
  Matrix<int> m{h, w};
  
  for (int r = 0; r < h; r++)
    {
      for (int c = 0; c < w; c++)
	{
	  m[r][c] = r * c;
	}
    }

  return m;
#else
  cout << "slices not implemented" << endl;
#endif
}

void printMatrixSlices(const Matrix<int>& m)
{
#ifdef SLICE
  for (int r = 0; r < m.height(); r++)
    {
      for (int c = 0; c < m.width(); c++)
	{
	  cout << m[r][c] << " ";
	}
      cout << endl;
    }
#else
  cout << "slices not implemented" << endl;
#endif
}

void printMatrixTransposed(const Matrix<int>& m)
{
#ifdef SLICE
  for (int c = 0; c < m.width(); c++)
    {
      for (int r = 0; r < m.height(); r++)
	{
	  cout << m.column(c)[r] << " ";
	}
      cout << endl;
    }
#else
  cout << "slices not implemented" << endl;
#endif
}

void testIterator1() {
#ifdef ALL
    auto m = makeMatrix(3, 4);

    m[0][0] = 99;
    m[1][1] = 98;
  
    cout << "ORIGINAL WITH ITERATORS" << endl;
    printMatrixIterators(m);
#else
    cout << "iterators not implemented" << endl;
#endif
}

void testIterator2() {
#ifdef ALL
    auto m = makeMatrix(3, 4);

    m.at(0, 0) = 99;
    m.at(1, 1) = 98;

    cout << "COPY AFTER MODIFYING LAST COLUMN" << endl;
    for (auto i = m.column(m.width() - 1).begin(); i != m.column(m.width() - 1).end(); ++i)
    {
      *i = 42;
    }
    printMatrixIterators(m);
#else
    cout << "iterators not implemented" << endl;
#endif
}

void testIterator3(){
#ifdef ALL
    auto m = makeMatrix(3, 4);

    cout << "SUM OF ORIGINAL BOTTOM ROW" << endl
       << sumSlice(m[m.height() - 1]) << endl;
#else
    cout << "iterators not implemented" << endl;
#endif
}

void testIterator3_const(){
#ifdef ALL
    auto m = makeMatrix(3, 4);
    const Matrix<int>& ref = m;

    cout << "SUM OF BOTTOM ROW OF CONST REFERENCE" << endl
	 << sumSlice(ref[ref.height() - 1]) << endl;
#else
    cout << "iterators not implemented" << endl;
#endif
}

void testIterator4() {
#ifdef ALL
    auto m = makeMatrix(3, 4);
  
    cout << "SUM OF ENTIRE ORIGINAL" << endl
       << sumMatrix(m) << endl;
#else
    cout << "iterators not implemented" << endl;
#endif
}

void testIterator5() {
#ifdef ALL
    auto m = makeMatrix(3, 4);
    auto copy = m;

    copy.at(0, 0) = 99;
    copy.at(1, 1) = 98;

    copy = m;

    copy[0][0] = 99;
    copy[1][1] = 98;
  
    for (auto i = copy.column(copy.width() - 1).begin(); i != copy.column(copy.width() - 1).end(); ++i)
    {
      *i = 42;
    }
  
    cout << "ITERATOR COMPARISONS" << endl;
    testCompareIterators(m, m, m);
#else
    cout << "iterators not implemented" << endl;
#endif
}

void printMatrixIterators(const Matrix<int>& m)
{
#ifdef ALL
  for (int r = 0; r < m.height(); r++)
    {
      for (auto i = m[r].begin(); i != m[r].end(); ++i)
	{
	  cout << *i << " ";
	}
      cout << endl;
    }
#else
  cout << "iterators not implemented" << endl;
#endif
}

void testCompareIterators(Matrix<int>& m1, const Matrix<int>& m2, Matrix<int> m3)
{
#ifdef ALL
  // add messages here indicating what is being compared
  cout << "begin == begin: "
       << (m1[0].begin() == m1[0].begin()) << endl; // true
  
#ifdef CPSC527
  cout << "iterator == const iterator: "
       << (m1[0].begin() == m2[0].begin()) << endl; // true
#else
  cout << "iterator == const iterator: 1" << endl;
#endif
  
  cout << "same position, different matrices: "
       << (m1[0].begin() == m3[0].begin()) << endl; // false
  
  cout << "same position through row and column: "
       << (m1[0].begin() == m1.column(0).begin()) << endl; // true
#else
  cout << "iterators not implemented" << endl;
#endif
}

template<typename Slice>
int sumSlice(const Slice& slice)
{
#ifdef ALL
  int sum = 0;
  for (auto i = slice.begin(); i != slice.end(); ++i)
    {
      sum += *i;
    }
  return sum;
#else
  return 0;
#endif
}

int sumMatrix(const Matrix<int>& m)
{
#ifdef ALL
  int sum = 0;
  for (int c = 0; c < m.width(); c++)
    {
      sum += sumSlice(m.column(c));
    }
  return sum;
#else
  return 0;
#endif
}

void testFinal()
{
#ifdef FINAL
  cout << "FINAL is defined" << endl;
#else
  cout << "make sure your final submission defines the FINAL symbol" << endl;
#endif
}
