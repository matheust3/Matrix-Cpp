
#if !defined(MATRIX_HH)
#define MATRIX_HH

#include <iostream>

class matrix
{
private:
  unsigned int _numRows;
  unsigned int _numColumns;
  float **_matrix;

public:
  void show();
  template <typename T, std::size_t N, std::size_t M>
  matrix(T (&a)[N][M]);
  ~matrix();
};
template <typename T, std::size_t N, std::size_t M>
matrix::matrix(T (&a)[N][M])
{
  _numRows = N;
  _numColumns = M;
  _matrix = new float *[_numRows];
  for (unsigned int i = 0; i < _numRows; i++)
  {
    _matrix[i] = new float[_numColumns];
    for (unsigned int j = 0; j < _numColumns; j++)
    {
      _matrix[i][j] = a[i][j];
    }
  }
}

matrix::~matrix()
{
  // free the allocated memory
  for (int i = 0; i < _numRows; i++)
  {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}
void matrix::show()
{
  for (unsigned int i = 0; i < _numRows; i++)
  {
    for (unsigned int j = 0; j < _numColumns; j++)
    {
      std::cout << _matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
#endif // MATRIX_HH
