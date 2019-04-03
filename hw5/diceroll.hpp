#ifndef __DICEROLL_HPP__
#define __DICEROLL_HPP__

#include <iostream>
#include <string>

using std::string;

using std::ostream;

namespace cs427_527
{

  /**
   * The result of rolling five six-sided dice.
   */
  class DiceRoll
  {
  public:
    /**
     * Creates a new roll with random numbers showing on each die.
     */
    DiceRoll();

    /**
     * Creates a roll with the given numbers showing on each die.
     *
     * @param s a string of NUM_DICE digts from 1 to NUM_SIDES
     */
    DiceRoll(const string& s);
    
    /**
     * Determines if all dice in this roll are showing the same number.
     *
     * @return true if and only if all dice are showing the same number.
     */
    bool allSame() const;

    /**
     * Returns the total of all the numbers showing on the dice in this roll.
     *
     * @return the total showing on all the dice
     */
    int total() const;

    /**
     * Returns the number of dice showing the given number.
     *
     * @param n a number between 1 and NUM_SIDES inclusive
     * @return the number of dice showing that number
     */
    int count(int n) const;

    /**
     * Rerolls all the dice in this roll.
     */
    void reroll();

    /**
     * Rerolls all the dice in this roll except the ones showing the
     * digits in the given string.
     *
     * @param keep a string representing the numbers showing on a subset
     * of the dice in this roll
     */
    void reroll(const std::string& keep);

    /**
     * Rerolls all the dice in this roll except the ones showing the
     * digits in the given string.
     *
     * @param keep a string representing the numbers showing on a subset
     * of the dice in this roll
     * @param rolled a string of digits from 1 to NUM_SIDES of length
     * equal to NUM_DICE minus the length of keep
     */
    void reroll(const std::string& keep, const std::string& rolled);

    /**
     * Determines if the given string represents the numbers showing on
     * some subset of the dice in this roll.
     *
     * @param keep a string of digits
     * @return true if and only if keep represents a subset of this roll
     */
    bool isValidKeep(const std::string& keep) const;

    /**
     * The number of sides on the dice in this roll.
     */
    static const int NUM_SIDES = 6;

    /**
     * The number of dice in this roll.
     */
    static const int NUM_DICE = 5;

  private:
    int counts[NUM_SIDES];
  };

  /**
   * Outputs a printable representation of the given roll to the given stream.
   *
   * @param os an output string
   * @param roll a roll
   */
  ostream& operator<<(ostream& os, const DiceRoll& roll);
  
}
  
#endif
