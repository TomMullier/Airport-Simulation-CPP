#include "../headers/display.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <thread>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

// void airportDisplay(RenderWindow &window, CCR &ccr, vector<Plane> &planes) {
//   while (window.isOpen()) {
//     Event event;
//     while (window.pollEvent(event)) {
//       if (event.type == Event::Closed) {
//         window.close();
//         return;
//       }
//     }

//     window.clear();

//     window.display();
//     this_thread::sleep_for(16.6ms);
//   }
// }


void display(CCR &ccr, vector<Plane> &planes) {
  RenderWindow window(VideoMode(1362, 840), "");
  int count = 0;
  window.setPosition(Vector2i(0, 0));
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
        return;
      }
      if (event.type == Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Right) {
          if (count < 11)
            count++;
          else
            count = 0;
        }
        if (event.key.code == sf::Keyboard::Left) {
          if (count > 0)
            count--;
          else
            count = 2;
        }
      }
    }

    window.clear();

    // Background
    Texture texture;
    changeTexture(texture, count, window);
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

Texture changeTexture(Texture &texture, int &count, RenderWindow &window){
    switch (count) {
    case 0: {
      texture.loadFromFile("../files/map.jpg");
      window.setTitle("CCR map");
      break;
    }
    case 1: {
      texture.loadFromFile("../files/Arras.png");
      window.setTitle("Arras (LFQD) airport");
      break;
    }
    case 2: {
      texture.loadFromFile("../files/Calais.png");
      window.setTitle("Calais (LFAC) airport");
      break;
    }
    case 3: {
      texture.loadFromFile("../files/Cambrai.png");
      window.setTitle("Cambrai (LFYG) airport");
      break;
    }
    case 4: {
      texture.loadFromFile("../files/Dunkerque.png");
      window.setTitle("Dunkerque (LFAK) airport");
      break;
    }
    case 5: {
      texture.loadFromFile("../files/Lille.png");
      window.setTitle("Lille (LFQQ) airport");
      break;
    }
    case 6: {
      texture.loadFromFile("../files/Maubeuge.png");
      window.setTitle("Maubeuge (LFQJ) airport");
      break;
    }
    case 7: {
      texture.loadFromFile("../files/Merville.png");
      window.setTitle("Merville (LFQT) airport");
      break;
    }
    case 8: {
      texture.loadFromFile("../files/StOmer.png");
      window.setTitle("Saint Omer (LFQN) airport");
      break;
    }
    case 9: {
      texture.loadFromFile("../files/Touquet.png");
      window.setTitle("Le Touquet (LFAT) airport");
      break;
    }
    case 10: {
      texture.loadFromFile("../files/Valenciennes.png");
      window.setTitle("Valanciennes (LFAV) airport");
      break;
    }
    case 11: {
      texture.loadFromFile("../files/Vitry.png");
      window.setTitle("Vitry en Artois (LFQS) airport");
      break;
    }
    default: {
      texture.loadFromFile("../files/map.jpg");
      window.setTitle("CCR map");
      count = 0;
      break;
    }
    }
    return texture;
}