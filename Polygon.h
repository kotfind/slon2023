#pragma once

#include <QList>
#include <QPointF>

class Polygon : public QList<QPointF> {
    public:
        Polygon();
};

QList<Polygon> intersect(const Polygon&, const Polygon&);
