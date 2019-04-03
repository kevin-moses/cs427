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

  int UpperBonus::getBonus(vector<int> scorenum, int bIndex) {
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
