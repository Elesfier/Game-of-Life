
#include <string>
#include <iostream>
#include "game.hpp"

int main (int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Use: Life <file_name> <length>" << std::endl;
      return 1;
    }
    Life::Game game(argv[1], std::stoul(argv[2]));
    game.run();
  }
  catch (std::exception& exc)
  {
    std::cerr << exc.what() << std::endl;
  }

  return 0;
}
