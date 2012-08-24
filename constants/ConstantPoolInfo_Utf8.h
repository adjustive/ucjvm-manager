#ifndef CONSTANTPOOLINFO_UTF8_H
#define CONSTANTPOOLINFO_UTF8_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_Utf8Private
{
    QString string;
};

class ConstantPoolInfo_Utf8 : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Utf8(QDataStream &data);
    ConstantPoolInfo_Utf8(QString string);

    void print() const;

    QString string() const;

private:
    ConstantPoolInfo_Utf8Private d;
};

#endif // CONSTANTPOOLINFO_UTF8_H
