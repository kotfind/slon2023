#include "PolygonGraphicsItem.h"

#include "Polygon.h"

#include <QPainter>
#include <QPainterPath>

PolygonGraphicsItem::PolygonGraphicsItem(
    Polygon* poly,
    QGraphicsItem* parent
) : poly(poly),
    QGraphicsItem(parent)
{
    
}

QRectF PolygonGraphicsItem::boundingRect() const {
    QRectF ans;
    for (const auto& pt : *poly) {
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
    for (const auto& pt : *poly) {
        path.lineTo(pt);
    }
    qp->fillPath(path, Qt::red);
}
