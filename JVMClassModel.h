#ifndef JVMCLASSMODEL_H
#define JVMCLASSMODEL_H

#include <QAbstractListModel>

#include "JVMClassList.h"

class JVMClassModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit JVMClassModel(JVMClassList classList, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex byName(QString className) const;

    JVMClassList classes() const;
    
private:
    JVMClassList classList;
};

#endif // JVMCLASSMODEL_H
