#include "../headers/plane.hpp"
#include <cmath>
#include <iterator>
#include <math.h>
#include <vector>

using namespace std;

Plane::Plane(Point3D &destination) {
  pos = Point3D(0, 0, 0);
  traj = Trajectory(pos, destination);
  speed = 1;
}

Point3D Plane::getPos(){
  return pos;
}

Trajectory Plane::getTraj(){
  return traj;
}

float Plane::getSpeed(){
  return speed;
}

void Plane::setPos(Point3D &newPos){
  pos = newPos;
}

void Plane::setTraj(Trajectory &newTraj){
  traj = newTraj;
}

void Plane::setSpeed(float &newSpeed){
  speed = newSpeed;
}

void Plane::nextPos() {
  float r = speed;
  vector<Point3D> list=traj.getList();
  vector<Point3D>::iterator const first = list.begin();
  vector<Point3D>::reverse_iterator const last = list.rbegin();
  Point3D C(last->getX(), last->getY(), first->getZ());
  float phi = atan((C.getY()-first->getY())/(C.getX()-first->getX()));
  float teta = acos((last->getZ()-first->getZ())/first->distanceTo(*last));
  pos = Point3D(pos.getX() + r * sin(teta) * cos(phi), pos.getY() + r * sin(teta) * sin(phi), pos.getZ() + r * cos(teta));
  //return Point3D(pos.getX() + speed * cos(teta), pos.getY() + speed * sin(teta), pos.getZ());
}
