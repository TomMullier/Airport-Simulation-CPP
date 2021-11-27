#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "../headers/plane.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  CCR France;
  cout << France;
  cout << "-------------------" << endl << endl;

  Plane p(France);
  p.setParameters(France);
  cout << p << endl;
}