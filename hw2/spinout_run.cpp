#include <iostream>
#include <cstring>
#include <sstream>
#include "spinout.hpp"
using std::cout;
using std::cin;
using std::endl;
using cs427_527::SpinOut;

bool checkDisks(char const input[]);
void interactive(SpinOut &game);
void noninteractive(SpinOut &game, int i[], int cap);

int main(int argc, char const *argv[])
{
	// check for interactive mode
	const char *mode = "-i";
	if (argc > 1 && strcmp(argv[1], mode) == 0) {

		if (argc > 2) {
			// check validity of string
			if (checkDisks(argv[2]) == false) {
				exit(-1);
			}

			// run interactive mode
			std::string inputstr(argv[2]);
			SpinOut game = SpinOut(inputstr);
			interactive(game);
			return 0;
		}

		SpinOut game{};
		interactive(game);
		return 0;
	}
	// non-interactive mode
	int index, count;
	SpinOut game = SpinOut();
	if (checkDisks(argv[1]) == true) {
		index = 2;
		count = 1;
		std::string inputstr(argv[1]);
		game = SpinOut(inputstr);
	} else {
		index = 1;
		count = 1;
	}
	for (int i = index; i < argc; i++) {
		// cout << "here" << endl;
		std::stringstream sval;
		sval << argv[i];
		int ival;
		sval >> ival;
		if (game.isLegalMove(ival)) {
			game.makeMove(ival);
			if (game.isSolved() && i+1==argc) {
				cout << "SOLVED" << endl;
				return 0;
			}
			count++;
			}
		else {
			cout << "SpinOut: illegal move " << ival << " in position " << count << " for " << game.toString() << endl;
			return 0;
		}
	}
	cout << game.toString() << endl;
	return 0;
}

void interactive(SpinOut &game) {
	cout <<  game.toString() << endl;
	int pos;
	while (cin >> pos) {
		if (game.isLegalMove(pos)) {
			game.makeMove(pos);
			cout << game.toString() << endl;
		}
		else {
			cout << "illegal move" << endl;
		}
		if(game.isSolved()) {
			cout << game.totalMoves() << " moves" << endl;
			return;
		}
	}
}

bool checkDisks(char const input[]) {
	int len = 0;
	while (input[len] != '\0') {
		if (input[len] != '-' && input[len] != '/') {
			return false;
		}
		len++;
		if (len != 7) {
			return false;
		}
	}
	return true;
}
