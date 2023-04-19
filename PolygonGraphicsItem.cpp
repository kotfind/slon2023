#include "PolygonGraphicsItem.h"

#include "Polygon.h"
#include "PointGraphicsItem.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QColor>

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

    auto pen = qp->pen();
    pen.setColor(Qt::red);
    pen.setWidthF(penWidth);
    pen.setCosmetic(false);
    qp->setPen(pen);

    auto brush = qp->brush();
    auto color = QColor(Qt::red);
    color.setAlphaF(0.5);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    qp->setBrush(brush);

    qp->drawPath(path);
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
        point->setFlags(
            point->flags() |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges
        );
        points << point;
    }

    QGraphicsObject::update();
}

void PolygonGraphicsItem::pointMoved(PointGraphicsItem* point) {
    prepareGeometryChange();

    auto i = points.indexOf(point);
    (*poly)[i] = mapToScene(point->pos());

    QGraphicsObject::update();
    emit changed();
}
