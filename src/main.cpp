#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include "../headers/plane.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  CCR France;
  cout << France;

  Plane p(France);
  p.setParameters(France);
  cout << p << endl;
  
}