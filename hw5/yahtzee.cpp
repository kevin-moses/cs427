#include <iostream>

#include <vector>
#include <bitset>
#include <string>

#include "diceroll.hpp"
#include "yahtzee.hpp"

using std::vector;
using std::bitset;
using std::string;

namespace cs427_527
{
	YahtzeeGame::YahtzeeGame(int options, vector<int> scorenum, vector<string> scorename, bool isBonus, int bonus) {
		this.options = options;
		this.scorename = scorename;
		this.scorenum = scorenum;
		this.isBonus = isBonus;
		this.bonus = bonus;
	}
	YahtzeeState YahtzeeGame::initialState() {
		// set scores to -1 
		for (int i = 0; i < options; i++){
			scorenum.push_back(-1);
		}
		// print upper rows
		for (int i = 0; i < 6; i++) {
			cout << "   "
		}

	}
}