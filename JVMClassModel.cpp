#include "JVMClassModel.h"

#include "JavaName.h"

#include <QDebug>

JVMClassModel::JVMClassModel(JVMClassList classList, QObject *parent)
    : QAbstractListModel(parent)
    , classList(classList)
{
}

int JVMClassModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return classList.size();
}

QVariant JVMClassModel::data(const QModelIndex &index, int role) const
{
    JVMClass const &item = classList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return JavaName::demangle(item.name());
    case Qt::UserRole:
        return QVariant::fromValue(item);
    }

    return QVariant();
}

JVMClassList JVMClassModel::classes() const
{
    return classList;
}
