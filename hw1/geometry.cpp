#include <cmath>

#include "geometry.hpp"

namespace geometry
{

  double euclidean_distance(double x1, double y1, double x2, double y2)
  {
    double d = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    return d;
  }
  double colatitude(double x1) {
  	return 90 - x1;
  }
  double to_radians(double angle) {
  	return 0.01745329252 * angle;
  }
  double size_c(double a, double b, double c) {
  	double left = cos(a) * cos(b);
  	double right = sin(a) * sin(b) * cos(c);
  	double tot = acos(left+right);
  	return tot;
  }
}