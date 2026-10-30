#include "distance.h"

#include <cmath>       // std::sqrt
#include <stdexcept>   // std::invalid_argument

namespace lab04 {

// Расстояние на плоскости:
// d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
double distance(double x1, double y1, double x2, double y2) {
    const double dx = x2 - x1;
    const double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

// Расстояние в пространстве:
// d = sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
double distance(double x1, double y1, double z1,
                double x2, double y2, double z2) {
    const double dx = x2 - x1;
    const double dy = y2 - y1;
    const double dz = z2 - z1;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

} // namespace lab04