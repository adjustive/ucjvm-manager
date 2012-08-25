#ifndef STRUCT_CLASSTABLE_H
#define STRUCT_CLASSTABLE_H

#include "Struct_Class.h"
struct JVMClassList;

#include <QList>
class QTextStream;

class Struct_ClassTable : public Struct
{
public:
    Struct_ClassTable(const JVMClassList &classList, quint32 baseAddress);

    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

private:
    void moveClass(QString name, int index);
    void sort();

private:
    QList<Struct_Class> classes;
};

#endif // STRUCT_CLASSTABLE_H
