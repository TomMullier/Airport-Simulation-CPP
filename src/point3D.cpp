#include "../headers/point3D.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

Point3D::Point3D() {
  x = rand() % 101;
  y = rand() % 101;
  z = rand() % 101;
};
Point3D::Point3D(const float &newx, const float &newy, const float &newz) {
  x = newx;
  y = newy, z = newz;
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

void Point3D::print() {
  cout << "x = " << x << " , y = " << y << " , z = " << z << endl;
};
float Point3D::distanceTo(Point3D &otherPoint3D) {
  return sqrt(pow(otherPoint3D.getX() - x, 2) +
              pow(otherPoint3D.getY() - y, 2) +
              pow(otherPoint3D.getZ() - z, 2));
};
