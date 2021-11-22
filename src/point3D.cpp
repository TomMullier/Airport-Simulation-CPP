#include "../headers/point3D.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;

Point3D::Point3D() {
  x = rand() % 101;
  y = rand() % 101;
  z = rand() % 101;
};
Point3D::Point3D(const float &newx, const float &newy, const float &newz) {
  x = newx;
  y = newy;
  z = newz;
};

void Point3D::setXYZ(const float &newx, const float &newy, const float &newz) {
  x = newx;
  y = newy;
  z = newz;
};
void Point3D::setX(const float &newx) { x = newx; };
void Point3D::setY(const float &newy) { y = newy; };
void Point3D::setZ(const float &newz) { z = newz; };

float Point3D::getX() { return x; };

float Point3D::getY() { return y; };

float Point3D::getZ() { return z; };

float Point3D::distanceTo(Point3D &otherPoint3D) {
  return sqrt(pow(otherPoint3D.getX() - x, 2) +
              pow(otherPoint3D.getY() - y, 2) +
              pow(otherPoint3D.getZ() - z, 2));
};

bool Point3D::operator<(const Point3D &pos) {
  if (this->x < pos.x)
    return true;
  if (this->y < pos.y)
    return true;
  if (this->z < pos.z)
    return true;
  return false;
}

ostream &operator<<(ostream &os, const Point3D &position) {
  os << "(" << position.x << ", " << position.y << ", " << position.z << ")"
     << endl;
  return os;
}