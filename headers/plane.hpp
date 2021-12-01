#include "./CCR.hpp"
#include <cmath>
#include <vector>

using namespace sf;

class Plane {
private:
  string name;
  Point3D pos;
  TWR twrDep;
  TWR twrDestination;
  Trajectory traj;
  float speed;
  CircleShape shape;

public:
  Plane(CCR &ccr);
  string getName() const { return name; };
  Point3D getPos() const { return pos; };
  TWR getDep() const { return twrDep; };
  TWR getDestination() const { return twrDestination; };
  Trajectory getTraj() const { return traj; };
  float getSpeed() const { return speed; };
  void setPos(Point3D &newPos);
  void setTraj(vector<Point3D> &newTraj);
  void setSpeed(float &newSpeed);
  Point3D nextPos(int &count);
  void setParameters(CCR &ccr);
  CircleShape *getShape() { return &shape; };
  void navigate(CCR &ccr);
  void rotate();
  void display(sf::RenderWindow &window);

    // void land();
    // void takeOf();
    // void parkIn();
    // void parkOut();
    friend ostream &operator<<(ostream &os, const Plane &p);
  };

  void threadPlane(Plane &p, CCR &ccr);