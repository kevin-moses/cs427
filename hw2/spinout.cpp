#include "spinout.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

namespace cs427_527 {
			/*
		A constructor SpinOut() that initializes the puzzle so all disks are vertical.
		*/
		SpinOut::SpinOut() {
			for (int i = 0; i < SIZE; i++) {
				disks[i] = false;
			}
		}
		
		/*
		A constructor SpinOut(const std::string& s) that initializes the puzzle according to the given string. The string will consist of 7 characters, each of which is '/' or '-' respectively to indicate a disk that is intially vertical or horizontal respectively.
		*/
		SpinOut::SpinOut(const std::string& s) {
			for (int i = 0; i < SIZE; i++) {
				if (s.at(i) == '-') {
					disks[i] = true;
				}
				else if (s.at(i) == '/') {
					disks[i] = false;
				}
				else {
					disks[i] = false;
				}
			}
		}
		
		/*
		A method bool isLegalMove(int i) const which takes an integer between 0 and 6 inclusive and determines whether it is possible to rotate that disk in the current object to its other orientation. Disks are numbered from left to right starting with zero.
		*/
		bool SpinOut::isLegalMove(int i) const{
			if (i == (SIZE-1)) {
				return true;
			} else {
				// check if disk to right is vertical
				if (disks[i+1] == true) {
					return false;
				}
				for (int j = i+1; j < SIZE; j++) {
					if (disks[j] == false) {
						return false;
					}
				}
			}
			return true;
		}
		
		/*
		A method void makeMove(int i) which takes an integer for which isLegalMove returns true and rotates the indicated disk in the current object into its other orientation.
		*/
		void SpinOut::makeMove(int i)  {
			if (SpinOut::isLegalMove(i) == true) {
				if (disks[i] == true) {
					disks[i] = false;
					moves++;
					return;
				} else {
					disks[i] = true;
					moves++;
				}
			}
			return;
		}
		
		/*
		A method int totalMoves() const which counts the number of legal moves performed on the current object since it was created.
		*/
		int SpinOut::totalMoves() const {
			return moves;
		}
		
		/*
		A method bool isSolved() const which determines if the current object is in its solved configuration (all disks rotated horizontally).
		*/
		bool SpinOut::isSolved() const {
			for (int i = 0; i < SIZE; i++) {
				if (disks[i] == false) {
					return false;
				}
			}
			return true;
		}
		
		/*
		A method std::string toString() const which returns a string representation of the current object in the same format as that passed to the second version of the constructor.
		*/
		std::string SpinOut::toString() {
			std::stringstream ss;
			for (int i = 0; i < SIZE; i++) {
				if (disks[i] == false){
					ss << "/";
				} else {
					ss << "-";
				}
			}
			return ss.str();
		}
}