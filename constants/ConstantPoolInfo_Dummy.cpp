#include "ConstantPoolInfo_Dummy.h"

#include <QDebug>

ConstantPoolInfo_Dummy::ConstantPoolInfo_Dummy()
{
}


void ConstantPoolInfo_Dummy::print() const
{
    qDebug("dummy CPI");
}
