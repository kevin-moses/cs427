#ifndef __RULE_HPP__
#define __RULE_HPP__

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "diceroll.hpp"

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

namespace cs427_527 {

  // name + abbreviation

  class IRule{
  public:
    virtual ~IRule() {}
    virtual int getScore(DiceRoll roll) = 0;
  };
  class Rule : public IRule{
  public:
    ~Rule() {}
    string name;
    string abbrev;
  };
  class UpperComb : public Rule {
  public:
    int getScore(DiceRoll roll) override;
  protected:
    int target;
  };
  class Ace : public UpperComb {
  public:
    Ace(){
      target = 1;
      name = "Aces";
      abbrev = "1";
    }
  };
  class Deuce : public UpperComb {
  public:
    Deuce() {

    target = 2;
    name = "Deuces";
    abbrev = "2";
    }
  };
  class Trey : public UpperComb {
  public:

    Trey() {

    name = "Treys";
    abbrev = "3";
    target = 3;
    }
  };
  class Four : public UpperComb {
  public:
    Four() {

    target = 4;
    name = "Fours";
    abbrev = "4";
    }
  };
  class Five : public UpperComb {
  public:
    Five() {

    target = 5;
    name = "Fives";
    abbrev = "5";
    }
  };
  class Six : public UpperComb {
  public:
    Six(){

    target = 6;
    name = "Sixes";
    abbrev = "6";
    }
  };

  // change to make a single method
  class LowerComb: public Rule {
  public:
    int getScore(DiceRoll roll) override;
  protected:
    int target;
  };
  class ThreeKind : public LowerComb {
  public:
    ThreeKind(){
      name = "Three of a Kind";
      abbrev = "3K";
      target = 3;
    }
  };
  class FourKind : public LowerComb {
  public:
    FourKind() {
      name = "Four of a Kind";
      abbrev = "4K";
      target = 4;
    }
  };
  class YahtzeeKind : public Rule {
  public:
    int getScore(DiceRoll roll) override;
    YahtzeeKind() {
      name = "Yahtzee";
      abbrev = "Y";
    }
    int score = 50;
  };
  class FullHouse : public Rule {
  public:
    int getScore(DiceRoll roll) override;
    FullHouse() {
      name = "Full House";
      abbrev = "FH";
    }
    int score = 25;
  };

  class Straight: public Rule {
  public:
    int getScore(DiceRoll roll) override;
  protected:
    int target;
    int score;
  };
  class SmallStraight: public Straight {
  public:
    SmallStraight() {
      target = 4;
      score = 30;
      name = "Small Straight";
      abbrev = "SS";
    }
  };
  class LargeStraight: public Straight {
  public:
    LargeStraight() {
      target = 5;
      score = 40;
      name = "Large Straight";
      abbrev = "LS";
    }
  };
  class Chance: public Rule{
  public:
    int getScore(DiceRoll roll) override;
    Chance(){
      name = "Chance";
      abbrev = "C";
    }
  };
  class UpperBonus: public Rule {
  public:
    int getScore(DiceRoll roll) override {return 0;}
    int getBonus(vector<int> scorenum, int bIndex);
    UpperBonus() {
      name = "UPPER BONUS";
    }
    int target = 63;
    int score = 53;
  };
}
#endif
