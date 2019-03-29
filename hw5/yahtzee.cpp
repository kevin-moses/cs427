#include <iostream>

#include <vector>
#include <bitset>
#include <string>

#include "diceroll.hpp"
#include "yahtzee.hpp"

using std::vector;
using std::bitset;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;


namespace cs427_527
{
	Scoresheet::Scoresheet(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index){
		this.options = options;
		this.scores = scores;
		this.rules = rules;
		this.ub_index = ub_index;
		for (int i = 0; i < options; i++) {
			isScored.push_back(false);
		}
		isScored(ub_index) = true;
	}

	vector<string> Scoresheet::unusedCategories() {
		vector<string> abreevs;
		for (int i = 0; i < options; i++) {
			if (isScored[i] == false) {
				abreevs.push_back(rules[i].abbrev);
			}
		}
		return abbrevs;
	}
	YahtzeeGame::scoreroll(Diceroll roll, string cat, Scoresheet sheet){
		int rulenum = 0;
		// find which rule it corresponds to
		for (int i = 0; i < options; i++) {
			if (compare(cat,rules[i].abbrev) == 0){
				rulenum = i;
				break;
			}
		}

		// get the score using that rule
		int score = rules[rulenum].getScore(roll);
		sheet.scorenum[rulenum] = score;
		sheet.isScored[rulenum] = true;
		return;
	}

	YahtzeeGame::YahtzeeGame(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index){
		this.options = options;
		this.scores = scores;
		this.rules = rules;
		this.ub_index = ub_index;
	}
	Scoresheet YahtzeeGame::initialSheet(){
		return Scoresheet(options, scores, rules, ub_index);
	}
	bool YahtzeeGame::isTerminal(Scoresheet sheet) {
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
		for (int i = 0; i < rules.size(); i++) {
			sum+=scorenum[i];
		}
		return sum;
	}
	std::ostream& operator<<(std::ostream& os, const Scoresheet& sheet){
		for (int i = 0; i < sheet.options; i++) {
			if (sheet.isScored[i] == true) {
				cout.width(6);
				cout << std::right << sheet.scorenum[i] << " ";
			}
			else {
				cout.width(6);
				cout << std::right;
			}
			cout << sheet.rules[i].name << endl;
		}
		cout.width(6);
		cout << std::right << getTotal(sheet.scorenum) << " " << "GRAND TOTAL" << endl;
	}
}
