#pragma once

#include <QGraphicsItem>
#include <QRectF>
#include <QList>

class Polygon;

class PolygonGraphicsItem : public QGraphicsItem {
    public:
        PolygonGraphicsItem(Polygon* poly, QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) override;

    private:
        Polygon* poly;
};
