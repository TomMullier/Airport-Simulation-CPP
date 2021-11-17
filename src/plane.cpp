#include "../headers/plane.hpp"
#include <iterator>
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
  vector<Point3D> list=traj.getList();
  vector<Point3D>::iterator first = list.begin();
  //vector<Point3D>::iterator const last = list.end();
  Point3D tmp = list[list.size()-1];
  Point3D C(tmp.getX(), first->getY(), 0);
  float teta = acos(first->distanceTo(C) / first->distanceTo(tmp));//tan(tmp.distanceTo(C)/first->distanceTo(C));
  pos = Point3D(pos.getX() + speed * cos(teta), pos.getY() + speed * sin(teta), pos.getZ());
  //return Point3D(pos.getX() + speed * cos(teta), pos.getY() + speed * sin(teta), pos.getZ());
}
