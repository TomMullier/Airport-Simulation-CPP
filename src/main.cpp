#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>

#include "../headers/Display.hpp"

// Number of planes in project (do not put more than 50, it's lagging -_- )
#define NBPLANES 10

using namespace std;
using namespace sf;

/*
########################################################
#                                                      #
#                  AIRPORT SIMULATION                  #
#       PROJECT BY TOM MULLIER AND MAXIME DECLEMY      #
#                                                      #
# Copyrighted, do not modify or distribute             #
#                                                      #
# Contact : tom.mullier@student.junia.com              #
#           maxime.declemy@student.junia.com           #
#                                                      #
########################################################
*/

/*
To modify :
      Speed : Plane.cpp
      Number of planes : main.cpp
      Colors : CCR.cpp
*/

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // Regional Center - Nord Pas de Calais
  CCR NPdC;

  // Load Plane image to display
  Image image;
  Texture texturePlane;
  image.loadFromFile("../files/Plane.png");
  texturePlane.loadFromImage(image);
  texturePlane.setSmooth(false);

  // Creation of NBPLANES planes
  vector<Plane> planes;
  for (int i = 0; i < NBPLANES; i++) {
    Plane *p = new Plane(NPdC, texturePlane);
    p->setParameters(NPdC);
    planes.push_back(*p);
  }

  // Threads to navigate planes
  vector<thread> T;
  for (int i = 0; i < NBPLANES; i++) {
    thread *th = new thread(threadPlane, ref(planes[i]), ref(NPdC));
    T.push_back(move(*th));
  }

  // Thread sfor display
  thread disp(display, ref(NPdC), ref(planes));

  // Join threads
  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
  disp.join();

  return EXIT_SUCCESS;
}
