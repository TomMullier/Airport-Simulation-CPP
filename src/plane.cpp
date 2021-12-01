#include "../headers/plane.hpp"
#include <bits/types/time_t.h>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <math.h>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

#define SPEED 10
#define BASESPEED 0.05

Plane::Plane(CCR &ccr) {
  name = "F-";
  for (size_t i = 0; i < 4; i++)
    name += aleat(90, 65);
  this->twrDep = ccr.getDep();
  this->twrDep->setNumberOfPlanes(1);
  cout << this->twrDep << endl;
  this->pos = twrDep->getParking();
  this->twrDestination = this->twrDep;
  traj = Trajectory(this->pos);
  speed = BASESPEED;
  // DISPLAY
  CircleShape _shape(5.f);
  _shape.setFillColor(Color::Green);
  _shape.setPosition(pos.getX(), pos.getY());
  this->shape = _shape;
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
    if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
      tmp.setY(tmp.getY() + r * sin(teta) * sin(phi));
    }
  } else if (tmp.getX() > last.getX()) {
    tmp.setX(tmp.getX() - r * sin(teta) * cos(phi));
    if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
      tmp.setY(tmp.getY() - r * sin(teta) * sin(phi));
    }
  } else if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
    tmp.setY(tmp.getY() + r * sin(teta) * sin(phi));
  }
  if (tmp.getZ() < last.getZ() || tmp.getZ() > last.getZ()) {
    tmp.setZ(tmp.getZ() + r * cos(teta));
  }
  return tmp;
}

void Plane::setParameters(CCR &ccr) {
  this->twrDestination = ccr.getArr(this->twrDep);
  vector<Point3D> tmp;
  tmp.push_back(twrDep->getPist());
  tmp.push_back(twrDep->getDeparture());
  tmp.push_back(twrDestination->getArrival());
  tmp.push_back(twrDestination->getPist());
  tmp.push_back(twrDestination->getParking());
  this->setTraj(tmp);
}

void Plane::navigate(CCR &ccr) {
  // Init
  int count = 0;
  vector<Point3D> t = this->getTraj().getList();
  // Vérification si décollage possible
  while (this->twrDep->isOccupied() == true) {
    this_thread::sleep_for(1000ms);
  };
  this->twrDep->setOccupied(true);
  // cout << this->twrDep.isOccupied() << endl;
  // cout << this->twrDestination.isOccupied() << endl<<endl;

  // Décollage + navigation
  while (count < int(t.size()) - 1) {
    // On libère la place de parking
    if (this->pos == this->getDep().getDeparture()) {
      this->twrDep->setNumberOfPlanes(-1);
      this->twrDep->setOccupied(false);
    }

    // Navigation
    this->speed = SPEED * pos.getZ() / 200 + BASESPEED;
    float dist1 = this->pos.distanceTo(t[count + 1]);
    Point3D nxt = this->nextPos(count);
    float dist2 = this->pos.distanceTo(nxt);

    // Entre deux points de Traj
    while (dist1 > dist2) {
      this->speed = SPEED * nxt.getZ() / 200 + BASESPEED;
      pos = nxt;
      dist1 = this->pos.distanceTo(t[count + 1]);
      nxt = this->nextPos(count);
      dist2 = this->pos.distanceTo(nxt);
      this_thread::sleep_for(16.6ms);
      // cout << this->twrDep.isOccupied() << endl;
      // cout << this->twrDestination.isOccupied() << endl<<endl;
    }
    // Téléportation si dépassé
    this->pos = t[count + 1];

    // Check if full
    // Si à l'arrivée on check les places et si piste libre
    if (this->pos == this->twrDestination->getArrival()) {
      // cout<<this->getDestination()<<endl;
      // cout << this->twrDep.isOccupied() << endl;
      // cout << this->twrDestination.isOccupied() << endl<<endl;
      while (this->twrDestination->isOccupied()) {
        // Attente
        rotate();
      }
      // On atteri
      this->twrDestination->setNumberOfPlanes(1);
      this->twrDestination->setOccupied(true);
    }
    this_thread::sleep_for(16.6ms);
    count++;
  }
  this->twrDestination->setOccupied(false);
  this->speed = BASESPEED;
  this->twrDep = this->twrDestination;
  this->traj = Trajectory(this->pos);
  this->setParameters(ccr);
  chrono::milliseconds tempt = (chrono::milliseconds)aleat(0, 2000);
  this_thread::sleep_for(tempt);
  this->navigate(ccr);
}

void Plane::rotate() {
  // Condition :
  // Nombre d'avion dans l'aeroport = limit
  // Avion en train de décoler ou atterrir (state tour décollage ou atterissage)
  // Avion peut décoller si tour libre sinon reste sur parking
  cout << "FULL" << endl;
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

void threadPlane(Plane &p, CCR &ccr) { p.navigate(ccr); }

void Plane::display(sf::RenderWindow &window) {
  this->getShape()->setPosition(this->getPos().getX(), this->getPos().getY());
  window.draw((*(*this).getShape()));
  Text text;
  Font font;
  text.setString(this->getName());
  font.loadFromFile("../files/arial.ttf");
  text.setFont(font);
  text.setCharacterSize(12); // in pixels, not points!
  text.setFillColor(sf::Color::Blue);
  text.setStyle(Text::Bold);
  text.setPosition(this->getPos().getX() + 10, this->getPos().getY() + 10);
  window.draw(text);
}