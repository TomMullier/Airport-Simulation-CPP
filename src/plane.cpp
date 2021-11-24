#include "../headers/plane.hpp"
#include <cmath>
#include <iterator>
#include <math.h>
#include <vector>

using namespace std;

Plane::Plane(CCR &ccr) {
  name = "F-";
  for (size_t i = 0; i < 4; i++)
    name += aleat(90, 65);
  this->twrDep = ccr.getDep();
  this->pos = twrDep.getParking();
  this->twrDestination = this->twrDep;
  traj = Trajectory(this->pos);
  speed = 1;
}

void Plane::setPos(Point3D &newPos) { pos = newPos; }

void Plane::setTraj(vector<Point3D> &newTraj) {
  vector<Point3D>::iterator it = newTraj.begin();
  while (it != newTraj.end()) {
    this->traj.setList(*it++);
  }
}

void Plane::setSpeed(float &newSpeed) { speed = newSpeed; }

Point3D Plane::nextPos(int &count) {
  float r = speed;
  Point3D tmp(this->getPos().getX(), this->getPos().getY(),
              this->getPos().getZ());
  vector<Point3D> list = traj.getList();
  Point3D first = list[count];
  Point3D last = list[count + 1];
  Point3D C(last.getX(), last.getY(), first.getZ());
  float phi = atan((C.getY() - first.getY()) / (C.getX() - first.getX()));
  float teta = acos((last.getZ() - first.getZ()) / first.distanceTo(last));
  if (tmp.getX() < last.getX()) {
    tmp.setX(tmp.getX() + r * sin(teta) * cos(phi));
  } else if (tmp.getX() > last.getX()) {
    tmp.setX(tmp.getX() - r * sin(teta) * cos(phi));
  }
  if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
    tmp.setY(tmp.getY() + r * sin(teta) * sin(phi));
  }
  if (tmp.getZ() < last.getZ() || tmp.getZ() > last.getZ()) {
    tmp.setZ(tmp.getZ() + r * cos(teta));
  }
  // pos = Point3D(pos.getX() + r * sin(teta) * cos(phi),
  //               pos.getY() + r * sin(teta) * sin(phi),
  //               pos.getZ() + r * cos(teta));

  return tmp;
}

void Plane::setParameters(CCR &ccr) {
  this->twrDestination = ccr.getArr(this->twrDep);
  vector<Point3D> tmp;
  tmp.push_back(twrDep.getPist());
  tmp.push_back(twrDep.getDeparture());
  tmp.push_back(twrDestination.getArrival());
  tmp.push_back(twrDestination.getPist());
  tmp.push_back(twrDestination.getParking());
  this->setTraj(tmp);
}

// void land() {}

// void takeOf();
// void parkIn();
// void parkOut();

void Plane::navigate() {
  int count = 0;
  vector<Point3D> t = this->getTraj().getList();
  while (count < 5) {
    float dist1 = this->pos.distanceTo(t[count + 1]);
    Point3D nxt = this->nextPos(count);
    float dist2 = this->pos.distanceTo(nxt);
    cout << "Distance 1 : " << dist1 << endl
         << "Distance 2 : " << dist2 << endl
         << "NXT : " << nxt << endl;
    ;
    while (dist1 > dist2) {
      pos = nxt;
      cout << "Position : " << pos << endl;
      dist1 = this->pos.distanceTo(t[count + 1]);
      nxt = this->nextPos(count);
      dist2 = this->pos.distanceTo(nxt);
      cout << "Distance 1 : " << dist1 << endl
           << "Distance 2 : " << dist2 << endl
           << "NXT : " << nxt << endl;
    }
    this->pos = t[count + 1];
    cout << pos << endl << endl;
    count++;
  }
}

ostream &operator<<(ostream &os, const Plane &p) {
  os << "Name : " << p.getName() << endl << endl;
  os << "Position : " << p.getPos() << endl;
  os << "TWR Departure : " << endl << p.getDep() << endl;
  os << "Destination : " << endl << p.getDestination() << endl;
  os << "Trajectory : " << endl << p.getTraj() << endl;
  os << "Speed : " << p.getSpeed() << endl;
  return os;
}