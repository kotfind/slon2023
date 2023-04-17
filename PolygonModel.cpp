#include "PolygonModel.h"

PolygonModel::PolygonModel(Polygon* poly, QObject* parent)
  : poly(poly),
    QAbstractTableModel(parent)
{}

int PolygonModel::rowCount(const QModelIndex& parent) const {
    return poly->size();
}

int PolygonModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant PolygonModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    auto pt = (*poly)[index.row()];
    switch (index.column()) {
        case 0: return pt.x();
        case 1: return pt.y();
    }
    return QVariant();
}

QVariant PolygonModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) {
        // Horizontal
        switch (section) {
            case 0: return "x";
            case 1: return "y";
        }
    } else {
        // Vertical
        return section + 1;
    }
    return QVariant();
}

bool PolygonModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole) return false;

    bool ok;
    double val = value.toDouble(&ok);
    if (!ok) return false;

    switch (index.column()) {
        case 0:
            (*poly)[index.row()].setX(val);
            break;

        case 1:
            (*poly)[index.row()].setY(val);
            break;

        default:
            return false;
    }

    emit changed();
    return true;
}

Qt::ItemFlags PolygonModel::flags(const QModelIndex& index) const {
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool PolygonModel::insertRows(int row, int count, const QModelIndex& parent) {
    if (parent.isValid()) return false;

    beginInsertRows(parent, row, row + count - 1);
    poly->insert(row, count, {0, 0});
    endInsertRows();

    emit changed();
    return true;
}

bool PolygonModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (parent.isValid()) return false;

    if (poly->size() - count < 3) return false;

    beginRemoveRows(parent, row, row + count - 1);
    poly->remove(row, count);
    endRemoveRows();

    emit changed();
    return true;
}

void PolygonModel::update() {
    beginResetModel();
    endResetModel();
}
