#include "./CCR.hpp"
#include <cmath>

class Plane {
private:
  Point3D pos;
  Trajectory traj;
  float speed;

public:
  Plane(Point3D &pos,Point3D &destination);
  Point3D getPos();
  Trajectory getTraj();
  float getSpeed();
  void setPos(Point3D &newPos);
  void setTraj(Trajectory &newTraj);
  void setSpeed(float & newSpeed);
  Point3D nextPos();

  // void Land();
};