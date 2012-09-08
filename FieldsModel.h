#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H

#include <QAbstractTableModel>

#include "Class.h"

class FieldsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FieldsModel(Class classData, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    Class classData;
};

#endif // FIELDSMODEL_H
