#include "yahtzee.hpp"

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <iomanip>

#include "diceroll.hpp"
#include "rule.hpp"

using std::vector;
using std::bitset;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;

namespace cs427_527
{
	Scoresheet::Scoresheet(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index, int y_index){
		this->options = options;
		this->scorenum = scores;
		this->rules = rules;
		this->ub_index = ub_index;
		this->y_index = y_index;
		for (int i = 0; i < options; i++) {
			isScored.push_back(false);
		}
		isScored[ub_index] = true;
		// y_index has the YORTZEE value. we want the YORTZEE BONUS to not apply during scoring.
		multbonus_count = -1;
		if (y_index != -1) {
			isScored[y_index+1] = true;
			multbonus_count = 0;
		} 

	}

	vector<string> Scoresheet::unusedCategories() {
		// get abbreviations
		vector<string> abreevs;
		for (int i = 0; i < options; i++) {
			if (isScored[i] == false) {
				abreevs.push_back(rules[i]->abbrev);
			}
		}

		return abreevs;
	}
	void YahtzeeGame::scoreRoll(DiceRoll roll, string cat, Scoresheet& sheet) const {

		int rulenum = 0;
		// find which rule it corresponds to
		for (int i = 0; i < options; i++) {
			if (cat.compare(rules[i]->abbrev) == 0){
				rulenum = i;
				break;
			}
		}
		// check see if the user isn't messing with us
		if (sheet.isScored[rulenum]) {
			throw std::invalid_argument("Already Scored");
		}
		// Check see if Yortzee is already scored (if bonuses exist in game)
		if (y_index != -1) {
			// its a yortzee - what is it used for?
			int yortzeescore = rules[y_index]->getScore(roll);
			if (yortzeescore > 0 && sheet.isScored[y_index]) {
				if (rules[rulenum]->getScore(roll) > 0 && sheet.scorenum[y_index] > 0) {
					// if it's scoring a nonzero value, add 5 to the bonus
					sheet.multbonus_count++;
					sheet.scorenum[y_index+1] +=  5*sheet.multbonus_count; 
					
					// cout << sheet.scorenum[y_index+1] << endl;
				}
			}

		}

		// get the score using that rule
		int score = rules[rulenum]->getScore(roll);
		sheet.scorenum[rulenum] = score;
		sheet.isScored[rulenum] = true;

		// update upper bonus
		int bonus = rules[ub_index]->getBonus(sheet.scorenum, ub_index);
		sheet.scorenum[ub_index] = bonus;

		return;
	}

	YahtzeeGame::YahtzeeGame(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index, int y_index){
		this->options = options;
		this->scorenum = scores;
		this->rules = rules;
		this->ub_index = ub_index;
		this->y_index = y_index;
	}
	Scoresheet YahtzeeGame::initialSheet() const{
		return Scoresheet(options, scorenum, rules, ub_index, y_index);
	}
	bool YahtzeeGame::isTerminal(Scoresheet sheet) const {
		bool ret = true;
		for (int i = 0; i < options; i++) {
			if (sheet.isScored[i] == false) {
				ret = false;
				break;
			}
		}
		return ret;
	}
	int getTotal(vector<int> scorenum) {
		int sum = 0;
		for (auto  i = scorenum.begin(); i != scorenum.end(); i++ ) {
			sum+= *i;
		}
		return sum;
	}


	std::ostream& operator<<(std::ostream& os, const Scoresheet& sheet){


		for (int i = 0; i < sheet.options; i++) {
			if (sheet.isScored[i]) {
				os << std::right <<  std::setw(4) << sheet.scorenum[i] << " " ;
			}
			else {
				os << std::setw(4) << "     ";
			}
			os << sheet.rules[i]->name << endl;
		}
		if (sheet.y_index == -1) {

			os << std::right << std::setw(4) <<  getTotal(sheet.scorenum) << " ";
			os << "GRAND TOTAL" << endl;
		}
		return os;
	}
}
