#include "factory.cpp"
#include <vector>
#include <memory>
using std::string;
using std::vector;
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
  // Helper method for 3K-5K
  int sumDice(vector<int> roll) {
    int size = 0;
    for (int i = 0; i < roll.size(); i++) {
      size+=roll[i];
    }
    return size;
  }
  // Scoring method for 3K-5K
  int LowerComb::getScore(Diceroll roll) {
    // find highest dicecount of 3K-5K
    int num = 0;
    for (int i = 1; i < 7; i++) {
      int count = roll.count(i);
      if (count >= target) {
        num = i;
      }
    }
    if (num != 0) {
      return dice.total();
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
  int FullHouse::getScore(Diceroll roll) {
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
      if (j.size() == target) {
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
    if (sum >= total) {
      return award;
    }
    return 0;
  }


  YahtzeeGame BasicYahtzeeFactory::makeGame()  {
  	// make array of options
  	const int options = 14;
  	vector<int> scores;
    vector<Rule> rules;
    const int ub_index = 6;

    // Fill vector of rules
    auto ace = make_shared<Ace>();
    rules.push_back(ace);
    auto deuce = make_shared<Deuce>();
    rules.push_back(deuce);
    auto three = make_shared<Trey>();
    rules.push_back(three);
    auto four = make_shared<Four>();
    rules.push_back(four);
    auto five = make_shared<Five>();
    rules.push_back(five);
    auto six = make_shared<Six>();
    rules.push_back(six);
    auto ub = make_shared<UpperBonus>();
    rules.push_back(ub);
    auto kthree = make_shared<ThreeKind>();
    rules.push_back(kthree);
    auto kfour = make_shared<FourKind>();
    rules.push_back(kfour);
    auto fh = make_shared<FullHouse>();
    rules.push_back(fh);
    auto ss = make_shared<SmallStraight>();
    rules.push_back(ss);
    auto ls = make_shared<LargeStraight>();
    rules.push_back(ls);
    auto yh = make_shared<FiveKind>();
    rules.push_back(yh);
    auto ch = make_shared<Chance>();
    rules.push_back(ch);
    // initialize scores to 0
    for (int i = 0; i < options; i++) {
      scores.push_back(0);
    }
    // feed into new game
  	YahtzeeGame g = YahtzeeGame(options, scores, rules, ub_index);
  	return g;
  }



  YahtzeeGame MysteryYahtzeeFactory::makeGame() override {

  }
}
