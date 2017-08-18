
#include "game.hpp"

namespace Life
{
  Game::Game(std::string _path, unsigned long _life_time)
    : filename("./" + _path.substr(_path.find_last_of("\\/")+1, _path.size())),
      life_time(_life_time),
      offset(std::to_string(_life_time).size()),
      matrix(get_content(_path))
  {
  }

  void Game::run()
  {
    for (unsigned long i = 0; i < life_time; ++i)
    {
      save_to_file(
        filename + convert_to_suffix(i+1),  //[NOTE]: new filename
        matrix.transform([](Field field){   //[NOTE]: return transform csv

          //[NOTE]: komórki sąsiadujące z środkową komórką
          unsigned short neigh = 0;
          for (unsigned short i = 0; i < 9; ++i)
          {
            if (i != 4 && field.index[i]) neigh++;
          }
          return ((field.index[4])?(neigh == 2 || neigh == 3):(neigh == 3));

        })
      );
    }
  }

  std::string Game::get_content (std::string filename)
  {
    std::ifstream in(filename);
    return std::string(
      std::istreambuf_iterator<char>(in),
      std::istreambuf_iterator<char>());
  }

  void Game::save_to_file (std::string filename, std::string content)
  {
    std::ofstream out(filename);
    out << content;
    out.close();
  }

  std::string Game::convert_to_suffix (unsigned long i)
  {
    std::stringstream ss;
    ss << "_" << std::setw(offset) << std::setfill('0') << i;
    return ss.str();
  }
}
