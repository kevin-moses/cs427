#include <iostream>
#include <cstring>
#include "spinout.hpp"
using std::cout;
using std::cin;
using std::endl;
using cs427_527::SpinOut;

bool checkDisks(char const input[]);
void interactive(SpinOut &game);

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
	}
	// non-interactive mode
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
		if (len > 7) {
			cout << "here" << endl;
			return false;
		}
	}
	return true;
}