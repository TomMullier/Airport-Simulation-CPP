#include "./TWR.hpp"

#include <SFML/Graphics.hpp>
#include <string>

int aleat(int val1, int val2);


class CCR {
private:
  vector<TWR*> ListOfTWR;

public:
  CCR();
  vector<TWR*> getList() {return ListOfTWR;};
  TWR* getDep();
  TWR* getArr(TWR* &dep);
  friend ostream &operator<<(ostream &os, const CCR &T);
  void display(sf::RenderWindow &window);
};