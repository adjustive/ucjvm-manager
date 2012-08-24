#include "Methods.h"

Methods::Methods()
{
}

Methods::Methods(QDataStream &data, ConstantPool const &cp)
{
    quint16 count;
    data >> count;

    for (int i = 0; i < count; i++)
    {
        methods.append(Method(data, cp));
    }
}

quint16 Methods::count() const
{
    return methods.size();
}

Method const &Methods::get(int index) const
{
    return methods[index];
}
