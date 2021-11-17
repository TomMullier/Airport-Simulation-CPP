#include "./point3D.hpp"
#include <cstddef>

#include <vector>
using namespace std;

class Trajectory {
private:
  Point3D *points;
  size_t numberOfPoints;

public:
  Trajectory(const size_t nb_points);
  Trajectory(Point3D *points, int &number);
  ~Trajectory();

  void print();
  float getTotalDistance();

  // Getters
  Point3D &getPoint(const int &n);
  size_t getNumberOfPoints();
};