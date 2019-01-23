#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "geometry.hpp"

// import java.util.List;
// import java.util.*;
// import java.awt.*;

// from math import sqrt
// from math import *

using std::cin;
using std::cout;
using std::endl;
using std::string;

using namespace std;
double earth_rad = 3959;

/**
 * Compile with
 *
 * g++ -Wall -pedantic -std=c++17 -o Distance distance.cpp
 *
 * and then run with
 *
 * ./Distance
 */
double sum_coord(double x, double y, double z) {
  // if negative degrees, has to distribute
  // cout << x << "\t" << y << "\t" << z << endl;
  if (x < 0) {
    return x - (y/60) - (z/3600);
  }
  else {
    return x + (y/60) + (z/3600);
  }
}


int main(int argc, char **argv)
{

  //read in file 
  double lon1, lat1;
  double lon2, lat2;
  int line_no = 0;
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  string line;
  double total_distance = 0.0;
   // extract from stream cin (standard input)
  while (getline(cin, line) && line_no < 4)
    {
      line_no++;
      stringstream ss(line);
      ss >> x;
      if (!ss.eof()){
         ss >> y;
         if (!ss.eof()) {
          ss >> z;
         }
      }
      switch(line_no) {
        case 1: lat1 = sum_coord(x, y , z);
        break;
        case 2: lon1 = sum_coord(x, y , z);
        break;
        case 3: lat2 = sum_coord(x, y , z);
        break;
        case 4: lon2 = sum_coord(x, y , z);
        break;
      }
    }
  // first compute colatitudes
  double a = geometry::colatitude(lat1);
  double b = geometry::colatitude(lat2);
  // compute difference in longitude
  double big_c = lon2-lon1;
  // convert to radians
  a = geometry::to_radians(a);
  b = geometry::to_radians(b);
  big_c = geometry::to_radians(big_c);
  // compute size C
  double lil_c = geometry::size_c(a, b, big_c);
  // multiply by radius of earth;
  total_distance = lil_c*earth_rad;
  cout << total_distance << endl;
}
