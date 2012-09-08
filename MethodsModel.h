#ifndef METHODSMODEL_H
#define METHODSMODEL_H

#include <QAbstractTableModel>

#include "Class.h"

class MethodsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MethodsModel(Class classData, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    Class classData;
};

#endif // METHODSMODEL_H
