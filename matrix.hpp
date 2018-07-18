
#if !defined(MATRIX_HH)
#define MATRIX_HH

#include <iostream>
#include <initializer_list>
#include <exception>
#include <math.h>

class MatrixException : public std::exception
{
public:
  MatrixException(const char *s)
  {
    _s = s;
  }
  virtual const char *what() const throw()
  {
    return _s;
  }

private:
  const char *_s;
};

class Matrix
{
private:
  unsigned int _numRows;
  unsigned int _numColumns;
  double **_matrix;

public:
  unsigned int getNumRows()
  {
    return _numRows;
  }
  unsigned int getNumColumns()
  {
    return _numColumns;
  }
  void show()
  {

    for (unsigned int i = 0; i < _numRows; i++)
    {
      std::cout << "[ ";
      for (unsigned int j = 0; j < _numColumns; j++)
      {
        std::cout << _matrix[i][j] << " ";
      }
      std::cout << "]" << std::endl;
    }
  }
  Matrix static TanH(const Matrix &m)
  {
    Matrix tM;
    tM._numRows = m._numRows, tM._numColumns = m._numColumns;
    tM._matrix = new double *[m._numRows];

    for (size_t i = 0; i < m._numRows; i++)
    {
      tM._matrix[i] = new double[m._numColumns];
      for (size_t j = 0; j < m._numColumns; j++)
      {
        tM._matrix[i][j] = (1 - exp(-2 * m._matrix[i][j])) / (1 + exp(-2 * m._matrix[i][j]));
        //tM._matrix[i][j] = (1 / (1 + exp(-m._matrix[i][j]))); --> Sigmod
      }
    }
    return tM;
  }
  friend bool &operator==(const Matrix &y, const Matrix &x)
  {
    if (y._numColumns == x._numColumns && x._numRows == y._numRows)
    {
      //Para cada linha
      for (size_t i = 0; i < x._numRows; i++)
      {
        //Para cada collumn
        for (size_t j = 0; j < x._numColumns; j++)
        {
          if (x._matrix[i][j] != y._matrix[i][j])
          {
            return false;
          }
        }
      }
      //Se não retornou false é igual
      return true;
    }
    else
    {
      return false;
    }
  }
  Matrix &operator=(const Matrix &y)
  {
    this->~Matrix();
    this->_matrix = new double *[y._numRows];
    this->_numRows = y._numRows, this->_numColumns = y._numColumns;

    for (size_t i = 0; i < y._numRows; i++)
    {
      this->_matrix[i] = new double[y._numColumns];
      for (size_t j = 0; j < y._numColumns; j++)
      {
        this->_matrix[i][j] = y._matrix[i][j];
      }
    }
    return *this;
  }
  Matrix operator+(const Matrix &x)
  {
    if (this->_numColumns != x._numColumns || this->_numRows != x._numRows)
    {
      throw new MatrixException("The matrices are of different dimensions");
    }
    Matrix m;
    m._numRows = x._numRows;
    m._numColumns = x._numColumns;
    m._matrix = new double *[x._numRows];

    for (size_t i = 0; i < x._numRows; i++)
    {
      m._matrix[i] = new double[x._numColumns];
      for (size_t j = 0; j < x._numColumns; j++)
      {
        m._matrix[i][j] = this->_matrix[i][j] + x._matrix[i][j];
      }
    }
    return m;
  }
  Matrix operator*(const Matrix &x)
  {
    if (this->_numColumns != x._numRows)
    {
      throw new MatrixException("The number of columns of the first matrix is different from the number of lines of the second");
    }
    Matrix p;
    p._numRows = this->_numRows, p._numColumns = x._numColumns;
    p._matrix = new double *[this->_numRows];
    for (size_t i = 0; i < this->_numRows; i++)
    {
      p._matrix[i] = new double[x._numColumns];
      for (size_t j = 0; j < x._numColumns; j++)
      {
        p._matrix[i][j] = 0;
        for (size_t k = 0; k < x._numRows; k++)
        {
          p._matrix[i][j] += this->_matrix[i][k] * x._matrix[k][j];
        }
      }
    }
    return p;
  }
  double *operator[](int x)
  {
    return _matrix[x];
  }
  template <typename T, std::size_t N, std::size_t M>
  Matrix(T (&a)[N][M])
  {
    _numRows = N;
    _numColumns = M;
    _matrix = new double *[_numRows];
    for (unsigned int i = 0; i < _numRows; i++)
    {
      _matrix[i] = new double[_numColumns];
      for (unsigned int j = 0; j < _numColumns; j++)
      {
        _matrix[i][j] = a[i][j];
      }
    }
  }
  Matrix(std::initializer_list<std::initializer_list<double>> j)
  {
    _numRows = j.size();
    _numColumns = 0;
    if (_numRows > 0)
    {
      _numColumns = j.begin()->size();
    }
    size_t counterR = 0;
    _matrix = new double *[_numRows];
    for (auto &row : j)
    {
      _matrix[counterR] = new double[_numColumns];
      size_t counterC = 0;
      for (auto &collumn : row)
      {
        _matrix[counterR][counterC++] = collumn;
      }
      counterR++;
    }
  }
  Matrix()
  {
    _matrix = 0;
    _numColumns = 0;
    _numRows = 0;
  }
  Matrix(size_t i, size_t j)
  {
    _numColumns = j;
    _numRows = i;
    _matrix = new double *[i];
    for (size_t k = 0; k < i; k++)
    {
      _matrix[k] = new double[j];

      for (size_t l = 0; l < j; l++)
      {
        _matrix[k][l] = 1;
      }
    }
  }
  Matrix(const Matrix &m)
  {
    _numColumns = m._numColumns, _numRows = m._numRows;
    _matrix = new double *[m._numRows];

    for (size_t i = 0; i < m._numRows; i++)
    {
      _matrix[i] = new double[m._numColumns];

      for (size_t j = 0; j < m._numColumns; j++)
      {
        _matrix[i][j] = m._matrix[i][j];
      }
    }
  }
  ~Matrix()
  {
    // free the allocated memory
    for (int i = 0; i < _numRows; i++)
    {
      delete[] _matrix[i];
    }
    delete[] _matrix;
  }
};
#endif // MATRIX_HH
