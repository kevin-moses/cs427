#include <iostream>

#include "spinout.hpp"

using std::cout;
using std::cin;
using std::endl;

using cs427_527::SpinOut;

void testSolved(const SpinOut& game);
void testTotalMoves(const SpinOut& game);
void testLegalMove(const SpinOut& game, int pos);
void testMakeMove(SpinOut& game, int pos);
void testIllegalPosition(const SpinOut& game, int pos);

int main(int argc, char **argv)
{
  int test;
  try
    {
      if (argc < 2)
	{
	  throw std::invalid_argument("no command-line arguments");
	}
      test = std::stod(std::string(argv[1]));
    }
  catch (...)
    {
      cout << "USAGE: " << argv[0] << " test-number" << endl;
      return 1;
    }

  auto game = SpinOut{};
  
  switch (test)
    {
    case 0:
      testSolved(game);
      break;

    case 1:
      testTotalMoves(game);
      break;

    case 2:
      testLegalMove(game, 4);
      break;

    case 3:
      testLegalMove(game, 5);
      break;
      
    case 4:
      testLegalMove(game, 6);
      break;

    case 5:
      {
	auto start = SpinOut{"------/"};
	testMakeMove(start, SpinOut::SIZE - 1);
      }
      break;

    case 6:
      testIllegalPosition(game, 7);
      break;
      
    default:
      cout << argv[0] << ": invalid test number " << argv[1] << endl;
    }

  return 0;
}

void testSolved(const SpinOut& game)
{
  cout << "solved: " << game.isSolved() << endl;
}

void testTotalMoves(const SpinOut& game)
{
  cout << "total moves: " << game.totalMoves() << endl;
}

void testLegalMove(const SpinOut& game, int pos)
{
  cout << "isLegalMove(" << pos << "): " << game.isLegalMove(pos) << endl;
}

void testMakeMove(SpinOut& game, int pos)
{
  cout << game.toString() << " spinning " << pos << " gives ";
  game.makeMove(pos);
  cout << game.toString() << endl;
}

void testIllegalPosition(const SpinOut& game, int pos)
{
  try
    {
      game.isLegalMove(pos);
    }
  catch (const std::invalid_argument& e)
    {
      cout << "caught exception" << endl;
    }
  catch (const std::out_of_range& e)
    {
      cout << "caught exception" << endl;
    }
}
