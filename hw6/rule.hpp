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
    virtual int getBonus(vector<int> scorenum, int bIndex) = 0;
    // virtual void multBonus(vector<int>& scorenum,int rulenum, vector<bool> isScored, vector<shared_ptr<Rule>> rules, DiceRoll roll, int y_index) = 0;
    virtual int getScore(DiceRoll roll) = 0;
  };
  class Rule : public IRule{
  public:
    ~Rule() {}
    int getBonus(vector<int> scorenum, int bIndex) {return 0;}
    // void multBonus(vector<int>& scorenum,int rulenum, vector<bool> isScored, vector<shared_ptr<Rule>> rules, DiceRoll roll, int y_index) {return;}
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
    int getBonus(vector<int> scorenum, int bIndex) override;
    UpperBonus() {
      name = "UPPER BONUS";
    }
    int target = 63;
    int score = 35;
  };

  // extending rule class for Yortzee

  //two pair is just a pair combination
  class TwoPair : public Rule {
  public:
    int getScore(DiceRoll roll) override;
    TwoPair(){
      name = "Two Pair";
      abbrev = "2P";
    }
  };
  //Small and Large straight different from Low and High Straight, so need different Straight Class
  class StraightYortzee: public Rule {
    public:
      int getScore(DiceRoll roll) override;
    protected:
      int target;
      int score;
  };
  class LowStraight: public StraightYortzee {
  public:
    LowStraight() {
      target = 1;
      score = 25;
      name = "Low Straight";
      abbrev = "LS";
    }
  };
  class HighStraight: public StraightYortzee {
  public:
    HighStraight() {
      target = 2;
      score = 30;
      name = "High Straight";
      abbrev = "HS";
    }
  };
  class Yatzie: public Rule {
    public:
      int getScore(DiceRoll roll) override;
      Yatzie(){
        name = "Yatzie";
        abbrev = "Y";
      }
      int score = 30;
  };
  class YortzeeKind: public Rule {
    public:
      int getScore(DiceRoll roll) override;
      // void multBonus(vector<int>& scorenum,int rulenum, vector<bool> isScored, vector<shared_ptr<Rule>> rules, DiceRoll roll, int y_index);
      YortzeeKind(){
        name = "Yortzee";
        abbrev = "Z";
      }
      int score = 15;
  };
  class UpperBonusYortzee: public Rule {
    public:
      int getScore(DiceRoll roll) override {return 0;}
      int getBonus(vector<int> scorenum, int bIndex) override;
      UpperBonusYortzee() {
        name = "UPPER BONUS";
      }
  };
  class YortzeeBonus: public Rule {
  public:
    int getScore(DiceRoll roll) override {return 0;}
    YortzeeBonus() {
      name = "YORTZEE BONUS";
    }
    int score = 5;
  };

}
#endif
