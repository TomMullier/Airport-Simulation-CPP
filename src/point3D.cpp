#include "../headers/point3D.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;

/**
 * Constructor of Point3D without argument
 *
 * @return  Point3D created and attributs set
 */
Point3D::Point3D() {
  x = rand() % 101;
  y = rand() % 101;
  z = rand() % 101;
};

/**
 * Constructor of Point3D with arguments
 *
 * @param   float    newx  first coordinate (x)
 * @param   float    newy  second coordinate (y)
 * @param   float    newz  third coordinate (z)
 *
 * @return  Point3D         Point3D created and attributs set
 */
Point3D::Point3D(const float &newx, const float &newy, const float &newz) {
  x = newx;
  y = newy;
  z = newz;
};

/**
 * Set coordinates
 *
 * @param   float  newx  remplace first coordinate (x)
 * @param   float  newy  remplace second coordinate (y)
 * @param   float  newz  remplace third coordinate (z)
 *
 * @return  void
 */
void Point3D::setXYZ(const float &newx, const float &newy, const float &newz) {
  x = newx;
  y = newy;
  z = newz;
};

/**
 * Distance between 2 points
 *
 * @return  float   Distance between the 2 points
 */
float Point3D::distanceTo(Point3D &otherPoint3D) {
  return sqrt(pow(otherPoint3D.getX() - x, 2) +
              pow(otherPoint3D.getY() - y, 2) +
              pow(otherPoint3D.getZ() - z, 2));
};

/**
 * Operator ==
 *
 * @return  bool    true if points are the same
 */
bool Point3D::operator==(const Point3D &pos) {
  if (this->x == pos.x && this->y == pos.y && this->z == pos.z)
    return true;
  else
    return false;
}

/**
 * Operator << overloaded
 *
 * @return  ostream information to print
 */
ostream &operator<<(ostream &os, const Point3D &position) {
  os << "(" << position.x << ", " << position.y << ", " << position.z << ")"
     << endl;
  return os;
}