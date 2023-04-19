#include "PointGraphicsItem.h"

#include "PolygonGraphicsItem.h"

#include <QSize>
#include <QPainter>
#include <QPen>

PointGraphicsItem::PointGraphicsItem(
    QGraphicsItem* parent
) : QGraphicsItem(parent)
{}

QRectF PointGraphicsItem::getRect() const {
    return {
        -radius,
        -radius,
        2 * radius,
        2 * radius
    };
}

QRectF PointGraphicsItem::boundingRect() const {
    return getRect().marginsAdded({1, 1, 1, 1});
}

void PointGraphicsItem::paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!static_cast<PolygonGraphicsItem*>(parentItem())->isReadOnly()) {
        qp->setPen(QPen(Qt::black,Qt::SolidLine));
        qp->setBrush(Qt::NoBrush);
        qp->drawEllipse(getRect());
    }
}

QVariant PointGraphicsItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange) {
        static_cast<PolygonGraphicsItem*>(parentItem())->pointMoved(this);
    }
    return value;
}
