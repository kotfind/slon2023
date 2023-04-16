#include "MainWindow.h"

#include "Polygon.h"
#include "PolygonModel.h"
#include "EditableTableWidget.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
    poly(std::make_unique<Polygon>())
{
    createUi();
    createDocks();

    poly->append({0, 5});
    poly->append({1, 0});
    poly->append({2, 2});
    poly->append({-1, 1});
    poly->append({3, 2});
    poly->append({1, 0});

    polyModel = new PolygonModel(poly.get(), this);
    polyWidget->setModel(polyModel);
}

void MainWindow::createUi() {
    auto* dummy = new QWidget(this);
    setCentralWidget(dummy);
}

void MainWindow::createDocks() {
    auto* dock = new QDockWidget(tr("Polygon"), this);
    polyWidget = new EditableTableWidget(this);
    dock->setWidget(polyWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}
