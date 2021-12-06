#include <complex>
#include <iostream>

using namespace std;

class Point3D {
private:
  float x, y, z;

public:
  // Constructors
  Point3D();
  Point3D(const float &newx, const float &newy, const float &newz);
  // Setters & Getters
  void setXYZ(const float &newx, const float &newy, const float &newz);
  void setX(const float &newx) { x = newx; };
  void setY(const float &newy) { y = newy; };
  void setZ(const float &newz) { z = newz; };
  float getX() const { return x; };
  float getY() const { return y; };
  float getZ() const { return z; };
  // Other functions
  float distanceTo(Point3D &otherPoint3D) const;
  // Operator
  friend ostream &operator<<(ostream &os, const Point3D &position);

  bool operator==(const Point3D &pos);
};