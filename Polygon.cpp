#include "Polygon.h"

Polygon::Polygon()
  : QList<QPointF>()
{}

QList<Polygon> intersect(const Polygon& p1, const Polygon& p2) {
    Polygon p;
    p.append({ 100,  100});
    p.append({-100,  100});
    p.append({-100, -100});
    p.append({ 100, -100});
    return { p };
}
