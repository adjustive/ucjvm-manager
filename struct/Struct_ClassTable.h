#ifndef STRUCT_CLASSTABLE_H
#define STRUCT_CLASSTABLE_H

#include "Struct_Class.h"
struct JVMClassList;

#include <QList>

class Struct_ClassTable : public Struct
{
public:
    Struct_ClassTable(const JVMClassList &classList, quint32 baseAddress);

    void writeThis(DataWriter &data) const;

private:
    void moveClass(QString name, int index);
    void sort();
    quint32 computeClassPositions(quint32 baseAddress);

private:
    QList<Struct_Class> classes;
};

#endif // STRUCT_CLASSTABLE_H
