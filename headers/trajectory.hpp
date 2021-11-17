#include "./point3D.hpp"
#include <cstddef>
#include <vector>

using namespace std;

class Trajectory {
private:
  vector<Point3D> listOfPoints;
  size_t numberOfPoints;

public:
  Trajectory(Point3D pos=Point3D(), Point3D destination=Point3D());
  vector<Point3D> getList() const { return listOfPoints; };
  friend ostream &operator<<(ostream &os, const Trajectory &T);
  Point3D &getPoint(const int &n);
  float getTotalDistance();
};