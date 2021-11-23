#include "./point3D.hpp"
#include <cstddef>
#include <vector>

using namespace std;

class Trajectory {
private:
  vector<Point3D> listOfPoints;
  size_t numberOfPoints;

public:
  Trajectory(Point3D pos=Point3D());
  void setNumberOfPoints(){numberOfPoints = listOfPoints.size();};
  void setList(Point3D &p);
  vector<Point3D> getList() const { return listOfPoints; };
  Point3D &getPoint(const int &n);
  int getNumberPoints() const {return numberOfPoints;};
  float getTotalDistance();
  friend ostream &operator<<(ostream &os, const Trajectory &T);
};