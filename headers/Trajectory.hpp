#include "./Point3D.hpp"
#include <cstddef>
#include <vector>

using namespace std;

class Trajectory {
private:
  vector<Point3D> listOfPoints;
  size_t numberOfPoints;

public:
  // Constructor
  Trajectory(Point3D pos = Point3D());
  // Setters & Getters
  vector<Point3D> getList() const { return listOfPoints; };
  Point3D &getPoint(const int &n) { return listOfPoints[n]; };
  int getNumberPoints() const { return numberOfPoints; };
  void setNumberOfPoints() { numberOfPoints = listOfPoints.size(); };
  void setList(Point3D const &p);
  void popList(int nbPoints);
  // Operator
  friend ostream &operator<<(ostream &os, const Trajectory &T);
};