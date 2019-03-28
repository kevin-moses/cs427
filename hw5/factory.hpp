#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include "diceroll.hpp"
#include "yahtzee.hpp"

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

namespace cs427_527
{

  // name + abbreviation
  class Rule {
    virtual int getScore(vector<int> roll) = 0;
    string name;
    string abbrev;
  };
  class UpperComb : public Rule {
    int getScore(vector<int> roll) override;
  protected:
    int target;
  };
  class Ace : public UpperComb {
    target = 1;
    name = "Aces";
    abbrev = "1";
  };
  class Deuce : public UpperComb {
    target = 2;
    name = "Deuces";
    abbrev = "2";
  };
  class Trey : public UpperComb {
    target = 3;
    name = "Treys";
    abbrev = "3";
  };
  class Four : public UpperComb {
    target = 4;
    name = "Fours";
    abbrev = "4";
  };
  class Five : public UpperComb {
    target = 5;
    name = "Fives";
    abbrev = "5";
  };
  class Six : public UpperComb {
    target = 6;
    name = "Fives";
    abbrev = "6";
  };

  // change to make a single method
  class LowerComb: public Rule {
    int getScore(vector<int> roll) override;
  };
  class ThreeKind : public LowerComb {
    name = "Three of a Kind";
    abbrev = "3K";
    target = 3;
  };
  class FourKind : public LowerComb {
    name = "Four of a Kind";
    abbrev = "4K";
    target = 4;
  };
  class FiveKind : public LowerComb {
    name = "Yahtzee";
    abbrev = "Y";
    target = 5;
  };


  class FullHouse : public Rule {
    int getScore(vector<int> roll) override;
    name = "Full House";
    abbrev = "FH";
  };

  class Straight: public Rule {
    int getScore(vector<int> roll) override;
  protected:
    int target;
    int score;
  };
  class SmallStraight: public Straight {
    target = 4;
    score = 30;
    name = "Small Straight";
    abbrev = "SS";
  };
  class LargeStraight: public Straight {
    target = 5;
    score = 40;
    name = "Large Straight";
    abbrev = "LS";
  };
  class Chance: public Rule{
    int getScore(vector<int> roll) override;
    name = "Chance";
    abbrev = "C";
  };
  class UpperBonus: public Rule {
    int getBonus(vector<int> scores, int bIndex);
    int total = 63;
    int award = 53;
  };



  class YahtzeeFactory
  {
  public:
    virtual YahtzeeGame makeGame() return 0;
  };
  class BasicYahtzeeFactory : public YahtzeeFactory{
  	YahtzeeGame makeGame();

  };
  class MysteryYahtzeeeFactory : public YahtzeeFactory {
    YahtzeeGame makeGame();
  };
}

#endif
