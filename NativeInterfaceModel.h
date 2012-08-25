#ifndef NATIVEINTERFACEMODEL_H
#define NATIVEINTERFACEMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "NativeFunction.h"

class NativeInterfaceModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit NativeInterfaceModel(QList<NativeFunction> functions, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<NativeFunction> functions;
};

#endif // NATIVEINTERFACEMODEL_H
