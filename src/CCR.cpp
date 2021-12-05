#include "../headers/CCR.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

#include "../headers/json.hpp"
using nlohmann::json;
using namespace sf;

/**
 * Constructor of CCR
 *
 * @return  CCR     CCR created and attributs set
 */
CCR::CCR() {
  std::ifstream file("../files/ListTWR.json");
  json j;
  file >> j;

  if (file.is_open()) {
    for (auto it = j.begin(); it != j.end(); ++it) {
      json temp;
      temp = *it;
      TWR *t = new TWR(temp["name"], temp["tag"],
                       Point3D(temp["parking"]["x"], temp["parking"]["y"], 0),
                       Point3D(temp["pist"]["x"], temp["pist"]["y"], 0),
                       Point3D(temp["departure"]["x"], temp["departure"]["y"],
                               temp["departure"]["z"]),
                       Point3D(temp["arrival"]["x"], temp["arrival"]["y"],
                               temp["arrival"]["z"]),
                       temp["limit"]);
      ListOfTWR.push_back(t);
    }
    file.close();
  } else {
    cout << "File 'ListTWR.txt' doesn't exist..." << endl;
    cout << "Please create a file named 'ListTWR.txt' with this pattern"
         << endl;
  }
}

CCR::~CCR(){
  delete [] &ListOfTWR;
}
/**
 * Choose a TWR of Departure
 *
 * @return  TWR     TWR of Departure for a plane
 */
TWR *CCR::getDep() const {
  int idx;
  do {
    idx = aleat(0, (ListOfTWR.size() - 1));
  } while (ListOfTWR[idx]->getLimit() == ListOfTWR[idx]->getNumberOfPlanes());
  return ListOfTWR[idx];
}

/**
 * Choose a TWR of Destionation different of Departure
 *
 * @return  TWR     TWR of Destination for a plane
 */
TWR *CCR::getArr(TWR *&dep) const {
  int idx;
  do {
    idx = aleat(0, (ListOfTWR.size() - 1));
  } while (ListOfTWR[idx] == dep);
  return ListOfTWR[idx];
}

/**
 * Display TWR of CCR on SFML window
 *
 * @return  void
 */
void CCR::display(RenderWindow &window) {
  vector<TWR *>::iterator it = ListOfTWR.begin();
  Vector2f rectSize(10,10);
  RectangleShape _shape(rectSize);
  _shape.setFillColor(Color::Red);
  while (it != ListOfTWR.end()) {
    _shape.setPosition((*it)->getPist().getX(), (*it)->getPist().getY());
    window.draw(_shape);
    _shape.setPosition((*it)->getParking().getX(), (*it)->getParking().getY());
    window.draw(_shape);
    _shape.setPosition((*it)->getDeparture().getX(),
                       (*it)->getDeparture().getY());
    window.draw(_shape);
    _shape.setPosition((*it)->getArrival().getX(), (*it)->getArrival().getY());
    window.draw(_shape);
    Text text;
    Font font;
    text.setString((*it)->getTag());
    font.loadFromFile("../files/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Red);
    text.setStyle(Text::Bold);
    text.setPosition((*it)->getPist().getX() - 13,
                     (*it)->getPist().getY() + 10);
    window.draw(text);
    *it++;
  }
};

/**
 * Operator << overloaded
 *
 * @return  ostream information to print
 */
ostream &operator<<(ostream &os, CCR &T) {
  os << "List :" << endl;
  vector<TWR *> l = T.getList();
  vector<TWR *>::iterator it = l.begin();
  while (it != l.end()) {
    cout << *it++ << endl;
  }
  return os;
}

/**
 * Find random number between 2 values
 *
 * @param   int  val1  minimum value
 * @param   int  val2  maximum value
 *
 * @return  int        random value
 */
int aleat(int val1, int val2) {
  if (val1 > val2)
    swap(val1, val2);
  return (rand() % ((val2 - val1) + 1)) + val1;
}