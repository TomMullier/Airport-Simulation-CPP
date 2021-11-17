#include "./point3D.hpp"
#include <cstddef>
#include <vector>

using namespace std;

class Trajectory {
private:
  vector<Point3D> listOfPoints;
  size_t numberOfPoints;

public:
  Trajectory(const size_t &nb_points);
  Trajectory(vector<Point3D> &points, int &number);
  vector<Point3D> getList() const { return this->listOfPoints; };
  friend ostream &operator<<(ostream &os, const Trajectory &T);
  Point3D &getPoint(const int &n);
  float getTotalDistance();
};