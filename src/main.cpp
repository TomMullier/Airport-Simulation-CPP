#include <SFML/System.hpp>
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
    thread *th = new thread(threadPlane, ref(planes[i]));
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
}

void display(CCR &ccr, vector<Plane> &planes) {
  RenderWindow window(VideoMode(1362, 840), "De la merde");
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
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

    // Display TWRs
    ccr.display(window);

    // Display planes
    vector<Plane>::iterator itPlane = planes.begin();
    while (itPlane != planes.end()) {
      // cout << itPlane->getPos() << endl;
      itPlane->getShape()->setPosition(itPlane->getPos().getX(),
                                       itPlane->getPos().getY());
      window.draw((*(*itPlane).getShape()));
      Text text;
      Font font;
      text.setString(itPlane->getName());
      font.loadFromFile("../files/arial.ttf");
      text.setFont(font);
      text.setCharacterSize(12); // in pixels, not points!
      text.setFillColor(sf::Color::Blue);
      text.setStyle(Text::Bold);
      text.setPosition(itPlane->getPos().getX()+10,
                                       itPlane->getPos().getY()+10);
      window.draw(text);
      *itPlane++;
    }
    window.display();
    this_thread::sleep_for(1000ms);
  }
}