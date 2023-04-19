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
    const QColor& color,
    bool readonly,
    QGraphicsItem* parent
) : QGraphicsObject(parent),
    poly(poly),
    color(color),
    readonly(readonly)
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
    pen.setColor(this->color);
    pen.setWidthF(penWidth);
    pen.setCosmetic(false);
    qp->setPen(pen);

    auto brush = qp->brush();
    auto color = QColor(this->color);
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
        if (!readonly) {
            point->setFlags(
                point->flags() |
                QGraphicsItem::ItemIsMovable |
                QGraphicsItem::ItemSendsGeometryChanges
            );
        }
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

bool PolygonGraphicsItem::isReadOnly() {
    return readonly;
}
