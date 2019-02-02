#ifndef __SPINOUT_HPP__
#define __SPINOUT_HPP__

#include <iostream>
#include <string>


namespace cs427_527 {
	class SpinOut {
	public:
		static const int SIZE =7;
		/*
		A constructor SpinOut() that initializes the puzzle so all disks are vertical.
		*/
		SpinOut();
		
		/*
		A constructor SpinOut(const std::string& s) that initializes the puzzle according to the given string. The string will consist of 7 characters, each of which is '/' or '-' respectively to indicate a disk that is intially vertical or horizontal respectively.
		*/
		SpinOut(const std::string& s);
		
		/*
		A method bool isLegalMove(int i) const which takes an integer between 0 and 6 inclusive and determines whether it is possible to rotate that disk in the current object to its other orientation. Disks are numbered from left to right starting with zero.
		*/
		bool isLegalMove(int i) const;
		
		/*
		A method void makeMove(int i) which takes an integer for which isLegalMove returns true and rotates the indicated disk in the current object into its other orientation.
		*/
		void makeMove(int i);
		
		/*
		A method int totalMoves() const which counts the number of legal moves performed on the current object since it was created.
		*/
		int totalMoves() const;
		
		/*
		A method bool isSolved() const which determines if the current object is in its solved configuration (all disks rotated horizontally).
		*/
		bool isSolved() const;
		
		/*
		A method std::string toString() const which returns a string representation of the current object in the same format as that passed to the second version of the constructor.
		*/
		std::string toString();

	private:
		// 0 if horizontal, 1 if vertical
		bool disks[SIZE];
		int moves = 0;
	};
}

#endif