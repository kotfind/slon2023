#include "EditableTableWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>

EditableTableWidget::EditableTableWidget(QWidget* parent)
  : QWidget(parent)
{
    createUi();
}

void EditableTableWidget::createUi() {
    auto* vbox = new QVBoxLayout;
    setLayout(vbox);

    // Buttons
    auto* hbox = new QHBoxLayout;
    vbox->addLayout(hbox);

    auto* insertButton = new QPushButton("+", this);
    hbox->addWidget(insertButton);
    connect(
        insertButton,
        &QPushButton::clicked,
        this,
        &EditableTableWidget::onInsertClicked
    );

    auto* removeButton = new QPushButton("-", this);
    hbox->addWidget(removeButton);
    connect(
        removeButton,
        &QPushButton::clicked,
        this,
        &EditableTableWidget::onRemoveClicked
    );

    hbox->addStretch(1);

    // View
    view = new QTableView(this);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    vbox->addWidget(view);
}

void EditableTableWidget::setModel(QAbstractItemModel* model) {
    view->setModel(model);
}

int EditableTableWidget::getCurrentRow() {
    const auto& index = view->currentIndex();
    return index.isValid()
        ? index.row()
        : 0;
}

void EditableTableWidget::onInsertClicked() {
    view->model()->insertRow(getCurrentRow());
}

void EditableTableWidget::onRemoveClicked() {
    view->model()->removeRow(getCurrentRow());
}
