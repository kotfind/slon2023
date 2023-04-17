#pragma once

#include <QGraphicsObject>
#include <QRectF>
#include <QList>

class Polygon;

class PolygonGraphicsItem : public QGraphicsObject {
    Q_OBJECT

    public:
        PolygonGraphicsItem(Polygon* poly, QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) override;

    private:
        Polygon* poly;

        QList<QPointF> points;

    signals:
        void changed();

    public slots:
        void update();
};
