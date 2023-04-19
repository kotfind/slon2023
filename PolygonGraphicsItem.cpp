#include "PolygonGraphicsItem.h"

#include "Polygon.h"
#include "PointGraphicsItem.h"

#include <QPainter>
#include <QPainterPath>

PolygonGraphicsItem::PolygonGraphicsItem(
    Polygon* poly,
    QGraphicsItem* parent
) : poly(poly),
    QGraphicsObject(parent)
{
    update();
}

QRectF PolygonGraphicsItem::boundingRect() const {
    return childrenBoundingRect();
}

void PolygonGraphicsItem::paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) {
    QPainterPath path;
    path.moveTo(points.last()->pos());
    for (auto* pt : points) {
        path.lineTo(pt->pos());
    }
    qp->fillPath(path, Qt::red);
}

void PolygonGraphicsItem::update() {
    prepareGeometryChange();
    for (auto* pt : points) {
        delete pt;
    }
    points.clear();
    for (const auto& pt : *poly) {
        auto* point = new PointGraphicsItem(this);
        point->setPos(mapFromScene(pt));
        points << point;
    }
    QGraphicsObject::update();
}
