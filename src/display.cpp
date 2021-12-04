#include "../headers/display.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <thread>

using namespace std;
using namespace sf;

void display(CCR &ccr, vector<Plane> &planes) {
  RenderWindow windowMap(VideoMode(1362, 840), "CCR map");
  windowMap.setPosition(Vector2i(0, 0));
  windowMap.setVerticalSyncEnabled(true);
  windowMap.setFramerateLimit(60);

  RenderWindow windowAirport(VideoMode(700, 500), "");
  windowAirport.setPosition(Vector2i(0, 0));
  windowAirport.setVerticalSyncEnabled(true);
  windowAirport.setFramerateLimit(60);
  int count = 0;

  while (windowMap.isOpen() && windowAirport.isOpen()) {
    Event event;
    while (windowMap.pollEvent(event) || windowAirport.pollEvent(event)) {
      if (event.type == Event::Closed) {
        windowMap.close();
        windowAirport.close();
        return;
      }
      if (event.type == Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Right) {
          if (count < 11)
            count++;
          else
            count = 1;
        }
        if (event.key.code == sf::Keyboard::Left) {
          if (count > 1)
            count--;
          else
            count = 11;
        }
      }
    }

    windowMap.clear();
    windowAirport.clear();

    // Background Map
    Texture textureMap;
    textureMap.loadFromFile("../files/map.jpg");
    Sprite mapSprite(textureMap);
    Vector2u TextureMapSize = textureMap.getSize(); // Get size of texture.
    Vector2u windowMapSize = windowMap.getSize();   // Get size of windowMap.
    float mapScaleX = (float)windowMapSize.x / TextureMapSize.x;
    float mapScaleY =
        (float)windowMapSize.y / TextureMapSize.y; // Calculate scale.
    mapSprite.setScale(mapScaleX, mapScaleY);
    windowMap.draw(mapSprite);

    // Background Airport
    Texture textureAirport;
    changeTexture(textureAirport, count, windowAirport);
    Sprite airportSprite(textureAirport);
    Vector2u TextureAirportSize =
        textureAirport.getSize();                     // Get size of texture.
    Vector2u windowAirportSize = windowAirport.getSize(); // Get size of windowAirport.
    float airportScaleX = (float)windowAirportSize.x / TextureAirportSize.x;
    float airportScaleY =
        (float)windowAirportSize.y / TextureAirportSize.y; // Calculate scale.
    airportSprite.setScale(airportScaleX, airportScaleY);
    windowAirport.draw(airportSprite);

    // Circles
    int colorThick = 50;
    Color color(colorThick, colorThick, colorThick);
    for (int i = 1; i < 10; i++) {
      CircleShape c;
      c.setRadius(100 * i);
      c.setOutlineColor(color);
      c.setFillColor(Color::Transparent);
      c.setOutlineThickness(1);
      c.setPosition((float)windowMap.getSize().x / 2 - c.getRadius(),
                    (float)windowMap.getSize().y / 2 - c.getRadius());
      windowMap.draw(c);
    }
    // Display TWRs
    ccr.display(windowMap);

    // Display planes
    vector<Plane>::iterator itPlane = planes.begin();
    while (itPlane != planes.end()) {
      (*itPlane++).display(windowMap);
    }
    windowMap.display();
    this_thread::sleep_for(16.6ms);
  }
}

Texture changeTexture(Texture &texture, int &count, RenderWindow &window) {
  switch (count) {
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
    texture.loadFromFile("../files/Arras.png");
    window.setTitle("Arras (LFQD) airport");
    count = 1;
    break;
  }
  }
  return texture;
}