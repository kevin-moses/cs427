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
#include "rule.hpp"

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;



//TODO; UPDATE RULES TO SHOW POLYMORPHIC BEHAVIOR A LA https://stackoverflow.com/questions/45686319/c-override-base-member-value
namespace cs427_527
{
  class YahtzeeFactory
  {
  public:
    virtual YahtzeeGame makeGame();
  };
  class BasicYahtzeeFactory : public YahtzeeFactory{
  	YahtzeeGame makeGame();

  };
  class MysteryYahtzeeeFactory : public YahtzeeFactory {
    YahtzeeGame makeGame();
  };

}

#endif
