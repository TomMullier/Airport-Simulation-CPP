#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include "../headers/plane.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  CCR France;
  // cout << France;
  vector<TWR> t = France.getList();
  vector<TWR>::iterator it1 = t.begin();
  vector<TWR>::reverse_iterator it2 = t.rbegin();
  Plane p(*it1);
  p.setParameters(*it2);
  cout << p << endl;

  // Point3D a(0, 0, 0);
  // Point3D b(2, 5, 10);

  // Plane p(a,b);
  //  Trajectory T(a,b);
  //  cout << a.distanceTo(b) << endl;

  // cout << p.getPos();
  // cout << p.getTraj();
  // while (p.nextPos()<b) {
  // cout << p.getPos();
  //}
}