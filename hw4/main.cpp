#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "maze.hpp"

using std::string;
using cs427_527::Maze;

int main(int argc, char **argv)
{
  try
    {
      std::vector<string> input;
      
      string line;
      while (std::getline(std::cin, line))
	{
	  if (line.find_first_not_of("RLSU?*X") != string::npos)
	    {
	      throw std::logic_error{"invalid character in input"};
	    }
	  if (input.size() > 0 && input[0].length() != line.length())
	    {
	      throw std::length_error{"rows are not the same length"};
	    }
	  if (line.size() == 0)
	    {
	      throw std::length_error{"empty row"};
	    }
	  
	  input.push_back(line);
	}
      if (input.size() == 0)
	{
	  throw std::length_error{"empty maze"};
	}

      auto m = Maze{input};
      auto path = m.shortestPath();
      std::for_each(path.begin(),
		    path.end(),
		    [](auto &p) { std::cout << p << std::endl; });
    }
  catch (const std::exception& ex)
    {
      std::cerr << argv[0] << ": " << ex.what() << std::endl;
    }
      
  return 0;
}
