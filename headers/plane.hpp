#include "./trajectory.hpp"

class Plane {
private:
  Point3D pos;
  Trajectory traj;
  float speed;

public:
  Plane(Point3D &destination);
  Point3D nextPos();
};