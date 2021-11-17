#include "../headers/trajectory.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

Trajectory::Trajectory(const size_t &nb_points) {
  numberOfPoints = nb_points;
  for (size_t i = 0; i < numberOfPoints; i++)
    listOfPoints.push_back(Point3D());
}

Trajectory::Trajectory(vector<Point3D> &points, int &number) {
  listOfPoints = points;
  numberOfPoints = number;
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