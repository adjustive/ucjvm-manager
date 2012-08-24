#include "ConstantPoolInfo_Utf8.h"

#include <vector>

ConstantPoolInfo_Utf8::ConstantPoolInfo_Utf8(QDataStream &data)
{
    quint16 size;
    data >> size;

    std::vector<char> bytes(size);
    data.readRawData(&bytes[0], size);

    d.string = QString::fromUtf8(&bytes[0], size);
}

ConstantPoolInfo_Utf8::ConstantPoolInfo_Utf8(QString string)
{
    d.string = string;
}

void ConstantPoolInfo_Utf8::print() const
{
    qDebug("Utf8 %s", d.string.toUtf8().constData());
}


QString ConstantPoolInfo_Utf8::string() const
{
    return d.string;
}
