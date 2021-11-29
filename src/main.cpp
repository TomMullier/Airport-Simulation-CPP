#include <SFML/Graphics.hpp>
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

  // CCR
  // CCR France;
  // cout << France;

  // Plane
  // Plane p(France);
  // p.setParameters(France);
  // cout << p << endl;
  // p.navigate();

  // Threads
  // vector<thread> T;
  // for (int i = 0; i < NBPLANES; i++) {
  //   thread *th = new thread(threadPlane, ref(France));
  //   T.push_back(move(*th));
  // }
  // vector<thread>::iterator itT = T.begin();
  // while (itT!=T.end()) {
  //   (*itT++).join();
  // }

  // Display
  // cout << "-------------------" << endl << endl;

  RenderWindow window(VideoMode(200, 200), "SFML works!");
  CircleShape shape(100.f);
  shape.setFillColor(Color::Green);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
}