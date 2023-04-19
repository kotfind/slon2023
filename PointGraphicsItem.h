#pragma once

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>

class PointGraphicsItem : public QGraphicsItem {
    public:
        PointGraphicsItem(QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* qp, const QStyleOptionGraphicsItem*, QWidget*) override;

        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        QRectF getRect() const;

        static constexpr double radius = 5;
};
