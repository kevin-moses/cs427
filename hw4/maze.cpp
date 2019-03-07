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
using std::hash;
using std::pair;

namespace cs427_527{
	// maze constructor -- error handling of input handled by
	Maze::Maze(vector<string> input) {
		width = input[0].size(); // length of first line
		height = input.size();
		entry = (2*width) + (2*height); // 2h+2w initial states
		matrix = input;
	}


	//overloading output operator
	std::ostream& operator<<(std::ostream& os, pair<int, int> p) {
		os << '(' << p.first << ", " << p.second << ")";
		return os;
	}

	void Maze::findNextNodes(pair<int, int> curr, vector<pair<int, int>> nodes, int &things) {
		switch(matrix[curr.first][curr.second]) {
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
	  queue< pair< pair<int, int>, pair<int, int>>> open;
	  unordered_map<pair<pair<int, int>, pair<int, int>>, pair<pair<int, int>, pair<int, int>>> visited;

	  // top row
	  for (int j = 0; j < width; j++) {
			auto x = make_pair(0, j);
			auto y = make_pair(-1, j);
	    // Space x(-1, j, 'S', SOUTH);
	    open.push(make_pair(x, y));
	  }
	  // bottom row facing up
	  for (int j = 0; j < width; j++) {
			auto x = make_pair(width-1, j);
			auto y = make_pair(width, j);
			// Space x(width, j, 'S', NORTH);
	    open.push(make_pair(x, y));
	  }
	  // left row facing right
	  for (int i = 0; i < height; i++) {
			auto x = make_pair(i, 0);
			auto y = make_pair(i, -1);
	    // Space x(i, -1, 'S', EAST);
			open.push(make_pair(x, y));

	  }
	  // right row facing left
	  for (int i = 0; i < height; i++) {
			auto x = make_pair(i, height-1)
			auto y = make_pair(i, height);
	    // Space x(i, height, 'S', WEST);
			open.push(make_pair(x, y));
	  }
	  // actual bfs
		// get start node (*) and where it came from
		pair<pair<int, int>, pair<int, int>> start;
	  while (!open.empty()) {
	    pair<pair<int, int>, pair<int, int>> curr = open.front();
			//find out what the direction is pointing at for base cases
			Direction dir;
			if (curr.first )
	    open.pop();
			if (matrix[curr.first][curr.second] == '*') {
				start = curr;
			}
	    vector<pair<int, int>> nextNodes;
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


/*
//queue up "entry" number of ways to get into maze.
queue<Space> open;
unordered_map<pair<int,int>, pair<int, int>> visited;
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
  int r1 = curr.row;
  int c1 = curr.col;
  vector<Space> nextNodes;
  int things = 0;
  findNextNodes(curr, nextNodes, things);
  for (int i = 0; i < things; i++) {
    Space next = nextNodes.at(i);
    int r2 = next.row;
    int c2 = next.col;
    // if past bounds of maze, get out
    if (r >= height || c >=  width || r == -1 || c == -1) {
      continue;
    }
    // if unseen
    if (!visited.count(next)) {
      visited.insert(<r2, c2> , <r1, c1>);
      open.push(next);
    }
  }
}
// traceback path
vector<Space> path;
Space curr = start;
int curr_r = curr.row;
int curr_c = curr.col;
while (visited.count(<curr_r, curr_c>) != 0) {
  path.push_back(curr);
  Space back = visited[curr];
  curr = back;
  curr_r = curr.row;
  curr_c = curr.col;
}
return path;

*/
