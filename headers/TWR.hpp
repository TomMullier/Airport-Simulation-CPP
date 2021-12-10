#include "./Trajectory.hpp"
#include <string>

class TWR {
private:
  string name;
  string tag;
  Point3D parking;
  Point3D pist;
  Point3D departure;
  Point3D arrival;
  int limit;
  int numberOfPlanes;
  bool occupied;

public:
  // Constructor
  TWR(string _name = "", string _tag = "", Point3D park = Point3D(),
      Point3D pi = Point3D(), Point3D dep = Point3D(), Point3D arr = Point3D(),
      int limit = 0);
  // Setters & Getters
  string getName() const { return name; };
  string getTag() const { return tag; };
  Point3D getParking() const { return parking; };
  Point3D getPist() const { return pist; };
  Point3D getDeparture() const { return departure; };
  Point3D getArrival() const { return arrival; };
  bool isOccupied() const { return occupied; }
  int getLimit() const { return limit; };
  int getNumberOfPlanes() const { return numberOfPlanes; };
  void setNumberOfPlanes(int x) { numberOfPlanes += x; };
  void setOccupied(bool newState) { occupied = newState; };
  // Operator
  bool operator==(const TWR &twr);
  friend ostream &operator<<(ostream &os, const TWR &T);
};