#include "../headers/TWR.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

/**
 * Constructor of TWR without argument
 *
 * @return  TWR     TWR created and attributs set
 */
TWR::TWR(string _name, string _tag, Point3D park, Point3D pi, Point3D dep, Point3D arr,
         int limit) {
  name = _name;
  tag = _tag;
  parking = park;
  pist = pi;
  arrival = arr;
  departure = dep;
  this->limit = limit;
  occupied = false;
  numberOfPlanes = 0;
  emergency =false;
}

/**
 * Operator ==
 *
 * @return  bool    true if both TWR are the same
 */
bool TWR::operator==(const TWR &twr) {
  return this->getName() == twr.getName();
}

/**
 * Operator << overloaded
 *
 * @return  ostream information to print
 */
ostream &operator<<(ostream &os, const TWR &T) {
  os << "Name : " << T.getName() << endl
     << "Parking : " << T.getParking() << "Piste : " << T.getPist()
     << "Departure : " << T.getDeparture() << "Arrival : " << T.getArrival()
     << "Number Of plane : " << T.getNumberOfPlanes() << endl
     << "Limit : " << T.getLimit() << endl;
  return os;
}
