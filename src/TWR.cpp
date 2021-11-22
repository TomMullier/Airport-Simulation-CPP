#include "../headers/TWR.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

TWR::TWR(string _name, Point3D park, Point3D pi, Point3D dep, Point3D arr) {
  name = _name;
  parking = park;
  pist = pi;
  arrival = arr;
  departure = dep;
}

ostream &operator<<(ostream &os, const TWR &T) {
  os << "Name : " << T.getName() << endl
     << "Parking : " << T.getParking() << "Piste : " << T.getPist()
     << "Departure : " << T.getDeparture() << "Arrival : " << T.getArrival()
     << endl;
  return os;
}
