#ifndef JVMSOURCEMODEL_H
#define JVMSOURCEMODEL_H

#include <QAbstractListModel>
#include <QDir>

#include "SourceList.h"

class SourceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SourceModel(QDir sourceDir, SourceList sourceList, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    bool compile(QDir source, QDir target) const;

private:
    QDir const sourceDir;
    SourceList sourceList;
};

#endif // JVMSOURCEMODEL_H
