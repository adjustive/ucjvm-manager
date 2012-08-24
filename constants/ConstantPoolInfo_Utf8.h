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

    QString string() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_Utf8Private d;
};

#endif // CONSTANTPOOLINFO_UTF8_H
