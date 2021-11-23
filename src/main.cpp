#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include "../headers/plane.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  CCR France;
  //cout << France;
  vector<TWR> t=France.getList();
  vector<TWR>::iterator it = t.begin();
  Point3D Park = it->getParking();
  Plane p(Park,*it);

  cout << p << endl;

  //Point3D a(0, 0, 0);
  //Point3D b(2, 5, 10);

  
  //Plane p(a,b);
  // Trajectory T(a,b);
  // cout << a.distanceTo(b) << endl;

  // cout << p.getPos();
  // cout << p.getTraj();
  //while (p.nextPos()<b) {
    //cout << p.getPos();
  //}
}