#include "PolygonGraphicsItem.h"

#include "Polygon.h"

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
    QRectF ans;
    for (const auto& pt : points) {
        int sz = 1;
        ans = ans.united(QRectF(
            pt.x() - sz,
            pt.y() - sz,
            2 * sz,
            2 * sz
        ));
    }
    return ans;
}

void PolygonGraphicsItem::paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) {
    QPainterPath path;
    path.moveTo(poly->last());
    for (const auto& pt : points) {
        path.lineTo(pt);
    }
    qp->fillPath(path, Qt::red);
}

void PolygonGraphicsItem::update() {
    prepareGeometryChange();
    points.clear();
    for (const auto& pt : *poly) {
        points << pt;
    }
    QGraphicsObject::update();
}
