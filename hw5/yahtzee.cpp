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
	Scoresheet::Scoresheet(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index){
		this->options = options;
		this->scorenum = scores;
		this->rules = rules;
		this->ub_index = ub_index;
		for (int i = 0; i < options; i++) {
			isScored.push_back(false);
		}
		isScored[ub_index] = true;
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

		// get the score using that rule
		int score = rules[rulenum]->getScore(roll);
		sheet.scorenum[rulenum] = score;
		sheet.isScored[rulenum] = true;


		return;
	}

	YahtzeeGame::YahtzeeGame(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index){
		this->options = options;
		this->scorenum = scores;
		this->rules = rules;
		this->ub_index = ub_index;
	}
	Scoresheet YahtzeeGame::initialSheet() const{
		return Scoresheet(options, scorenum, rules, ub_index);
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
		os << std::right << std::setw(4) <<  getTotal(sheet.scorenum) << " ";
		os << "GRAND TOTAL" << endl;
		return os;
	}
}
