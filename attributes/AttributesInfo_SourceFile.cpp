#include "AttributesInfo_SourceFile.h"

#include <QDataStream>

AttributesInfo_SourceFile::AttributesInfo_SourceFile(QDataStream &data)
{
    data >> sourceFileIndex;
}
