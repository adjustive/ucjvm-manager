#include "SourceList.h"

#include <QDebug>
#include <QProcess>


SourceList::SourceList(QList<QFileInfo> const &files)
{
    this->reserve(files.size());
    foreach (QFileInfo const &info, files)
        this->append(Source(info));
}


bool SourceList::compile(const QDir &sourceDir, const QDir &targetDir) const
{
    QProcess compiler;

    QStringList sources;
    sources.reserve(this->size());

    sources << "-d" << sourceDir.relativeFilePath(targetDir.absolutePath());
    sources << "-classpath" << ".";

    foreach (Source const &source, *this)
        sources.append(source.relativeName(sourceDir));

    compiler.setWorkingDirectory(sourceDir.path());
    compiler.start("ecj", sources, QProcess::ReadOnly);
    compiler.waitForFinished(-1);

    qDebug() << compiler.readAllStandardOutput();
    qWarning() << compiler.readAllStandardError();

    return true;
}
