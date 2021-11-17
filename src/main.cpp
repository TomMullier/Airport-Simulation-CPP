#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include "../headers/plane.hpp"

// #define INTERVALLE 1

using namespace std;

int main(int argc, char *argv[]) {
  Point3D a(0, 0, 0);
  Point3D b(10, 10, 0);
  Trajectory T(a,b);
  cout << a.distanceTo(b) << endl;

  
}