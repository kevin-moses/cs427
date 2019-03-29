#ifndef __YAHTZEE_HPP__
#define __YAHTZEE_HPP__
#include <iostream>
#include <memory>
#include <vector>
#include <bitset>
#include <string>
#include "factory.hpp"
#include "diceroll.hpp"

using std::vector;
using std::bitset;
using std::string;
using std::shared_ptr;


namespace cs427_527
{


// use scoresheet instead of YahtzeeState
  class Scoresheet {
    Scoresheet(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index);
    vector<string> unusedCategories();
  private:
    int options;
    vector<int> scorenum;
    vector<shared_ptr<Rule>> rules;
    int ub_index;
    vector<bool> isScored;
  }
  std::ostream& operator<<(std::ostream& os, const Scoresheet& sheet);

  class YahtzeeGame {
    public:
      YahtzeeGame(int options, vector<int> scores, vector<shared_ptr<Rule>> rules, int ub_index);
      Scoresheet initialSheet();
      bool isTerminal(Scoresheet sheet);
      scoreroll(Diceroll roll, string cat, Scoresheet sheet);

    private:
      const int maxTurns = 3;
      int turn;
      int options;
      vector<int> scorenum;
      vector<shared_ptr<Rule>> rules;
      int ub_index;

  };


}

#endif
