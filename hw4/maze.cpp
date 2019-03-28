#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "maze.hpp"
using std::string;
using std::vector;
using std::queue;
using std::unordered_map;
using std::hash;
using std::pair;
using std::cout;
using std::endl;

namespace cs427_527{
	// maze constructor -- error handling of input handled by
	Maze::Maze(vector<string> input) {
		width = input[0].size(); // length of first line
		height = input.size();
		entry = (2*width) + (2*height); // 2h+2w initial states
		matrix = input;
	}


	void Maze::findNextNodes(pair <pair<int, int>,pair<int, int>> curr, vector<pair <pair<int, int>,pair<int, int>> > &nodes
		) {
		// get current row and column
		int curr_r = curr.first.first;
		int curr_c = curr.first.second;
		// get previous row and column indices
		int prev_r = curr.second.first;
		int prev_c = curr.second.second;
		// row and column to be inserted
		int next_r;
		int next_c;
		switch(matrix[curr_r][curr_c]) {
			case 'S':
				// NORTH
				if (curr_r < prev_r) {
					next_r = curr_r -1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// SOUTH
				if (curr_r > prev_r) {
					next_r = curr_r + 1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// EAST
				if (curr_c > prev_c) {
					next_c = curr_c + 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// WEST
				if (curr_c < prev_c) {
					next_c = curr_c - 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				break;
			case 'L':
				// NORTH
				if (curr_r < prev_r) {
					next_c = curr_c -1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// SOUTH
				if (curr_r > prev_r) {
					next_c = curr_c + 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// EAST
				if (curr_c > prev_c) {
					next_r = curr_r -1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// WEST
				if (curr_c < prev_c) {
					next_r = curr_r + 1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				break;
				// YOU ARE HERE
			case 'R':
				// NORTH
				if (curr_r < prev_r) {
					next_c = curr_c + 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// SOUTH
				if (curr_r > prev_r) {
					next_c = curr_c - 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// EAST
				if (curr_c > prev_c) {
					next_r = curr_r + 1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// WEST
				if (curr_c < prev_c) {
					next_r = curr_r -  1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				break;
			case 'U':
				// NORTH
				if (curr_r < prev_r) {
					next_r = curr_r + 1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// SOUTH
				if (curr_r > prev_r) {
					next_r = curr_r - 1;
					next_c = curr_c;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// EAST
				if (curr_c > prev_c) {
					next_c = curr_c - 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				// WEST
				if (curr_c < prev_c) {
					next_c = curr_c + 1;
					next_r = curr_r;
					nodes.push_back(std::make_pair (std::make_pair(next_r, next_c), std::make_pair(curr_r, curr_c)));
					break;
				}
				break;
			case '?':
				int one_r = curr_r+1;
				int two_r = curr_r-1;
				int one_c = curr_c+1;
				int two_c = curr_c-1;
				nodes.push_back(std::make_pair (std::make_pair(one_r, curr_c), std::make_pair(curr_r, curr_c)));
				nodes.push_back(std::make_pair (std::make_pair(two_r, curr_c), std::make_pair(curr_r, curr_c)));
				nodes.push_back(std::make_pair (std::make_pair(curr_r, one_c), std::make_pair(curr_r, curr_c)));
				nodes.push_back(std::make_pair (std::make_pair(curr_r, two_c), std::make_pair(curr_r, curr_c)));		
				break;
		}
		return;
	}

	vector<pair<int, int>> Maze::shortestPath() {
	  //queue up "entry" number of ways to get into maze.
	  queue< pair< pair<int, int>, pair<int, int>>> open;
	  unordered_map< pair<pair<int, int>, pair<int, int>>, pair<pair<int, int>, pair<int, int>>> visited;
	  // top row
	  for (int j = 0; j < width; j++) {
	  	auto x = std::make_pair(0, j);
		auto y = std::make_pair(-1, j);
	    // Space x(-1, j, 'S', SOUTH);
	    open.push(std::make_pair(x, y));
	  }
	  // bottom row facing up
	  for (int j = 0; j < width; j++) {
		auto x = std::make_pair(width-1, j);
		auto y = std::make_pair(width, j);
		// Space x(width, j, 'S', NORTH);
	    open.push(std::make_pair(x, y));
	  }
	  // left row facing right
	  for (int i = 0; i < height; i++) {
		auto x = std::make_pair(i, 0);
		auto y = std::make_pair(i, -1);
	    // Space x(i, -1, 'S', EAST);
		open.push(std::make_pair(x, y));

	  }
	  // right row facing left
	  for (int i = 0; i < height; i++) {
		auto x = std::make_pair(i, height-1);
		auto y = std::make_pair(i, height);
	    // Space x(i, height, 'S', WEST);
		open.push(std::make_pair(x, y));
	  }


	  // actual bfs
	  // get start node (*) and where it came from
	  pair<pair<int, int>, pair<int, int>> start;

	  while (!open.empty()) {
	    pair<pair<int, int>, pair<int, int>> curr = open.front();
	    open.pop();
	    // get thing about to be popped off queue as starting point in hashtable
		if (matrix[curr.first.first][curr.first.second] == '*') {
			start = curr;
			break;
		}
		//get list of nodes to search and how many things are in that array
	    vector<pair <pair<int, int>,pair<int, int>> > nextNodes;
	    findNextNodes(curr, nextNodes);
	    for (auto& next : nextNodes) {
	      int r = next.first.first;
	      int c = next.first.second;
	      // if past bounds of maze, get out
	      if (r >= height || c >=  width || r == -1 || c == -1) {
	        continue;
	      }
	      // if unseen
	      if (!visited.count(next)) {
	        visited.insert({next, curr});
	        open.push(next);
	      }
	    }
	  }
	  
	  // traceback path
	  vector<pair<int,int>> path;
	  if (matrix[start.first.first][start.first.second] == '*') {
		  pair<pair<int, int>, pair<int, int>> curr = start;
		  // cout << curr.first << curr.second << endl;
		  while (visited.count(curr) != 0) {
		  	int r = curr.first.first;
		  	int c = curr.first.second;
		    path.push_back(std::make_pair(r, c));
		    pair<pair<int, int>, pair<int, int>> back = visited[curr];
		    curr = back;
		  }
		  path.push_back(curr.first);
		  path.push_back(curr.second);
		  std::reverse(path.begin(), path.end());
	  }
	  return path;
	}
}