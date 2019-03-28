#include "factory.cpp"
#include <vector>
using std::string;
using std::vector;
using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

namespace cs427_527 {

  // Scoring mechanism for aces, deuces, treys.. in upper bracket of standard Yahtzee
  int UpperComb::getScore(vector<int> roll) {
    int count = 0;
    for (int i = 0; i < roll.size(); i++) {
      if (roll[i] == target) {
        count++;
      }
    }
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
  int LowerComb::getScore(vector<int> roll) {
    std::sort(roll.begin(), roll.end());
    for (int i = 0; i < roll.size(); i++) {
      int attempt = roll[i];
      int count = 0;
      for (int j = i; j < roll.size(); j++) {
        if (roll[j]  == attempt) {
          count++;
        }
        if (count == target){
          return sumDice(roll);
        }
      }
    }
    return 0;
  }
  // just throw whatever in fam
  int Chance::getScore(vector<int> roll) {
    return sumDice(roll);
  }
  // a little different from every other class
  int FullHouse::getScore(vector<int> roll) {
    // check that there's a 3K
    std::sort(roll.begin(), roll.end());
    while (i < 3) {
      if (roll[i+1] == roll[i] && roll[i+2] == roll[i]) {
        // case 1: lower full house, check upper pair
        if (i == 0) {
          if (roll[3] == roll[4]) {
            return 25;
          }
        }
        // case 2: upper full house, check lower pair
        if (i == 2) {
          if (roll[0] == roll[1]) {
            return 25;
          }
        }
      }
    return 0;
  }
  // scoring method for large, small straights
  int Straight::getScore(vector<int> roll) {
    std::sort(roll.begin(), roll.end());
    int sequence = 0;
    for (int i = 0; i < roll.size(); i++) {
      vector<int> straight;
      straight.push_back(roll[i]);
      for (int j = i; j < roll.size(); j++) {
        if (roll[j] - straight.back() == 1) {
          straight.push_back(roll[j]);
        }
      }
      if (straight.size() == target) {
        return score;
      }
    }
    return 0;
  }

  int UpperBonus::getBonus(vector<Rule> scores, int bIndex) {
    int sum = 0;
    for (int i = 0; i < bIndex; i++) {
      sum+=scores[i];
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
