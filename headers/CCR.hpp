#include "./TWR.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class CCR {
private:
  vector<TWR *> ListOfTWR;

public:
  // Constructor
  CCR();
  // Setters & Getters
  vector<TWR *> getList() { return ListOfTWR; };
  TWR *getDep() const;
  TWR *getArr(TWR *&dep) const;
  // Other functions
  void display(sf::RenderWindow &window);
  // Operator
  friend ostream &operator<<(ostream &os, const CCR &T);
};

int aleat(int val1, int val2);