#include "../headers/plane.hpp"

Plane::Plane(Point3D &destination) {
  pos = Point3D(0, 0, 0);
  traj = Trajectory(pos, destination);
  speed = 1;
}


Point3D Plane::nextPos() {
  Point3D first = traj[0];
  Point3D last = this->listOfPoints[numberOfPoints];
  Point3D C(last.getX(), first.getY(), 0);
  float teta = acos(first.distanceTo(C) / first.distanceTo(last));
  return Point3D(p.getX() + speed * cos(teta),
                 p.getY() + speed * sin(teta), p.getZ());
}
