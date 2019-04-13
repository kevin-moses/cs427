#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>

#include "yahtzee.hpp"
#include "factory.hpp"
#include "diceroll.hpp"

using std::string;

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::find;
using std::copy;
using std::ostream_iterator;

using std::make_shared;
using std::shared_ptr;

using cs427_527::YahtzeeFactory;
using cs427_527::BasicYahtzeeFactory;
using cs427_527::MysteryYahtzeeFactory;
using cs427_527::Scoresheet;
using cs427_527::YahtzeeGame;
using cs427_527::DiceRoll;

#ifdef CPSC527
using cs427_527::YahtzeeState;
#endif

void test_scoring(const YahtzeeGame& game);

int main(int argc, char **argv)
{
  // determine which game we're playing
  shared_ptr<YahtzeeFactory> factory;

  if (argc > 1 && string{"-mystery"} == argv[1])
    {
      factory = make_shared<MysteryYahtzeeFactory>();
    }
  else
    {
      factory = make_shared<BasicYahtzeeFactory>();
    }

  // make the game
  YahtzeeGame game = factory->makeGame();

  // sometimes we just want to check the wscoring rules without worrying
  // about turn mechanics
  if (argc > 2 && string{"-scoring"} == argv[2])
    {
      try
	{
	  test_scoring(game);
	}
      catch (...)
	{
	  cout << "error in scoring test" << endl;
	  return 1;
	}
      return 0;
    }

  // rolls and random if last argument is not -derandomize
  bool randomize = (string{"-derandomize"} != argv[argc - 1]);
  
#ifndef CPSC527
  // get a blank scoresheet
  Scoresheet sheet = game.initialSheet();

  // play one turn until the game is over
  while (!game.isTerminal(sheet))
    {
      // roll
      DiceRoll roll;
      if (!randomize)
	{
	  string dice;
	  getline(cin, dice);

	  if (cin)
	    {
	      try
		{
		  roll = DiceRoll{dice};
		}
	      catch (...)
		{
		  cout << "invalid result of first roll" << endl;
		  return 1;
		}
	    }
	  else
	    {
	      cout << "failed to read result of first roll" << endl;
	      return 1;
	    }
	}
      
      // print the scoresheet
      cout << sheet << endl;

      // player rerolls twice
      for (int r = 0; r < 2; r++)
	{
	  cout << roll << endl;
	  cout << "REROLL " << (r + 1) << endl;

	  string keep;
	  while (getline(cin, keep) && !roll.isValidKeep(keep))
	    {
	      cout << "ILLEGAL MOVE" << endl;
	    }
	  if (!cin)
	    {
	      return 1;
	    }

	  if (randomize)
	    {
	      roll.reroll(keep);
	    }
	  else
	    {
	      string rerolled;
	      getline(cin, rerolled);
	      if (cin)
		{
		  try
		    {
		      roll.reroll(keep, rerolled);
		    }
		  catch (...)
		    {
		      cout << "invalid result of reroll" << endl;
		      return 1;
		    }
		}
	      else
		{
		  cout << "failed to read result of reroll" << endl;
		  return 1;
		}
	    }
	}
      cout << roll << endl;

      // get and display unused categories
      vector<string> options = sheet.unusedCategories();
      copy(options.begin(), options.end(), ostream_iterator<string>(cout, " "));
      cout << endl;

      // player chooses a category
      string cat;
      while (getline(cin, cat)
	     && find(options.begin(), options.end(), cat) == options.end())
	{
	  cout << "ILLEGAL MOVE" << endl;
	}
      if (!cin)
	{
	  return 1;
	}
      
      // mark score
      game.scoreRoll(roll, cat, sheet);
    }

  // game over, output final scoresheet and total
  cout << sheet << endl;
#else
  YahtzeeState state = game.initialState();
  if (!randomize)
    {
      string dice;
      getline(cin, dice);
      
      if (cin)
	{
	  try
	    {
	      state.setRoll(dice);
	    }
	  catch (...)
	    {
	      cout << "invalid result of first roll" << endl;
	      return 1;
	    }
	}
      else
	{
	  cout << "failed to read result of first roll" << endl;
	  return 1;
	}
    }
  while (!state.isTerminal())
    {
      cout << state;
      
      string choice;
      bool valid = false;
      do
	{
	  getline(cin, choice);
	  if (!cin)
	    {
	      return 1;
	    }

	  try
	    {
	      if (state.isEndTurn())
		{
		  // score roll in chosen category
		  state.scoreRoll(choice);
		  
		  // set up start of next turn
		  if (!randomize && !state.isTerminal())
		    {
		      string dice;
		      getline(cin, dice);
		      
		      if (cin)
			{
			  try
			    {
			      state.setRoll(dice);
			    }
			  catch (...)
			    {
			      cout << "invalid result of first roll" << endl;
			      return 1;
			    }
			}
		      else
			{
			  cout << "failed to read result of first roll" << endl;
			  return 1;
			}
		    }
		}
	      else
		{
		  state.reroll(choice);
		  
		  if (!randomize)
		    {
		      string rerolled;
		      getline(cin, rerolled);
		      if (cin)
			{
			  try
			    {
			      state.setRoll(choice + rerolled);
			    }
			  catch (...)
			    {
			      cout << "invalid result of reroll" << endl;
			      return 1;
			    }
			}
		      else
			{
			  cout << "failed to read result of reroll" << endl;
			  return 1;
			}
		    }
		}
	      valid = true;
	    }
	  catch (...)
	    {
	      // OOF! I really should have specified that reroll and scoreRoll
	      // throw some new exception type to simplify the exception
	      // handling throughout.
	      cout << "ILLEGAL MOVE" << endl;
	    }
	}
      while (!valid);
    }
  cout << state;
#endif
}

void test_scoring(const YahtzeeGame& game)
{
#ifndef CPSC527
  // get a blank scoresheet
  Scoresheet sheet = game.initialSheet();

  string dice;
  while (!game.isTerminal(sheet) && cin >> dice)
    {
      // make the roll (throws an exception if invalid)
      DiceRoll roll{dice};
      
      // get and display unused categories
      vector<string> options = sheet.unusedCategories();

      // read chooses a category
      string cat;
      cin >> cat;
      if (cin && find(options.begin(), options.end(), cat) == options.end())
	{
	  throw std::logic_error{"invalid category read"};
	}
      if (!cin)
	{
	  throw std::logic_error{"missing category input"};
	}
      
      // mark score
      game.scoreRoll(roll, cat, sheet);
    }

  // game over, output final scoresheet and total
  cout << sheet << endl;
#else
  YahtzeeState state = game.initialState();
  string dice;
  
  while (!state.isTerminal() && cin >> dice)
    {
      state.setRoll(dice);
      
      string cat;
      cin >> cat;
      if (!cin)
	{
	  throw std::logic_error{"missing category input"};
	}
      state.scoreRoll(cat);
    }
  cout << state << endl;
#endif
}

