#include "../headers/plane.hpp"
#include <cmath>
#include <iterator>
#include <math.h>
#include <vector>

using namespace std;

int aleat (int val1, int val2){
    if (val1>val2) swap(val1, val2);
    return ( rand() % ( ( val2 - val1 ) + 1) ) + val1;
}

Plane::Plane(Point3D pos,TWR &destination) {
  name = "F-";
  for (size_t i=0; i<4; i++) name += aleat(90, 65);
  this->pos = pos;
  this->destination = destination;
  traj = Trajectory(pos, destination.getArrival());
  speed = 1;
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

Point3D Plane::nextPos() {
  float r = speed;
  vector<Point3D> list=traj.getList();
  vector<Point3D>::iterator const first = list.begin();
  vector<Point3D>::reverse_iterator const last = list.rbegin();
  Point3D C(last->getX(), last->getY(), first->getZ());
  float phi = atan((C.getY()-first->getY())/(C.getX()-first->getX()));
  float teta = acos((last->getZ()-first->getZ())/first->distanceTo(*last));
  
  if (abs(first->getX())<abs(last->getX())) {
    pos = Point3D(pos.getX() + r * sin(teta) * cos(phi), this->getPos().getY(), this->getPos().getZ());
  }
  if (abs(first->getY())<abs(last->getY())) {
    pos = Point3D(this->getPos().getX(), pos.getY() + r * sin(teta) * sin(phi), this->getPos().getZ());
  }
  if (abs(first->getZ())<abs(last->getZ())) {
    pos = Point3D(this->getPos().getX(), this->getPos().getY(), pos.getZ() + r * cos(teta));
  }
  //pos = Point3D(pos.getX() + r * sin(teta) * cos(phi), pos.getY() + r * sin(teta) * sin(phi), pos.getZ() + r * cos(teta));
  return getPos();
}

void land(){

}

void takeOf();
void parkIn();
void parkOut();

ostream &operator<<(ostream &os, const Plane &p){
  os << "Name : " << p.getName() << endl << endl;
  os << "Position : " << p.getPos() << endl;
  os << "Destination : " << endl << p.getDestination() << endl;
  os << "Trajectory : " << endl << p.getTraj() << endl;
  os << "Speed : "  << p.getSpeed() << endl;
  return os;
}