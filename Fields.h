#ifndef FIELDS_H
#define FIELDS_H

#include "Field.h"
class ConstantPool;

class Fields
{
public:
    Fields();
    Fields(QDataStream &data, ConstantPool const &cp);

    quint16 count() const;
    Field const &get(int index) const;

private:
    QList<Field> fields;
};

#endif // FIELDS_H
