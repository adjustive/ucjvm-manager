#include "Source.h"

#include <QDir>

Source::Source(const QFileInfo &file)
    : file(file)
{
}


QString Source::name() const
{
    return file.fileName();
}


QString Source::relativeName(const QDir &path) const
{
    return path.relativeFilePath(file.absoluteFilePath());
}
