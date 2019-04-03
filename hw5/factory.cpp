#include "factory.hpp"

#include <vector>
#include <memory>

#include "diceroll.hpp"
#include "yahtzee.hpp"
#include "rule.hpp"

using std::string;
using std::vector;
using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

namespace cs427_527 {

  YahtzeeGame BasicYahtzeeFactory::makeGame()  {
  	// make array of options
  	const int options = 14;
  	vector<int> scores;
    vector<shared_ptr<Rule>> rules;
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
    auto ch = make_shared<Chance>();
    rules.push_back(ch);
    auto yh = make_shared<YahtzeeKind>();
    rules.push_back(yh);
    // initialize scores to 0
    for (int i = 0; i < options; i++) {
      scores.push_back(0);
    }
    // feed into new game
  	YahtzeeGame g = YahtzeeGame(options, scores, rules, ub_index);
  	return g;
  }



  YahtzeeGame MysteryYahtzeeFactory::makeGame()  {
      	// make array of options
  	const int options = 14;
  	vector<int> scores;
    vector<shared_ptr<Rule>> rules;
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
    auto ch = make_shared<Chance>();
    rules.push_back(ch);
    auto yh = make_shared<YahtzeeKind>();
    rules.push_back(yh);
    // initialize scores to 0
    for (int i = 0; i < options; i++) {
      scores.push_back(0);
    }
    // feed into new game
  	YahtzeeGame g = YahtzeeGame(options, scores, rules, ub_index);
  	return g;
  }
}
