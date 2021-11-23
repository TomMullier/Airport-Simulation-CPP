#include "./CCR.hpp"
#include <cmath>

class Plane {
private:
  string name;
  Point3D pos;
  TWR destination;
  Trajectory traj;
  float speed;

public:
  Plane(Point3D pos, TWR &destination);
  string getName() const {return name;};
  Point3D getPos() const {return pos;};
  TWR getDestination() const {return destination;};
  Trajectory getTraj() const {return traj;};
  float getSpeed() const {return speed;};
  void setPos(Point3D &newPos);
  void setTraj(Trajectory &newTraj);
  void setSpeed(float & newSpeed);
  Point3D nextPos();
  void land();
  void takeOf();
  void parkIn();
  void parkOut();
  friend ostream &operator<<(ostream &os, const Plane &p);
};