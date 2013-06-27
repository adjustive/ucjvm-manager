#include "AttributesInfo_Signature.h"

#include <QDataStream>

AttributesInfo_Signature::AttributesInfo_Signature(QDataStream &data)
{
    data >> signatureIndex;
}
