#include "./TWR.hpp"

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
  // string getName() const { return name; };
  // Point3D getParking() const { return parking; };
  // Point3D getPist() const { return pist; };
  // Point3D getDeparture() const { return departure; };
  // Point3D getArrival() const { return arrival; };
  friend ostream &operator<<(ostream &os, const CCR &T);
};