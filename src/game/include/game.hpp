
#ifndef GAME_HPP
#define GAME_HPP

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "matrix.hpp"

namespace Life
{
  class Game
  {
  public:
    explicit Game(std::string _filename, unsigned long _life_time);
    void run();

  private:
    std::string convert_to_suffix (unsigned long i);
    std::string get_content (std::string filename);
    void save_to_file (std::string filename, std::string content);

    std::string filename;
    const unsigned long life_time;
    const unsigned short offset;
    Matrix matrix;
  };
}

#endif // GAME_HPP
