#include "rule.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;
namespace cs427_527 {

  // Scoring mechanism for aces, deuces, treys.. in upper bracket of standard Yahtzee
  int UpperComb::getScore(DiceRoll roll) {
    int count = roll.count(target);
    return (count * target);
  }

  // Scoring method for 3K-5K
  int LowerComb::getScore(DiceRoll roll) {
    // find highest dicecount of 3K-5K
    int num = 0;
    for (int i = 1; i < 7; i++) {
      int count = roll.count(i);
      if (count >= target) {
        num = i;
      }
    }
    if (num != 0) {
      return roll.total();
    }
    return 0;
  }
  int YahtzeeKind::getScore(DiceRoll roll) {
    if (roll.allSame()) {
      return score;
    }
    return 0;
  }

  // just throw whatever in fam
  int Chance::getScore(DiceRoll roll) {
    return roll.total();
  }

  // a little different from every other class
  int FullHouse::getScore(DiceRoll roll) {
    int num1 = 3;
    int num2 = 2;
    for (int i = 1; i < 7; i++) {
      if (roll.count(i) == num1) {
        for (int j = 1; j < 7; j++) {
          if (roll.count(j) == num2) {
            return score;
          }
        }
      }
    }
    return 0;
  }
  // scoring method for large, small straights
  int Straight::getScore(DiceRoll roll) {
    // check it two times for small straight, only once for small roll
    for (int i = 1; i < 8-target; i++) {
      vector<int> straight;
      for (int j = i; j < i+target; j++){
        if (roll.count(j) == 0) {
          break;
        } else {
          straight.push_back(j);
        }
      }
      if (straight.size() == size_t(target)) {
        return score;
      }
    }
    return 0;
  }

  // scoring method for Yortzee version of straights
  int StraightYortzee::getScore(DiceRoll roll) {
    // check 1-5 for low, 2-6 for high
    vector<int> straight;
    for (int j = target; j < target+5; j++){
      if (roll.count(j) == 0) {
        break;
      } else {
        straight.push_back(j);
      }
    }
    if (straight.size() == 5) {
      return score;
    }
    return 0;
  }
  int Yatzie::getScore(DiceRoll roll) {
    // Yatzie scores 30 plus the sum of the dice for five of a kind and 0 otherwise.
    if (roll.allSame()) {
      return (roll.total() + score);
    }
    return 0;
  }

  int YortzeeKind::getScore(DiceRoll roll) {
    // check all 5 dice are different
    for (int i = 1; i < 7; i++) {
      if (roll.count(i) >=2) {
        return 0;
      }
    }
    return score;
  }
  int TwoPair::getScore(DiceRoll roll) { 
    // find first pair
    for (int i = 1; i < 7; i++) {
      if (roll.count(i) >= 4) {
        return roll.total(); 
      }
      else if (roll.count(i) >=2 && roll.count(i) < 4){
        for (int j = i+1; j < 7; j++) {
          if (roll.count(j) >=2) {
            return roll.total();
          }
        }
      }
    }
    return 0;
  }

  // method to handle multiple bonuses
  // void YortzeeKind::multBonus(vector<int>& scorenum, int rulenum, vector<bool> isScored, vector<shared_ptr<Rule>> rules, DiceRoll roll, int y_index) {
  //   //check see that we have a Yortzee
  //   int rollScore = YortzeeKind::getScore(roll);
  //   if (rollScore == 0) {
  //     // don't need to apply bonus, not a Yortzee
  //     return;
  //   }
  //   // its a Yortzee

  //   else if (rules[rulenum]->getScore(roll) > 0) {
  //     int currBonus = scorenum[y_index+1] + 5;
  //     scorenum[y_index+1] += currBonus;
  //     return;
  //   }
  //   else {
  //     // not scored, no bonus needed..just push back up to yahtzee.cpp to finish the job
  //     return;
  //   }
  // }

  // new upper bonus method for Yortzee
  int UpperBonusYortzee::getBonus(vector<int> scorenum, int bIndex) {
    int sum = 0;
    for (int i = 0; i < bIndex; i++) {
      sum+=scorenum[i];
    }
    if (sum >= 42 && sum <= 62) {
      return 15;
    }
    else if (sum >=63 && sum <= 83) {
      return 35;
    }
    else if (sum >=84 && sum <= 104) {
      return 55;
    }
    else if (sum >=105) {
      return 75;
    }
    else {
      return 0;
    }
  }
  // old upper bonus method for Yahtzee
  int UpperBonus::getBonus(vector<int> scorenum,int bIndex) {
    int sum = 0;
    for (int i = 0; i < bIndex; i++) {
      sum+=scorenum[i];
    }
    if (sum >= target) {
      return score;
    }
    return 0;
  }
}
