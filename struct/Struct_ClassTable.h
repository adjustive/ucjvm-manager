#ifndef STRUCT_CLASSTABLE_H
#define STRUCT_CLASSTABLE_H

#include "Struct_Class.h"
#include "Struct_ResourceTable.h"
struct ClassList;

#include <QList>
class QTextStream;

class Struct_ClassTable : public Struct
{
public:
    Struct_ClassTable(const ClassList &classList,
                      quint32 baseAddress,
                      QList<NativeFunction> const &nativeInterface,
                      QStringList resourceFiles,
                      ResourceEditor::Collection const &editors,
                      MemoryModel const &memoryModel);

    Struct_Class const &byName(QString name) const;

    MemoryModel::Align alignment() const { return MemoryModel::ADDRESS_ALIGN; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(const MemoryModel &memoryModel, quint32 baseAddress);
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
    Struct_ResourceTable resourceTable;
};

#endif // STRUCT_CLASSTABLE_H
