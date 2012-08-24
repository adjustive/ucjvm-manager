#ifndef ATTRIBUTESINFO_SIGNATURE_H
#define ATTRIBUTESINFO_SIGNATURE_H

#include "AttributesInfo.h"

class AttributesInfo_Signature : public AttributesInfo
{
public:
    AttributesInfo_Signature(QDataStream &data);

private:
    quint16 signatureIndex;
};

#endif // ATTRIBUTESINFO_SIGNATURE_H
