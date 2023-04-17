#pragma once

#include "Polygon.h"

#include <QMainWindow>
#include <memory>
#include <QGraphicsView>
#include <QGraphicsScene>

class PolygonModel;
class EditableTableWidget;
class PolygonGraphicsItem;

class MainWindow : public QMainWindow {
    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        void createUi();
        void createDocks();

        std::unique_ptr<Polygon> poly;
        PolygonModel* polyModel;
        EditableTableWidget* polyWidget;
        PolygonGraphicsItem* polyItem;

        QGraphicsView* graphicsView;
        QGraphicsScene* graphicsScene;
};
