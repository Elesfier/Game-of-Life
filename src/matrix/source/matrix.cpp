
#include "matrix.hpp"

namespace Life
{
  const char* WrongCSVFormatException::what() const throw ()
  {
      return "WrongCSVFormatException: Bad csv format, please check the file.";
  }

  const char* WrongCSVSizeException::what() const throw ()
  {
      return "WrongCSVSizeException: Wrong size in csv file.";
  }

  Matrix::Matrix(std::string csv_content)
  {
    std::regex cvs_format_regex("^([0-1](,|\n)?)+$");
    if (!std::regex_match(csv_content, cvs_format_regex))
      throw WrongCSVFormatException();
    unsigned long h = 0, w = 0, prev_w = 0;
    const unsigned long csv_len = csv_content.size();
    for (unsigned long i = 0; i < csv_len;)
    {
      w++;
      if ((i+1) != csv_len && csv_content.at(i+1) == '\n')
      {
        if (prev_w != 0 && w != prev_w)
          throw WrongCSVSizeException();
        h++;
        prev_w = w;
        w = 0;
      }
      i += 2;
    }
    if (h != prev_w)
      throw WrongCSVSizeException();
    matrix_size = h;
    prepare_matrix(csv_content);
  }

  Matrix::~Matrix()
  {
    for (unsigned long i = 0; i < matrix_size; ++i)
    {
      delete matrix[i];
    }
    delete matrix;
    delete matrix_part[0];
    delete matrix_part[1];
    delete matrix_part[2];
  }

  void Matrix::prepare_matrix(std::string csv_content)
  {
    if (matrix_size)
    {
      matrix = new bool *[matrix_size];
      for (unsigned long i = 0; i < matrix_size; ++i)
      {
        matrix[i] = new bool [matrix_size];
      }
      matrix_part[0] = new bool [matrix_size];
      matrix_part[1] = new bool [matrix_size];
      matrix_part[2] = new bool [matrix_size];

      const unsigned long csv_len = csv_content.size();
      for (unsigned long i = 0, h = 0, w = 0; i < csv_len-2;)
      {
        matrix[h][w] = (csv_content.at(i) == '1')?(true):(false);
        w++;
        if ((i+1) != csv_len && csv_content.at(i+1) == '\n')
        {
          h++;
          w = 0;
        }
        i += 2;
      }
    }
  }

  std::string Matrix::transform (std::function<bool(Field field)> operation)
  {
    std::string new_content = "";
    unsigned short prev_part = 0;
    unsigned short next_part = 0;
    for (unsigned long i = 0; i < matrix_size+2; ++i)
    {
      for (unsigned long j = 0; j < matrix_size; ++j)
      {
        if (i > 1)
        {
          matrix[i-2][j] = matrix_part[prev_part][j];
          new_content += (matrix[i-2][j])?("1"):("0");
          new_content += ",";
          if (prev_part == 2) { prev_part = 0; } else { prev_part++; }
        }

        if (i < matrix_size)
        {
          Field area;
          area.index[0] = (i != 0 && j != 0)?(matrix[i-1][j-1]):(false);
          area.index[1] = (i != 0)?(matrix[i-1][j]):(false);
          area.index[2] = (i != 0 && j+1 < matrix_size)?(matrix[i-1][j+1]):(false);
          area.index[3] = (i != 0)?(matrix[i][j-1]):(false);
          area.index[4] = matrix[i][j]; //[NOTE]: centre
          area.index[5] = (j+1 < matrix_size)?(matrix[i][j+1]):(false);
          area.index[6] = (j != 0 && i+1 < matrix_size)?(matrix[i+1][j-1]):(false);
          area.index[7] = (i+1 < matrix_size)?(matrix[i+1][j]):(false);
          area.index[8] = (i+1 < matrix_size && j+1 < matrix_size)?(matrix[i+1][j+1]):(false);

          matrix_part[next_part][j] = operation(area);
          if (next_part == 2) { next_part = 0; } else { next_part++; }
        }
      }
      if (i > 1)
      {
        new_content.pop_back();
        new_content += "\n";
      }
    }
    return new_content;
  }
}
