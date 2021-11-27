#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "../headers/plane.hpp"

using namespace std;
using namespace sf;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  CCR France;
  cout << France;
  cout << "-------------------" << endl << endl;

  // RenderWindow window(VideoMode(200, 200), "SFML works!");
  // CircleShape shape(100.f);
  // shape.setFillColor(Color::Green);

  // while (window.isOpen()) {
  //   Event event;
  //   while (window.pollEvent(event)) {
  //     if (event.type == Event::Closed)
  //       window.close();
  //   }

  //   window.clear();
  //   window.draw(shape);
  //   window.display();
  // }

  Plane p(France);
  p.setParameters(France);
  cout << p << endl;
  // p.navigate();
}