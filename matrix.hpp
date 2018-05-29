
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
    template <typename T, std::size_t N, std::size_t M>
    matrix(T (&a)[N][M]);
    ~matrix();
};
template <typename T, std::size_t N, std::size_t M>
matrix::matrix(T (&a)[N][M])
{
    _numRows = N;
    _numColumns = M;
}

matrix::~matrix()
{
}

#endif // MATRIX_HH
