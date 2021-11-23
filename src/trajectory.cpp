#include "../headers/trajectory.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Trajectory::Trajectory(Point3D pos) {
  listOfPoints.push_back(pos);
  numberOfPoints = listOfPoints.size();
}

void Trajectory::setList(Point3D &p) {
  listOfPoints.push_back(p);
  numberOfPoints++;
}

ostream &operator<<(ostream &os, const Trajectory &T) {
  vector<Point3D> table = T.listOfPoints;
  vector<Point3D>::iterator it = table.begin();
  while (it != table.end()) {
    os << *it++;
  }
  os << T.numberOfPoints << " points" << endl;
  return os;
}

Point3D &Trajectory::getPoint(const int &n) { return listOfPoints[n]; }

float Trajectory::getTotalDistance() {
  float distance = 0;
  for (size_t i = 0; i < numberOfPoints - 1; i++) {
    Point3D &previous = listOfPoints[i];
    Point3D &next = listOfPoints[i + 1];
    distance += previous.distanceTo(next);
  }
  return distance;
}
