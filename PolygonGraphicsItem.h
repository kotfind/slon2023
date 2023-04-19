#pragma once

#include <QGraphicsObject>
#include <QRectF>
#include <QList>

class Polygon;
class PointGraphicsItem;

class PolygonGraphicsItem : public QGraphicsObject {
    Q_OBJECT

    public:
        PolygonGraphicsItem(Polygon* poly, QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) override;

        void pointMoved(PointGraphicsItem* point);

    private:
        Polygon* poly;

        QList<PointGraphicsItem*> points;

    signals:
        void changed();

    public slots:
        void update();
};
