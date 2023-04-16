#pragma once

#include <QMainWindow>
#include <memory>

#include "Polygon.h"

class PolygonModel;
class EditableTableWidget;

class MainWindow : public QMainWindow {
    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        void createUi();
        void createDocks();

        std::unique_ptr<Polygon> poly;
        PolygonModel* polyModel;
        EditableTableWidget* polyWidget;
};
