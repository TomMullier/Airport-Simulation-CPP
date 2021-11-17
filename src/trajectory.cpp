#include "../headers/trajectory.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

Trajectory::Trajectory(Point3D pos, Point3D destination) {
  listOfPoints.push_back(pos);
  listOfPoints.push_back(destination);
  numberOfPoints = listOfPoints.size();
}

ostream &operator<<(ostream &os, const Trajectory &T) {
  vector<Point3D> table = T.listOfPoints;
  vector<Point3D>::iterator it = table.begin();
  while (it != table.end()) {
    os << *it;
  }
  os << T.numberOfPoints;
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
