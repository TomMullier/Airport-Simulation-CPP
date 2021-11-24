#include "../headers/CCR.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR ','

CCR::CCR() {
  fstream file;
  file.open("../files/ListTWR.txt", ios::in);
  if (file.is_open()) {
    float pa1, pa2, pi1, pi2, dep1, dep2, dep3, arr1, arr2, arr3;
    string line;
    string _name;
    while (getline(file, line)) {
      stringstream stream(line);
      string str_comp;
      int counter = 1;

      while (getline(stream, str_comp, SEPARATOR)) {
        switch (counter) {
        case 1: {
          _name = str_comp;
          counter++;
          break;
        }
        case 2: {
          pa1 = stof(str_comp);
          counter++;
          break;
        }
        case 3: {
          pa2 = stof(str_comp);
          counter++;
          break;
        }
        case 4: {
          pi1 = stof(str_comp);
          counter++;
          break;
        }
        case 5: {
          pi2 = stof(str_comp);
          counter++;
          break;
        }
        case 6: {
          dep1 = stof(str_comp);
          counter++;
          break;
        }
        case 7: {
          dep2 = stof(str_comp);
          counter++;
          break;
        }
        case 8: {
          dep3 = stof(str_comp);
          counter++;
          break;
        }
        case 9: {
          arr1 = stof(str_comp);
          counter++;
          break;
        }
        case 10: {
          arr2 = stof(str_comp);
          counter++;
          break;
        }
        case 11: {
          arr3 = stof(str_comp);
          counter++;
          break;
        }
        }
      }
      TWR t(_name, Point3D(pa1, pa2, 0), Point3D(pi1, pi2, 0),
            Point3D(dep1, dep2, dep3), Point3D(arr1, arr2, arr3));
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
