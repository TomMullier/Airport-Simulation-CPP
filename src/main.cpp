#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>

#include "../headers/display.hpp"

#define INTERVALLE 1
#define NBPLANES 6

using namespace std;
using namespace sf;

void display(CCR &ccr, vector<Plane> &planes);
// void airportDisplay(RenderWindow &window, CCR &ccr, vector<Plane> &planes);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // CCR
  CCR France;
  // RenderWindow window(VideoMode(1362, 840), "Airport");
  // window.setPosition(Vector2i(0,0));
  // window.setVerticalSyncEnabled(true);
  // window.setFramerateLimit(60);
  // RenderWindow window_(VideoMode(1920-1362, 1920-1362), "Airport #2");
  // window_.setPosition(Vector2i(window.getSize().x,0));
  // window_.setVerticalSyncEnabled(true);
  // window_.setFramerateLimit(60);

  // Plane
  vector<Plane> planes;
  for (int i = 0; i < NBPLANES; i++) {
    Plane *p = new Plane(France);
    p->setParameters(France);
    planes.push_back(*p);
    // cout << *p << endl;
  }

  // Threads
  vector<thread> T;
  for (int i = 0; i < NBPLANES; i++) {
    thread *th = new thread(threadPlane, ref(planes[i]), ref(France));
    T.push_back(move(*th));
  }

  thread disp(display, ref(France), ref(planes));
  // thread a_disp(airportDisplay, ref(window_), ref(France), ref(planes));

  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
  disp.join();
  // a_disp.join();

  return EXIT_SUCCESS;
}
