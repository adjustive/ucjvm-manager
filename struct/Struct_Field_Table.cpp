#include "Struct_Field_Table.h"

#include "Struct_Field.h"
#include "Fields.h"
#include "DataWriter.h"
#include "JavaName.h"

#include <QTextStream>

Struct_Field_Table::Struct_Field_Table(Fields const &fields)
{
    foreach (Field const &field, fields.fields())
        this->fields.append(Struct_Field(field));
}

Struct_Field const *Struct_Field_Table::getField(QString name, QString descriptor) const
{
#if 0
    qDebug("resolving field: %s %s",
           JavaName::demangle(descriptor).toUtf8().constData(),
           name.toUtf8().constData());
#endif
    foreach (Struct_Field const &field, fields)
        if (field.name == name && field.descriptor == descriptor)
        {
#if 0
            qDebug("field resolved: %s %s (%p)",
                   JavaName::demangle(descriptor).toUtf8().constData(),
                   name.toUtf8().constData(),
                   &field);
#endif
            return &field;
        }

    return NULL;
}

void Struct_Field_Table::writeStruct(DataWriter &data) const
{
    data.put16(fields.size());
    data.pad16();

    foreach (Struct_Field const &field, fields)
        data.putAddress(field);
}

void Struct_Field_Table::writeData(DataWriter &data) const
{
    foreach (Struct_Field const &field, fields)
        field.write(data);
}

quint32 Struct_Field_Table::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    for (int i = 0; i < fields.size(); i++)
        baseAddress = fields[i].computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_Field_Table::printMemoryMap(QTextStream &ts) const
{
    ts << "Field_Table @0x" << structStart << " {\n";

    foreach (Struct_Field const &field, fields)
        field.printMemoryMap(ts);
    ts << "    }\n";
}
