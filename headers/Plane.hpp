#include "./CCR.hpp"

#include <cmath>
#include <vector>

using namespace sf;

class Plane {
private:
  string name;
  Point3D pos;
  TWR *twrDep;
  TWR *twrDestination;
  Trajectory traj;
  float speed;
  Sprite shape;
  float rot;

public:
  // Constructor
  Plane(CCR &ccr, sf::Texture &texture);

  // Setters & Getters
  string getName() const { return name; };
  Point3D getPos() const { return pos; };
  TWR *getDep() const { return twrDep; };
  TWR *getDestination() const { return twrDestination; };
  Trajectory getTraj() const { return traj; };
  float getSpeed() const { return speed; };
  Sprite *getShape() { return &shape; };
  void setPos(Point3D &newPos) { pos = newPos; };
  void setParameters(CCR &ccr);
  void setTraj(vector<Point3D> &newTraj);
  void setSpeed(float &newSpeed) { speed = newSpeed; };

  // Other fonctions
  Point3D nextPos(int &count);
  void navigate(CCR &ccr);
  void rotate(int _i);
  void display(sf::RenderWindow &window);
  
  // Operator
  friend ostream &operator<<(ostream &os, const Plane &p);
};

void threadPlane(Plane &p, CCR &ccr);