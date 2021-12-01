#include "../headers/TWR.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

TWR::TWR(string _name, Point3D park, Point3D pi, Point3D dep, Point3D arr,
         int limit) {
  name = _name;
  parking = park;
  pist = pi;
  arrival = arr;
  departure = dep;
  this->limit = limit;
  occupied=false;
  numberOfPlanes=0;
}

bool TWR::operator==(const TWR &twr) {
  return this->getName() == twr.getName();
}

ostream &operator<<(ostream &os, const TWR &T) {
  os << "Name : " << T.getName() << endl
     << "Parking : " << T.getParking() << "Piste : " << T.getPist()
     << "Departure : " << T.getDeparture() << "Arrival : " << T.getArrival()
     << "Number Of plane : " << T.getNumberOfPlanes() << endl
     << "Limit : " << T.getLimit() << endl;
  return os;
}
