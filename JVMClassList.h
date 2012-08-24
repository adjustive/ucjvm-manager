#ifndef JVMCLASSLIST_H
#define JVMCLASSLIST_H

#include <QList>
#include <QDir>

#include "JVMClass.h"

class JVMClassList : private QList<JVMClass>
{
public:
    JVMClassList(QDir dir);

    using QList<JVMClass>::const_reference;
    using QList<JVMClass>::const_iterator;

    using QList<JVMClass>::size;
    using QList<JVMClass>::at;

    using QList<JVMClass>::begin;
    using QList<JVMClass>::end;
    using QList<JVMClass>::push_back;

    bool containsName(QString className) const;
    void createArrayClasses();
};

#endif // JVMCLASSLIST_H
