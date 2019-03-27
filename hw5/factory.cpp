#include "factory.cpp"
#include <vector>
using std::string;
using std::vector;

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
  int sumDice(vector<int> roll) {
    int size = 0;
    for (int i = 0; i < roll.size(); i++) {
      size+=roll[i];
    }
    return size;
  }
  int Chance::getScore(vector<int> roll) {
    return sumDice(roll);
  }

  int ThreeKind::getScore(vector<int> roll) {
    // sort. the
    std::sort(roll.begin(), roll.end());
    int i = 0;
    while (i < 3) {
      if (roll[i+1] == roll[i] && roll[i+2] == roll[i]) {
        return sumDice(roll);
      }
      i++;
    }
    return 0;
  }
  int FourKind::getScore(vector<int> roll) {
    // sort. the
    std::sort(roll.begin(), roll.end());
    int i = 0;
    while (i < 2) {
      if (roll[i+1] == roll[i] && roll[i+2] == roll[i] && roll[i+3] == roll[i]) {
        return sumDice(roll);
      }
      i++;
    }
    return 0;
  }
  int FiveKind::getScore(vector<int> roll) {
    if (roll[0] == roll[1] && roll[0] == roll[2] && roll[0] == roll[3] && roll[0] == roll[4]) {
      return 50;
    }
    return 0;
  }
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

  YahtzeeGame BasicYahtzeeFactory::makeGame()  {
  	// make array of options
  	const int options = 13;
  	vector<int> scorenum;
    vector<rule> rules;
  	vector<string> scorename;
  	// give names to scores
  	scorename.push_back("Aces");
  	scorename.push_back("Deuces");
  	scorename.push_back("Treys");
  	scorename.push_back("Fours");
  	scorename.push_back("Fives");
  	scorename.push_back("Sixes");
  	scorename.push_back("Three of a Kind");
  	scorename.push_back("Four of a Kind");
  	scorename.push_back("Full House");
  	scorename.push_back("Small Straight");
  	scorename.push_back("Large Straight");
  	scorename.push_back("Chance");
  	scorename.push_back("Yahtzee");
  	int bonus = 0;
  	bool isBonus = false;
  	YahtzeeGame g = YahtzeeGame(options, scorenum, scorename, isBonus, bonus);
  	return g;
  }



  YahtzeeGame MysteryYahtzeeFactory::makeGame() override {
  	// make array of options
  	const int options = 13;
  	vector<int> scorenum;
  	vector<string> scorename;
  	// set scores to -1
  	for (int i = 0; i < options; i++){
  		scorenum.push_back(-1);
  	}
  	// give names to scores
  	scorename.push_back("Aces");
  	scorename.push_back("Deuces");
  	scorename.push_back("Treys");
  	scorename.push_back("Fours");
  	scorename.push_back("Fives");
  	scorename.push_back("Sixes");
  	scorename.push_back("Three of a Kind");
  	scorename.push_back("Four of a Kind");
  	scorename.push_back("Full House");
  	scorename.push_back("Small Straight");
  	scorename.push_back("Large Straight");
  	scorename.push_back("Chance");
  	scorename.push_back("Yahtzee");
  	int bonus = 0;
  	bool isBonus = false;
  	YahtzeeGame g = YahtzeeGame(options, scorenum, scorename, isBonus, bonus);
  	return g;
  }
}
