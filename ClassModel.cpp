#include "ClassModel.h"

#include "JavaName.h"

#include <QDebug>

ClassModel::ClassModel(ClassList classList, QObject *parent)
    : QAbstractListModel(parent)
    , classList(classList)
{
}

int ClassModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return classList.size();
}

QVariant ClassModel::data(const QModelIndex &index, int role) const
{
    Class const &item = classList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return JavaName::demangle(item.name());
    case Qt::UserRole:
        return QVariant::fromValue(item);
    }

    return QVariant();
}

QModelIndex ClassModel::byName(QString className) const
{
    for (int i = 0; i < classList.size(); i++)
        if (JavaName::demangle(classList.at(i).name()) == className)
            return index(i);
    return QModelIndex();
}

ClassList ClassModel::classes() const
{
    return classList;
}
