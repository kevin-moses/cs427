#include "diceroll.hpp"

#include <string>

namespace cs427_527
{
  
  DiceRoll::DiceRoll()
  {
    reroll();
  }

  bool DiceRoll::allSame() const
  {
    int num = 0;
    while (num < NUM_SIDES && counts[num] != NUM_DICE)
      {
	num++;
      }
    return num < NUM_SIDES;
  }

  int DiceRoll::total() const
  {
    int sum = 0;
    for (int i = 0; i < NUM_SIDES; i++)
      {
	sum += (i + 1) * counts[i];
      }
    return sum;
  }

  int DiceRoll::count(int n) const
  {
    return counts[n - 1];
  }

  void DiceRoll::reroll()
  {
    for (int n = 0; n < NUM_SIDES; n++)
      {
	counts[n] = 0;
      }

    for (int i = 0; i < NUM_DICE; i++)
      {
	int roll = rand() % NUM_SIDES;
	counts[roll]++;
      }
  }

  void DiceRoll::reroll(const std::string& keep)
  {
    if (!isValidKeep(keep))
      {
	throw std::invalid_argument("not a valid set of dice to keep: " + keep);
      }

    // zero out dice
    for (int d = 0; d < NUM_SIDES; d++)
      {
	counts[d] = 0;
      }

    // keep dice indicated by string
    for (char ch : keep)
      {
	int num = ch - '1';
	counts[num]++;
      }

    // reroll the rest
    for (size_t i = 0; i < NUM_DICE - keep.length(); i++)
      {
	int roll = rand() % NUM_SIDES;
	counts[roll]++;
      }
  }

  bool DiceRoll::isValidKeep(const string& keep) const
  {
    int kept[NUM_SIDES];
    for (int i = 0; i < NUM_SIDES; i++)
      {
	kept[i] = 0;
      }

    for (char ch : keep)
      {
	int num = ch - '1';
	if (num < 0 || num >= NUM_SIDES)
	  {
	    // invalid number
	    return false;
	  }
	kept[num]++;
	if (kept[num] > counts[num])
	  {
	    // keeping number that wasn't rolled
	    return false;
	  }
      }

    return true;
  }
  
  std::ostream& operator<<(std::ostream& os, const DiceRoll& roll)
  {
    os << '[';
    for (int d = 1; d <= DiceRoll::NUM_SIDES; d++)
      {
	for (int i = 0; i < roll.count(d); i++)
	  {
	    os << ' ' << d;
	  }
      }
    os << " ]";

    return os;
  }

}
