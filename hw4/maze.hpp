#ifndef __CS427527_MAZE_HPP__
#define __CS427527_MAZE_HPP__
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;


namespace cs427_527{
	class Space {
	public:
		Space() {
			row = 0;
			col = 0;
			state = 'S';
			pos = 0;
		}
		Space(int r, int c, char s, int p) {
			row = s;
			col = c;
			state = s;
			pos = p;
		}
		int row;
		int col;
		char state;
		int pos;
	};


	// maze is a unordered map of Spaces
	class Maze {
	//constructor
	public:
		Maze(vector<string> input);
		vector<Space> findNextNodes(Space curr);
		vector<Space> bfs(Space path, int& dist);
		vector<Space> shortestPath();

	private:
		vector<vector<Space>> matrix;
		int width;
		int height;
		int entry; // initial states
	};
	//overloaded hash class
	template<>
	struct std::hash<Space, Space>
	{
	public:
		size_t operator()(Space x, Space y) const
		{
			size_t h;
			size_t one = (size_t)x.state;
			size_t two = (size_t)y.state;
			h = 37*two*one;
			return h;
		}
	};
}


#endif
