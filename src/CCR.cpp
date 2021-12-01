#include "../headers/CCR.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

#include "../headers/json.hpp"
using nlohmann::json;
using namespace sf;

CCR::CCR() {
  std::ifstream file("../files/ListTWR.json");
  json j;
  file >> j;

  if (file.is_open()) {
    for (auto it = j.begin(); it != j.end(); ++it) {
      json temp;
      temp = *it;
      TWR *t = new TWR (temp["name"],
            Point3D(temp["parking"]["x"], temp["parking"]["y"], 0),
            Point3D(temp["pist"]["x"], temp["pist"]["y"], 0),
            Point3D(temp["departure"]["x"], temp["departure"]["y"],
                    temp["departure"]["z"]),
            Point3D(temp["arrival"]["x"], temp["arrival"]["y"],
                    temp["arrival"]["z"]),
            temp["limit"]);
      ListOfTWR.push_back(*t);
    }
    file.close();
  } else {
    cout << "File 'ListTWR.txt' doesn't exist..." << endl;
    cout << "Please create a file named 'ListTWR.txt' with this pattern"
         << endl;
  }
}

int aleat(int val1, int val2) {
  if (val1 > val2)
    swap(val1, val2);
  return (rand() % ((val2 - val1) + 1)) + val1;
}

TWR CCR::getDep() const {
  int idx = aleat(0, (ListOfTWR.size() - 1));
  return ListOfTWR[idx];
}

TWR CCR::getArr(const TWR &dep) {
  int idx;
  do {
    idx = aleat(0, (ListOfTWR.size() - 1));
  } while (ListOfTWR[idx] == dep);
  return ListOfTWR[idx];
}

ostream &operator<<(ostream &os, const CCR &T) {
  os << "List :" << endl;
  vector<TWR> l = T.getList();
  vector<TWR>::iterator it = l.begin();
  while (it != l.end()) {
    cout << *it++ << endl;
  }
  return os;
}

void CCR::display(RenderWindow &window) {
  vector<TWR>::iterator it = ListOfTWR.begin();
  CircleShape _shape(5.f);
  _shape.setFillColor(Color::Red);
  while (it != ListOfTWR.end()) {
    _shape.setPosition((*it).getPist().getX(), (*it).getPist().getY());
    window.draw(_shape);
    _shape.setPosition((*it).getParking().getX(), (*it).getParking().getY());
    window.draw(_shape);
    _shape.setPosition((*it).getDeparture().getX(),
                       (*it).getDeparture().getY());
    window.draw(_shape);
    _shape.setPosition((*it).getArrival().getX(), (*it).getArrival().getY());
    window.draw(_shape);
    Text text;
    Font font;
    text.setString(it->getName());
    font.loadFromFile("../files/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Red);
    text.setStyle(Text::Bold);
    text.setPosition(it->getPist().getX() - 13, it->getPist().getY() + 10);
    window.draw(text);
    *it++;
  }
};