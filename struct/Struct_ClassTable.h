#ifndef STRUCT_CLASSTABLE_H
#define STRUCT_CLASSTABLE_H

#include "Struct_Class.h"
struct JVMClassList;

#include <QList>
class QTextStream;

class Struct_ClassTable : public Struct
{
public:
    Struct_ClassTable(const JVMClassList &classList, quint32 baseAddress, QList<NativeFunction> const &nativeInterface);

    Struct_Class const &byName(QString name) const;

    quint8 alignment() const { return 4; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "ClassTable"; }

private:
    void moveClass(int index, QString name);
    void sort();

    void setStaticDataHandles();
    void loadNativeInterface(QList<NativeFunction> const &nativeInterface);
    void resolveClassReferences();
    void computeClassSizes();
    void computeFieldOffsets();

private:
    QList<Struct_Class> classes;
};

#endif // STRUCT_CLASSTABLE_H
