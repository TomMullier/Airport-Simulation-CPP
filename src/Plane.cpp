#include "../headers/Plane.hpp"
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <bits/types/time_t.h>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstddef>
#include <ctime>
#include <iterator>
#include <math.h>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

#define SPEED 10
#define BASESPEED 0.05

#define TEXT
#define EMERGENCY Red

chrono::milliseconds INTERVAL = (chrono::milliseconds)17;

std::mutex mtx;

/**
 * Constructor
 *
 * @return  Plane   Plane created and attributs set
 */
Plane::Plane(CCR &ccr, sf::Texture &texture) : shape(texture) {
  name = "F-";
  for (size_t i = 0; i < 4; i++)
    name += aleat(90, 65);
  this->twrDep = ccr.getDep();
  this->twrDep->setNumberOfPlanes(1);
  this->pos = twrDep->getParking();
  this->twrDestination = this->twrDep;
  traj = Trajectory(this->pos);
  speed = BASESPEED;
  this->shape.setOrigin(shape.getTexture()->getSize().x / 2.f,
                        shape.getTexture()->getSize().y / 2.f);
  this->shape.setScale(0.03, 0.03);
  this->shape.setPosition(pos.getX(), pos.getY());
  this->rot = 90;
  this->emergency = false;

#ifdef TEXT
  mtx.lock();
  cout << this->name << " generated at " << this->twrDep->getName() << "("
       << this->twrDep->getTag() << ")" << endl;
  mtx.unlock();
#endif
}

/**
 * Set TWR of destination
 *
 * @return  void
 */
void Plane::setParameters(CCR &ccr) {
  this->twrDestination = ccr.getArr(this->twrDep);
  vector<Point3D> tmp;
  tmp.push_back(twrDep->getPist());
  tmp.push_back(twrDep->getDeparture());
  tmp.push_back(twrDestination->getArrival());
  tmp.push_back(twrDestination->getPist());
  tmp.push_back(twrDestination->getParking());
  this->setTraj(tmp);
#ifdef TEXT
  mtx.lock();
  cout << this->name << " set destination to "
       << this->twrDestination->getName() << "("
       << this->twrDestination->getTag() << ")" << endl;
  mtx.unlock();
#endif
}

/**
 * Define the trajectory of plane, trajectory is composed of all important
 * points plane must pass
 *
 * @return  void
 */
void Plane::setTraj(vector<Point3D> &newTraj) {
  vector<Point3D>::iterator it = newTraj.begin();
  while (it != newTraj.end()) {
    this->traj.setList(*it++);
  }
}

/**
 * Calculate the next position of our trajectory (from actual position to next
 * point in trajectory)
 *
 * @param   int      count  Use as index to know next point of trajectory
 *
 * @return  Point3D         [Next position
 */
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
    rot = phi * 180 / M_PI;
  } else if (tmp.getX() > last.getX()) {
    tmp.setX(tmp.getX() - r * sin(teta) * cos(phi));
    if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
      tmp.setY(tmp.getY() - r * sin(teta) * sin(phi));
    }
    rot = (phi + M_PI) * 180 / M_PI;
  } else if (tmp.getY() < last.getY() || tmp.getY() > last.getY()) {
    tmp.setY(tmp.getY() + r * sin(teta) * sin(phi));
    rot = (phi)*180 / M_PI;
  }
  if (tmp.getZ() < last.getZ() || tmp.getZ() > last.getZ()) {
    tmp.setZ(tmp.getZ() + r * cos(teta));
  }
  return tmp;
}

/**
 * Move plane from a TWR to another TWR during all program
 *
 * @return  void
 */
void Plane::navigate(CCR &ccr) {
  // Init
  int count = 0;
  vector<Point3D> t = this->getTraj().getList();
  // Check take off possible
  while (this->twrDep->isOccupied() == true) {
    this_thread::sleep_for(1000ms);
  };
  this->twrDep->setOccupied(true);
#ifdef TEXT
  mtx.lock();
  cout << this->name << " take off from " << this->twrDep->getName() << "("
       << this->twrDep->getTag() << ")" << endl;
  mtx.unlock();
#endif

  // Take off
  while (count < int(t.size()) - 1) {
    // Check if full or runway free
    if (this->pos == this->twrDestination->getArrival()) {
      if (this->twrDestination->isOccupied() ||
          this->twrDestination->getLimit() ==
              this->twrDestination->getNumberOfPlanes()) {
// Attente
#ifdef TEXT
        mtx.lock();
        cout << this->name << " is waiting to land to "
             << this->twrDestination->getName() << "("
             << this->twrDestination->getTag() << ")" << endl;
        mtx.unlock();
#endif
        rotate(0);
      }
      this->pos = this->twrDestination->getArrival();
      // Landing
      this->twrDestination->setNumberOfPlanes(1);
      this->twrDestination->setOccupied(true);
#ifdef TEXT
      mtx.lock();
      cout << this->name << " land to " << this->twrDestination->getName()
           << "(" << this->twrDestination->getTag() << ")" << endl;
      mtx.unlock();
#endif
    }
    // On libère la place de parking
    if (this->pos == this->getDep()->getDeparture()) {
      this->twrDep->setNumberOfPlanes(-1);
      this->twrDep->setOccupied(false);
    }

    // Navigation
    this->speed = SPEED * pos.getZ() / 200 + BASESPEED;
    float dist1 = this->pos.distanceTo(t[count + 1]);
    Point3D nxt = this->nextPos(count);
    float dist2 = this->pos.distanceTo(nxt);

    // Between 2 points of traj
    while (dist1 > dist2) {
      if (count >= 2 && count <= 3 && !this->emergency) {
        this->emergency = randEmergency();
        cout << emergency << endl;
        if (emergency) {
          instructionEmergency(ccr);
        }
      }
      this->speed = SPEED * nxt.getZ() / 200 + BASESPEED;
      pos = nxt;
      dist1 = this->pos.distanceTo(t[count + 1]);
      nxt = this->nextPos(count);
      dist2 = this->pos.distanceTo(nxt);
      this_thread::sleep_for(INTERVAL);
    }
    // Change pos
    this->pos = t[count + 1];

    this_thread::sleep_for(INTERVAL);
    count++;
  }
// Is arrived and set plane with new datas
#ifdef TEXT
  mtx.lock();
  cout << this->name << " arrived to " << this->twrDestination->getName() << "("
       << this->twrDestination->getTag() << ")" << endl;
  mtx.unlock();
#endif
  this->twrDestination->setOccupied(false);
  this->speed = BASESPEED;
  this->twrDep = this->twrDestination;
  this->traj = Trajectory(this->pos);
  // Define new destination
  chrono::seconds tempt = (chrono::seconds)aleat(3, 10);
  this_thread::sleep_for(tempt);
  this->setParameters(ccr);
  this->navigate(ccr);
}

