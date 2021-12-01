#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <thread>
#include <vector>

#include "../headers/plane.hpp"

#define INTERVALLE 1
#define NBPLANES 6

using namespace std;
using namespace sf;

void display(CCR &ccr, vector<Plane> &planes);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // CCR
  CCR France;

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

  vector<thread>::iterator itT = T.begin();
  while (itT != T.end()) {
    if (itT->joinable()) {
      (*itT++).join();
    }
  }
  disp.join();
  return EXIT_SUCCESS;
}

void display(CCR &ccr, vector<Plane> &planes) {
  RenderWindow window(VideoMode(1362, 840), "Airport");
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
        return;
      }
    }

    window.clear();

    // Background
    Texture texture;
    texture.loadFromFile("../files/map.jpg");
    Sprite sprite(texture);
    Vector2u TextureSize = texture.getSize(); // Get size of texture.
    Vector2u WindowSize = window.getSize();   // Get size of window.
    float ScaleX = (float)WindowSize.x / TextureSize.x;
    float ScaleY = (float)WindowSize.y / TextureSize.y; // Calculate scale.
    sprite.setScale(ScaleX, ScaleY);
    window.draw(sprite);

    // Circles
    int colorThick = 50;
    Color color(colorThick, colorThick, colorThick);
    for (int i = 1; i < 10; i++) {
      CircleShape c;
      c.setRadius(100 * i);
      c.setOutlineColor(color);
      c.setFillColor(Color::Transparent);
      c.setOutlineThickness(1);
      c.setPosition((float)window.getSize().x / 2 - c.getRadius(),
                    (float)window.getSize().y / 2 - c.getRadius());
      window.draw(c);
    }
    // Display TWRs
    ccr.display(window);

    // Display planes
    vector<Plane>::iterator itPlane = planes.begin();
    while (itPlane != planes.end()) {
      (*itPlane++).display(window);
    }
    window.display();
    this_thread::sleep_for(16.6ms);
  }
}