#ifndef ATTRIBUTESINFO_SOURCEFILE_H
#define ATTRIBUTESINFO_SOURCEFILE_H

#include "AttributesInfo.h"

class AttributesInfo_SourceFile : public AttributesInfo
{
public:
    AttributesInfo_SourceFile(QDataStream &data);

private:
    quint16 sourceFileIndex;
};

#endif // ATTRIBUTESINFO_SOURCEFILE_H
