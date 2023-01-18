#include "MyRandom.h"

double MyRandom::UniDist(double min, double max) {
    uniform_real_distribution<double> Dist(min, max);
    return Dist(rd);
}