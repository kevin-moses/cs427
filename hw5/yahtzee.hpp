#ifndef __YAHTZEE_HPP__
#define __YAHTZEE_HPP__
#include <iostream>

#include <vector>
#include <bitset>
#include <string>

#include "diceroll.hpp"

using std::vector;
using std::bitset;
using std::string;

namespace cs427_527
{

  class YahtzeeState
  {
  public:
    bool isTerminal() const;
    bool isEndTurn() const;
    void scoreRoll(const string choice);
    void reRoll(const string choice);
    void update(int cat, int score);
    void total(std::ostream& os) const;
  
  private:
    const YahtzeeGame& game;
  
  };

  std::ostream& operator<<(std::ostream& os, const YahtzeeState& sheet);

  class YahtzeeGame {
    public:
      YahtzeeGame(int options, vector<int> scorenum, vector<string> scorename, bool isBonus, int bonus);
      YahtzeeState initialState();
    private:
      vector<bitset<6>> scoringDice;
      const int maxTurns = 3;
      int turn;
      int options;
      vector<int> scorenum;
      vector<string> scorename;
      bool isBonus;
      int bonus;
  };

  
}

#endif