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

void display(CCR &ccr, vector<Plane> &planes);

int main(int argc, char *argv[]) {
  srand(time(NULL));
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

  thread disp(display, ref(France), ref(planes));
  // disp.join();

  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
}

void display(CCR &ccr, vector<Plane> &planes) { 
  RenderWindow window(VideoMode(200, 200), "De la merde");
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
    }

    vector<Plane>::iterator itPlane = planes.begin();
    window.clear();
    ccr.display(window);
    while (itPlane != planes.end()) {
      cout << itPlane->getPos() << endl;
      itPlane->getShape()->setPosition(itPlane->getPos().getX(),
                                      itPlane->getPos().getY());
      window.draw((*(*itPlane++).getShape()));
    }
    window.display();
    this_thread::sleep_for(1s);
  }
}