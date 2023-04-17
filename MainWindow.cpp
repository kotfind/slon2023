#include "MainWindow.h"

#include "Polygon.h"
#include "PolygonModel.h"
#include "EditableTableWidget.h"
#include "PolygonGraphicsItem.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
    poly(std::make_unique<Polygon>())
{
    createUi();
    createDocks();

    poly->append({ 300,  200});
    poly->append({ 100,  100});
    poly->append({ 200,  400});
    poly->append({-100,  300});
    poly->append({-100,  400});
    poly->append({-300,  100});
    poly->append({-100, -300});

    polyModel = new PolygonModel(poly.get(), this);
    polyWidget->setModel(polyModel);

    graphicsScene = new QGraphicsScene(this);
    graphicsView->setScene(graphicsScene);

    polyItem = new PolygonGraphicsItem(poly.get());
    graphicsScene->addItem(polyItem);

    connect(
        polyModel,
        &PolygonModel::changed,
        polyItem,
        &PolygonGraphicsItem::update
    );

    connect(
        polyItem,
        &PolygonGraphicsItem::changed,
        polyModel,
        &PolygonModel::update
    );
}

void MainWindow::createUi() {
    graphicsView = new QGraphicsView(this);
    setCentralWidget(graphicsView);
}

void MainWindow::createDocks() {
    auto* dock = new QDockWidget(tr("Polygon"), this);
    polyWidget = new EditableTableWidget(this);
    dock->setWidget(polyWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}
