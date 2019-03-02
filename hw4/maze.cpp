#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <queue>

using std::string;
using std::vector;
using std::queue;
enum Direction {NORTH, EAST, SOUTH, WEST};

namespace cs427_527 {
	// maze constructor -- error handling of input handled by 
	Maze::Maze(vector<string> input) {
		width = input[0].size(); // length of first line
		height = input.size();
		entry = (2*width) + (2*height); // 2h+2w initial states
		// put this all into the map
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				// add nodes
				Space ins(i, j, input[i].at(j), 0);
				matrix[i].at(j) = ins;
			}
		}
	}
	vector<Space> Maze::findNextNodes(curr) {
		vector<Space> nodes;
		switch(curr.state) {
			case 'S':
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
				nodes.push_back(matrix[curr.row+1][curr.col]);
				nodes.push_back(matrix[curr.row-1][curr.col]);
				nodes.push_back(matrix[curr.row][curr.col-1]);
				nodes.push_back(matrix[curr.row][curr.col+1]);
				break;
			case 'X':
				break;
			case '*':
				break;
		}
		return nodes;
	}
	//BFS implementation
	vector<Space> Maze::bfs(Space start, Space target) {
		// set up queue and push root
		vector<vector<bool>> visited(height, vector<bool>(width, false));
		vector<Space> path;
		path.push_back(start);
		queue<Space> open;
		open.push(start);

		while (!open.empty()) {
			Space curr = open.front();
			open.pop();
			vector<Space> nextNodes = findNextNodes(curr);
			for (int i = 0; i < nextNodes.size(); i++) {
				// if reached end
				if (nextNodes.at(i) == target) {
					open.push();
					// YOU ARE HERE
				}

			}
		}

	}

	Maze::shortestPath() {
		//queue up "entry" number of ways to get into maze.
		vector<Space> start;
		// top row
		for (int j = 0; j < width; j++) {
			Space x(-1, j, 'S', SOUTH);
			start.push_back(x);
		}
		// bottom row facing up
		for (int j = 0; j < width; j++) {
			Space x(width, j, 'S', NORTH);
			start.push_back(x);	
		}
		// left row facing right
		for (int i = 0; i < height; i++) {
			Space x(i, -1, 'S', EAST);
			start.push_back(x);
		}
		// right row facing left
		for (int i = 0; i < height; i++) {
			Space x(i, height, 'S', WEST);
			start.push_back(x);
		}
		// find targets - multiple targets can exist
		vector<Space> target;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (matrix[i].at(j).state == '*') {
				 	target.push_back(matrix[i].at(j));
				}
			}
		}
		// run bfs for each target for each entry position
		for(int k = 0; k < target.size(); k++) {
			for (int i = 0; i < states; i++) {
				bfs(start.at(i), target.at(k));
			}
		}
	}


}