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

namespace cs427_527{
	// class Space {
	// public:
	// 	// comparison operator
	// 	Space() {
	// 		row = 0;
	// 		col = 0;
	// 		state = 'S';
	// 		pos = 0;
	// 	}
	// 	Space(int r, int c, char s, int p) {
	// 		row = s;
	// 		col = c;
	// 		state = s;
	// 		pos = p;
	// 	}
	// 	int row;
	// 	int col;
	// 	char state;
	// 	int pos;
	// 	bool operator==(const Space &two) const {
	// 		return (row == two.row && col == two.col && state == two.state && pos == two.pos);
	// 	}
	// 	bool operator!=(const Space &two) const {
	// 		return !(*this==two);
	// 	}
	// };

	std::ostream& operator<<(std::ostream& os, Space s);


	// maze is a unordered map of Spaces
	class Maze {
	//constructor
	public:
		Maze(vector<string> input);
		void findNextNodes(pair<int, int> curr, vector<pair<int, int>> nextNodes, int &things);
		// vector<Space> bfs(Space path, int& dist);
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
  template<>
  class hash< pair< int, int > >
  {
  public:
    size_t operator()(const pair< int, int >& p) const
    {
      return p.first + p.second;
    }
  };
}

namespace std {
	//overloaded hash class
	template<>
	struct hasher<class Space>
	{
		size_t operator()(const cs427_527::Space &x) const
		{
			return (37* hash<int>()(x.row) ^ hash<int>()(x.col));
		}
	};

}


#endif
