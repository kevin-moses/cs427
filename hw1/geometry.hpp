#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

namespace geometry
{
  /**
   * Computes the Euclidean distance between two points (x1, y1) and (x2, y2).
   *
   * @param x1 a double
   * @param y1 a double
   * @param x2 a double
   * @param y2 a double
   * @return the Euclidean distance between (x1, y1) and (x2, y2)
   */
  double to_radians(double);
  double euclidean_distance(double, double, double, double);
  /*
   the colatitude is the angle between the point and the North Pole with the center of the Earth as the vertex and can be computed as 90−lat
  */
  double colatitude(double);
  double size_c(double, double, double);
}

#endif