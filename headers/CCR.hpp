#include "./TWR.hpp"

#include <SFML/Graphics.hpp>
#include <string>

int aleat(int val1, int val2);


class CCR {
private:
  vector<TWR> ListOfTWR;

public:
  CCR();
  vector<TWR> getList() const{return ListOfTWR;};
  TWR getDep() const;
  TWR getArr(const TWR &dep);
  friend ostream &operator<<(ostream &os, const CCR &T);
  void display(sf::RenderWindow &window);
};