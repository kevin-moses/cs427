#ifndef __YAHTZEE_HPP__
#define __YAHTZEE_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include <bitset>
#include <string>

#include "diceroll.hpp"
#include "rule.hpp"

using std::vector;
using std::bitset;
using std::string;
using std::shared_ptr;
namespace cs427_527
{
  class YahtzeeState;
// use scoresheet instead of YahtzeeState
  class Scoresheet {
  public:
    Scoresheet(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index, int y_index);
    vector<string> unusedCategories();
    int options;
    vector<int> scorenum;
    vector<shared_ptr<Rule>> rules;
    int ub_index;
    int y_index;
    int multbonus_count;
    vector<bool> isScored;
  };

  std::ostream& operator<<(std::ostream& os, const Scoresheet& sheet);

  class YahtzeeGame {
  public:
    YahtzeeGame(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index, int y_index);
    Scoresheet initialSheet() const;
    bool isTerminal(Scoresheet sheet) const;
    void scoreRoll(DiceRoll roll, string cat, Scoresheet& sheet) const;

    int options;
    vector<int> scorenum;
    vector<shared_ptr<Rule>> rules;
    int ub_index;
    int y_index;

  };
}

#endif
