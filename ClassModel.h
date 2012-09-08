#ifndef JVMCLASSMODEL_H
#define JVMCLASSMODEL_H

#include <QAbstractListModel>

#include "ClassList.h"

class ClassModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ClassModel(ClassList classList, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex byName(QString className) const;

    ClassList classes() const;
    
private:
    ClassList classList;
};

#endif // JVMCLASSMODEL_H
