#include "SourceModel.h"

#include "JavaName.h"

#include <QDebug>

SourceModel::SourceModel(QDir sourceDir, SourceList sourceList, QObject *parent)
    : QAbstractListModel(parent)
    , sourceDir(sourceDir)
    , sourceList(sourceList)
{
}

int SourceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return sourceList.size();
}

QVariant SourceModel::data(const QModelIndex &index, int role) const
{
    Source const &item = sourceList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return item.relativeName(sourceDir);
    }

    return QVariant();
}


bool SourceModel::compile(QDir source, QDir target) const
{
    return sourceList.compile(source, target);
}
