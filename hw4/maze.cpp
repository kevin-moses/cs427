#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <queue>
#include "maze.hpp"
using std::string;
using std::vector;
using std::queue;
using std::unordered_map;
using std::hasher;
enum Direction {NORTH, EAST, SOUTH, WEST};

namespace cs427_527{
	// maze constructor -- error handling of input handled by
	Maze::Maze(vector<string> input) {
		width = input[0].size(); // length of first line
		height = input.size();
		entry = (2*width) + (2*height); // 2h+2w initial states
		matrix.resize(height);
		// put this all into the map
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				// add nodes
				Space ins(i, j, input[i].at(j), 0);
				matrix[i].push_back(ins);
			}
		}
	}
	//overloading output operator
	std::ostream& operator<<(std::ostream& os, Space s) {
		os << '(' << s.row << ", " << s.col << ")";
		return os;
	}

	void Maze::findNextNodes(Space curr, vector<Space> nodes, int &things) {
		switch(curr.state) {
			case 'S':
				things = 1;
				switch(curr.pos) {
					case NORTH: nodes.push_back(matrix[curr.row-1][curr.col]);
						break;
					case SOUTH: nodes.push_back(matrix[curr.row+1][curr.col]);
						break;
					case EAST: nodes.push_back(matrix[curr.row][curr.col+1]);
						break;
					case WEST: nodes.push_back(matrix[curr.row][curr.col-1]);
						break;
				}
				break;
			case 'L':
				things = 1;
				switch(curr.pos) {
					case NORTH: nodes.push_back(matrix[curr.row][curr.col-1]);
						break;
					case SOUTH: nodes.push_back(matrix[curr.row][curr.col+1]);
						break;
					case EAST: nodes.push_back(matrix[curr.row-1][curr.col]);
						break;
					case WEST: nodes.push_back(matrix[curr.row+1][curr.col]);
						break;
				}
				break;
			case 'R':
				things = 1;
				switch(curr.pos) {
					case NORTH: nodes.push_back(matrix[curr.row][curr.col+1]);
						break;
					case SOUTH: nodes.push_back(matrix[curr.row][curr.col-1]);
						break;
					case EAST: nodes.push_back(matrix[curr.row+1][curr.col]);
						break;
					case WEST: nodes.push_back(matrix[curr.row-1][curr.col]);
						break;
				}
				break;
			case 'U':
				things = 1;
				switch(curr.pos) {
					case NORTH: nodes.push_back(matrix[curr.row+1][curr.col]);
						break;
					case SOUTH: nodes.push_back(matrix[curr.row-1][curr.col]);
						break;
					case EAST: nodes.push_back(matrix[curr.row][curr.col-1]);
						break;
					case WEST: nodes.push_back(matrix[curr.row][curr.col+1]);
						break;
				}
				break;
			case '?':
				things = 3;
				nodes.push_back(matrix[curr.row+1][curr.col]);
				nodes.push_back(matrix[curr.row-1][curr.col]);
				nodes.push_back(matrix[curr.row][curr.col-1]);
				nodes.push_back(matrix[curr.row][curr.col+1]);
				break;
			case 'X':
				things = 0;
				break;
			case '*':
				things = 0;
				break;
		}
		return;
	}

	// //hashing attempt
	// std::size_t hashing(const Space &s) {
	// 	return (37* std::hash<int>()(s.row) ^ std::hash<int>()(name.col));
	// }

	vector<Space> Maze::shortestPath() {
	  //queue up "entry" number of ways to get into maze.
	  queue<Space> open;
	  unordered_map<Space, Space, hasher> visited;

	  // top row
	  for (int j = 0; j < width; j++) {
	    Space x(-1, j, 'S', SOUTH);
	    open.push(x);
	  }
	  // bottom row facing up
	  for (int j = 0; j < width; j++) {
	    Space x(width, j, 'S', NORTH);
	    open.push(x);
	  }
	  // left row facing right
	  for (int i = 0; i < height; i++) {
	    Space x(i, -1, 'S', EAST);
	    open.push(x);
	  }
	  // right row facing left
	  for (int i = 0; i < height; i++) {
	    Space x(i, height, 'S', WEST);
	    open.push(x);
	  }
	  // actual bfs
		Space start;
	  while (!open.empty()) {
	    Space curr = open.front();
	    open.pop();
			if (curr.state == '*') {
				start = curr;
			}
	    vector<Space> nextNodes;
			int things = 0;
	    findNextNodes(curr, nextNodes, things);
	    for (int i = 0; i < things; i++) {
	      Space next = nextNodes.at(i);
	      int r = next.row;
	      int c = next.col;
	      // if past bounds of maze, get out
	      if (r >= height || c >=  width || r == -1 || c == -1) {
	        continue;
	      }
	      // if unseen
	      if (!visited.count(next)) {
	        visited.insert(next, curr);
	        open.push(next);
	      }
	    }
	  }
	  // traceback path
	  vector<Space> path;
		Space curr = start;
	  while (visited.count(curr) != 0) {
	    path.push_back(curr);
	    Space back = visited[curr];
	    back = curr;
	  }
		return path;
	}





}
