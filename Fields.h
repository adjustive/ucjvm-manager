#ifndef FIELDS_H
#define FIELDS_H

#include "Field.h"
class ConstantPool;

struct FieldsPrivate
{
    QList<Field> fields;
};

class Fields
{
public:
    Fields();
    Fields(QDataStream &data, ConstantPool const &cp);

    quint16 count() const;
    Field const &get(int index) const;
    QList<Field> fields() const;

private:
    FieldsPrivate d;
};

#endif // FIELDS_H
