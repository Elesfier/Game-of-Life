
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <functional>
#include <iostream>
#include <exception>
#include <regex>

namespace Life
{
  class WrongCSVFormatException : public std::exception
  {
  public:
      virtual const char* what() const throw ();
  };

  class WrongCSVSizeException : public std::exception
  {
  public:
      virtual const char* what() const throw ();
  };

  //[NOTE]: index przedstawia mały obszar w macierzy
  typedef struct Field { bool index[9]; } Field;

  class Matrix
  {
  public:
    explicit Matrix(std::string csv_content);
    ~Matrix();

    std::string transform (std::function<bool(Field field)> operation);

  private:
    void prepare_matrix(std::string csv_content);

    unsigned long matrix_size;
    bool** matrix;
    //[NOTE]: tablica przechowująca przetworzone komorki
    bool* matrix_part[3];
  };
}

#endif // MATRIX_HPP
