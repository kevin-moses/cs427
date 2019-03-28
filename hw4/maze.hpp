#ifndef __CS427527_MAZE_HPP__
#define __CS427527_MAZE_HPP__
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;

namespace cs427_527{
	// maze is a unordered map of Spaces
	class Maze {
	//constructor
	public:
		Maze(vector<string> input);
		void findNextNodes(pair <pair<int, int>,pair<int, int>> curr, vector<pair <pair<int, int>,pair<int, int>> > &nodes) ;
		vector<pair<int, int>> shortestPath();

	private:
		vector<string> matrix;
		int width;
		int height;
		int entry; // initial states
	};

}
namespace std
{
	//overloading output operator
	inline ostream& operator<<(std::ostream& os, const pair<int, int>& p) {
		os << '(' << p.first << ", " << p.second << ")";
		return os;
	}
  template<>
  class hash< pair< pair<int, int>, pair<int, int> > >
  {
  public:
    size_t operator()(const pair< pair<int, int>, pair<int, int> > & p) const
    {
      return p.first.first + p.first.second * p.second.first + p.second.second;
    }
  };
}

#endif
