#include "../headers/trajectory.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

void Trajectory::print() {
  for (size_t i = 0; i < numberOfPoints; i++) {
    points[i].print();
  }
}
Point3D &Trajectory::getPoint(const int &n) { return points[n]; }
float Trajectory::getTotalDistance() {
  float distance = 0;
  for (size_t i = 0; i < numberOfPoints - 1; i++) {
    Point3D &previous = points[i];
    Point3D &next = points[i + 1];
    distance += previous.distanceTo(next);
  }
  return distance;
}

Trajectory::Trajectory(const size_t nb_points) {
  numberOfPoints = nb_points;
  points = new Point3D[numberOfPoints];
  for (size_t i = 0; i < numberOfPoints; i++) {
    points[i] = Point3D();
  }
}

Trajectory::Trajectory(Point3D *points, int &number) {
  this->points = points;
  numberOfPoints = number;
}

Trajectory::~Trajectory() { delete points; }
