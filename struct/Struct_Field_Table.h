#ifndef STRUCT_FIELD_TABLE_H
#define STRUCT_FIELD_TABLE_H

#include "Struct_Field.h"
class Fields;

#include <QList>

class Struct_Field_Table : public Struct
{
public:
    Struct_Field_Table(Fields const &fields);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

private:
    QList<Struct_Field> fields;
};

#endif // STRUCT_FIELD_TABLE_H
