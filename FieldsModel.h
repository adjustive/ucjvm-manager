#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H

#include <QAbstractTableModel>

#include "JVMClass.h"

class FieldsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FieldsModel(JVMClass classData, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    JVMClass classData;
};

#endif // FIELDSMODEL_H
