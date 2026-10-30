#ifndef LAB04_DISTANCE_H
#define LAB04_DISTANCE_H

// Ч2. Только объявления функций.
// Ч3. Своё пространство имён.
namespace lab04 {

// Ч1. Перегрузки функции distance.

// Расстояние между двумя точками на плоскости (2D).
// Параметры: x1, y1 — первая точка; x2, y2 — вторая.
double distance(double x1, double y1, double x2, double y2);

// Расстояние между двумя точками в пространстве (3D).
// Параметры: x1, y1, z1 — первая точка; x2, y2, z2 — вторая.
double distance(double x1, double y1, double z1,
                double x2, double y2, double z2);

} // namespace lab04

#endif // LAB04_DISTANCE_H