#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>

#include "../headers/Display.hpp"

#define INTERVALLE 1
#define NBPLANES 1

using namespace std;
using namespace sf;

void display(CCR &ccr, vector<Plane> &planes);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // CCR
  CCR France;

   // Image Plane
  Image image;
  Texture texturePlane;
  image.loadFromFile("../files/Plane.png");
  texturePlane.loadFromImage(image);
  texturePlane.setSmooth(false);
 

  // Plane
  vector<Plane> planes;
  for (int i = 0; i < NBPLANES; i++) {
    Plane *p = new Plane(France, texturePlane);
    p->setParameters(France);
    planes.push_back(*p);
  }

  // Threads
  vector<thread> T;
  for (int i = 0; i < NBPLANES; i++) {
    thread *th = new thread(threadPlane, ref(planes[i]), ref(France));
    T.push_back(move(*th));
  }

  thread disp(display, ref(France), ref(planes));

  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
  disp.join();

  return EXIT_SUCCESS;
}
