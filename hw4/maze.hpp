#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;

namespace cs427_527 {

	// maze is a unordered map of Spaces
	class Maze {
		//constructor
		Maze(vector<string> input);
		vector<Space> shortestPath();
	public:
		class Space {
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

	private:
		Vector<Vector<Space>> matrix;
		int width;
		int height;
		int entry; // initial states
	};
}