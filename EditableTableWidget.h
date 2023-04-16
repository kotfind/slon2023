#pragma once

#include <QWidget>
#include <QTableView>

class QAbstractItemModel;

class EditableTableWidget : public QWidget {
    public:
        EditableTableWidget(QWidget* parent = nullptr);

        void setModel(QAbstractItemModel*);

    private:
        void createUi();

        int getCurrentRow();

        QTableView* view;

    private slots:
        void onInsertClicked();
        void onRemoveClicked();
};
