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
using std::vector

namespace cs427_527
{

  class Rule {
    virtual int getScore(vector<int> roll) = 0;
  };
  class UpperComb : public Rule {
    int getScore(vector<int> roll) override;
  protected:
    int target;
  };
  class Ace : public UpperComb {
    target = 1;
  };
  class Deuce : public UpperComb {
    target = 2;
  };
  class Trey : public UpperComb {
    target = 3;
  };
  class Four : public UpperComb {
    target = 4;
  };
  class Five : public UpperComb {
    target = 5;
  };
  class Six : public UpperComb {
    target = 6;
  };

  class ThreeKind : public Rule {
    int getScore(vector<int> roll) override;
  };
  class FourKind : public Rule {
    int getScore(vector<int> roll) override;
  };
  class FullHouse : public Rule {
    int getScore(vector<int> roll) override;
  };
  class FiveKind : public Rule {
    int getScore(vector<int> roll) override;
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
  };
  class LargeStraight: public Straight {
    target = 5;
    score = 40;
  };
  class Chance: public Rule{
    int getScore(vector<int> roll) override;
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
