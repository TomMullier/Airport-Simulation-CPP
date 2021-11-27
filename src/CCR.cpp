#include "../headers/CCR.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

#include "../headers/json.hpp"
using nlohmann::json;

CCR::CCR() {
  std::ifstream file("../files/ListTWR.json");
  json j;
  file >> j;

  if (file.is_open()) {
    for (auto it = j.begin(); it != j.end(); ++it) {
      json temp;
      temp = *it;
      TWR t(temp["name"],
            Point3D(temp["parking"]["x"], temp["parking"]["y"], 0),
            Point3D(temp["pist"]["x"], temp["pist"]["y"], 0),
            Point3D(temp["departure"]["x"], temp["departure"]["y"],
                    temp["departure"]["z"]),
            Point3D(temp["arrival"]["x"], temp["arrival"]["y"],
                    temp["arrival"]["z"]));
      ListOfTWR.push_back(t);
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
  int idx = aleat(0, ListOfTWR.size());
  return ListOfTWR[idx];
}

TWR CCR::getArr(const TWR &dep) {
  int idx;
  do {
    idx = aleat(0, ListOfTWR.size());
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
