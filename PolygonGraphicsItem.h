#pragma once

#include <QGraphicsObject>
#include <QRectF>
#include <QList>
#include <QColor>

class Polygon;
class PointGraphicsItem;

class PolygonGraphicsItem : public QGraphicsObject {
    Q_OBJECT

    public:
        PolygonGraphicsItem(Polygon* poly, const QColor& color, QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) override;

        void pointMoved(PointGraphicsItem* point);

    private:
        Polygon* poly;

        QList<PointGraphicsItem*> points;

        static constexpr double penWidth = 5;

        QColor color;

    signals:
        void changed();

    public slots:
        void update();
};
