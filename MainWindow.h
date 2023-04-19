#pragma once

#include "Polygon.h"

#include <QMainWindow>
#include <memory>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>

class PolygonModel;
class EditableTableWidget;
class PolygonGraphicsItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        std::unique_ptr<Polygon> polys[2];
        PolygonModel* polyModels[2];
        EditableTableWidget* polyWidgets[2];
        PolygonGraphicsItem* polyItems[2];

        QGraphicsView* graphicsView;
        QGraphicsScene* graphicsScene;

        QList<Polygon> intersection;
        QList<PolygonGraphicsItem*> intersectionItems;

    private slots:
        void onPolygonChanged();
};
