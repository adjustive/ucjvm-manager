#ifndef JVMCLASSLIST_H
#define JVMCLASSLIST_H

#include <QList>
#include <QDir>

#include "Class.h"

class ClassList : private QList<Class>
{
public:
    ClassList(const QList<QFileInfo> &files);

    using QList<Class>::const_reference;
    using QList<Class>::const_iterator;

    using QList<Class>::size;
    using QList<Class>::at;

    using QList<Class>::begin;
    using QList<Class>::end;
    using QList<Class>::push_back;

    bool containsName(QString className) const;
    Class const *byName(QString className) const;
    void createArrayClasses();
    void linkSuperClasses();
};

#endif // JVMCLASSLIST_H
