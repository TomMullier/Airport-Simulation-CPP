#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>

#include "../headers/plane.hpp"

#define INTERVALLE 1
#define NBPLANES 1

using namespace std;
using namespace sf;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // DISPLAY
  RenderWindow window(VideoMode(500, 500), "Comme tu veux");

  // CCR
  CCR France;
  cout << France;

  // Plane
  vector<Plane> planes;
  for (int i = 0; i < NBPLANES; i++) {
    Plane *p = new Plane(France);
    p->setParameters(France);
    planes.push_back(*p);
    cout << *p << endl;
  }

  // Threads
  vector<thread> T;
  for (int i = 0; i < NBPLANES; i++) {
    thread *th = new thread(threadPlane, ref(planes[i]));
    T.push_back(move(*th));
  }

  // Display
  vector<Plane>::iterator itPlane = planes.begin();
  cout << "-------------------" << endl << endl;
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
    }
    window.clear();
    while (itPlane != planes.end()) {
      (*itPlane).getShape().setPosition(itPlane->getPos().getX(), itPlane->getPos().getY());
      window.draw((*itPlane++).getShape());
    }
    window.display();
  }

  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
}