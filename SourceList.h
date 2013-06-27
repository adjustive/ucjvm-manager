#ifndef JVMSOURCELIST_H
#define JVMSOURCELIST_H

#include <QList>
#include <QDir>

#include "Source.h"

class SourceList : private QList<Source>
{
public:
    explicit SourceList(const QList<QFileInfo> &files);

    using QList<Source>::const_reference;
    using QList<Source>::const_iterator;

    using QList<Source>::size;
    using QList<Source>::at;

    using QList<Source>::begin;
    using QList<Source>::end;
    using QList<Source>::push_back;

    bool compile(QDir const &sourceDir, QDir const &targetDir) const;
};

#endif // JVMSOURCELIST_H
