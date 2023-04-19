#include "MainWindow.h"

#include "Polygon.h"
#include "PolygonModel.h"
#include "EditableTableWidget.h"
#include "PolygonGraphicsItem.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
    polys{
        std::make_unique<Polygon>(),
        std::make_unique<Polygon>()
    }
{
    graphicsView = new QGraphicsView(this);
    setCentralWidget(graphicsView);

    polys[0]->append({ 300,  200});
    polys[0]->append({ 100,  100});
    polys[0]->append({ 200,  400});
    polys[0]->append({-100,  300});
    polys[0]->append({-100,  400});
    polys[0]->append({-300,  100});
    polys[0]->append({-100, -300});

    polys[1]->append({ 200,  300});
    polys[1]->append({ 100,  100});
    polys[1]->append({ 400,  200});
    polys[1]->append({ 300, -100});
    polys[1]->append({ 400, -100});
    polys[1]->append({ 100, -300});
    polys[1]->append({-300, -100});

    graphicsScene = new QGraphicsScene(this);
    graphicsView->setScene(graphicsScene);

    for (int i = 0; i < 2; ++i) {
        auto* dock = new QDockWidget(tr("Polygon %1").arg(i + 1), this);
        polyWidgets[i] = new EditableTableWidget(this);
        dock->setWidget(polyWidgets[i]);
        addDockWidget(Qt::RightDockWidgetArea, dock);

        polyModels[i] = new PolygonModel(polys[i].get(), this);
        polyWidgets[i]->setModel(polyModels[i]);

        polyItems[i] = new PolygonGraphicsItem(
            polys[i].get(),
            i == 0 ? Qt::red : Qt::blue
        );
        graphicsScene->addItem(polyItems[i]);

        connect(
            polyModels[i],
            &PolygonModel::changed,
            polyItems[i],
            &PolygonGraphicsItem::update
        );

        connect(
            polyModels[i],
            &PolygonModel::changed,
            this,
            &MainWindow::onPolygonChanged
        );

        connect(
            polyItems[i],
            &PolygonGraphicsItem::changed,
            polyModels[i],
            &PolygonModel::update
        );

        connect(
            polyItems[i],
            &PolygonGraphicsItem::changed,
            this,
            &MainWindow::onPolygonChanged
        );
    }

    onPolygonChanged();
}

void MainWindow::onPolygonChanged() {
    // Clear old
    for (auto* item : intersectionItems) {
        graphicsScene->removeItem(item);
        delete item;
    }
    intersectionItems.clear();
    intersection.clear();

    // Generate new
    intersection = intersect(*polys[0], *polys[1]);
    for (auto& poly : intersection) {
        auto* item = new PolygonGraphicsItem(
            &poly,
            Qt::green,
            true /* readonly */
        );
        graphicsScene->addItem(item);
        intersectionItems.append(item);
    }
}
