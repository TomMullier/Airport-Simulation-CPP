#include "../headers/Trajectory.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * Constructor of Trajectory without argument
 *
 * @return  Trajectory created and attributs set
 */
Trajectory::Trajectory(Point3D pos) {
  listOfPoints.push_back(pos);
  numberOfPoints = listOfPoints.size();
}

/**
 * Complete the trajectory with points to pass
 *
 * @return  void
 */
void Trajectory::setList(Point3D const &p) {
  listOfPoints.push_back(p);
  numberOfPoints++;
}

/**
 * Delete last point of list
 *
 * @param   int   nbPoints  Number of points to delete
 *
 * @return  void            
 */
void Trajectory::popList(int nbPoints) {
  for (int i; i < nbPoints; i++) {
    listOfPoints.pop_back();
    numberOfPoints--;
  }
}

/**
 * Operator << overloaded
 *
 * @return  ostream information to print
 */
ostream &operator<<(ostream &os, const Trajectory &T) {
  vector<Point3D> table = T.listOfPoints;
  vector<Point3D>::iterator it = table.begin();
  while (it != table.end()) {
    os << *it++;
  }
  os << T.numberOfPoints << " points" << endl;
  return os;
}