/**
 * Turn around airport
 *
 * @return  void
 */
void Plane::rotate(int _i) {
  Point3D centerPoint = this->twrDestination->getPist();
  float numberOfIt = 200;
  float angleInRadians = (360 / numberOfIt) * (M_PI / 180);
  float cosTheta = cos(angleInRadians);
  float sinTheta = sin(angleInRadians);
  rot = (angleInRadians * _i + M_PI / 2) * 180 / M_PI;
  Point3D pointToRotate = this->pos;
  float X = (cosTheta * (pointToRotate.getX() - centerPoint.getX()) -
             sinTheta * (pointToRotate.getY() - centerPoint.getY()) +
             centerPoint.getX());
  float Y = (sinTheta * (pointToRotate.getX() - centerPoint.getX()) +
             cosTheta * (pointToRotate.getY() - centerPoint.getY()) +
             centerPoint.getY());
  this->pos.setX(X);
  this->pos.setY(Y);
  _i++;
  if (_i != numberOfIt) {
    this_thread::sleep_for(INTERVAL);
    rotate(_i);
  } else if (this->twrDestination->isOccupied() ||
             this->twrDestination->getLimit() ==
                 this->twrDestination->getNumberOfPlanes()) {
    // Attente
#ifdef TEXT
    mtx.lock();
    cout << this->name << " is waiting to land to "
         << this->twrDestination->getName() << "("
         << this->twrDestination->getTag() << ")" << endl;
    mtx.unlock();
#endif
    rotate(0);
  }
}

/**
 * Display planes on SFML window
 *
 * @return  void
 */
void Plane::display(sf::RenderWindow &window) {
  this->getShape()->setPosition(this->getPos().getX() + 4,
                                this->getPos().getY() + 4);
  this->getShape()->setRotation(rot);
  window.draw((*(*this).getShape()));
  Text text;
  Font font;
  string str = this->getName() + "\nAlt. : " + to_string(this->getPos().getZ());
  text.setString(str);
  font.loadFromFile("../files/arial.ttf");
  text.setFont(font);
  text.setCharacterSize(12);
  Color clr(190, 190, 190); // in pixels, not points!
  text.setFillColor(clr);
  if (this->emergency == true)
    text.setFillColor(Color::EMERGENCY);
  text.setStyle(Text::Bold);
  text.setPosition(this->getPos().getX() + 10, this->getPos().getY() + 10);
  window.draw(text);
}

/**
 * Operator << overloaded
 *
 * @return  ostream information to print
 */
ostream &operator<<(ostream &os, const Plane &p) {
  os << "Name : " << p.getName() << endl << endl;
  os << "Position : " << p.getPos() << endl;
  os << "TWR Departure : " << endl << p.getDep() << endl;
  os << "Destination : " << endl << p.getDestination() << endl;
  os << "Trajectory : " << endl << p.getTraj() << endl;
  os << "Speed : " << p.getSpeed() << endl;
  return os;
}

bool randEmergency() {
  int x = aleat(0, 100);
  if (x == 0)
    return true;
  else
    return false;
}

void Plane::instructionEmergency(CCR &ccr) {
  vector<TWR *> vect = ccr.getList();
  vector<TWR *>::iterator it = vect.begin();
  TWR *tmpTWR = *it;
  Point3D tmpPoint = (*it++)->getArrival();
  float dist = this->pos.distanceTo(tmpPoint);

  while (it != vect.end()) {
    cout << "ok";
    tmpPoint = (*it)->getArrival();
    if (dist < this->pos.distanceTo(tmpPoint)) {
      dist = this->pos.distanceTo(tmpPoint);
    }
    tmpTWR = *it++;
  }

  this->traj.popList(3);
  this->traj.setList(tmpTWR->getArrival());
  this->traj.setList(tmpTWR->getPist());
  this->traj.setList(tmpTWR->getParking());
}

void threadPlane(Plane &p, CCR &ccr) { p.navigate(ccr); }
