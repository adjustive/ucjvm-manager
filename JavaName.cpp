#include "JavaName.h"

#include <QDebug>
#include <QStringList>

static QString demangle1(QString::const_iterator &mangled)
{
    switch ((mangled++)->toAscii())
    {
    case 'C': return "char";
    case 'B': return "byte";
    case 'Z': return "boolean";
    case 'I': return "int";
    case 'J': return "long";
    case 'F': return "float";
    case 'D': return "double";
    case 'S': return "short";
    case 'V': return "void";
    case 'L':
        {
            QString::const_iterator start = mangled;
            do
                ++mangled;
            while (*mangled != ';');
            QString demangled(start, mangled - start);
            ++mangled;
            return demangled.replace('/', '.');
        }
    case '[':
        return demangle1(mangled) + "[]";
    default:
        return QString(--mangled).replace('/', '.');
    }
}

QString JavaName::demangle(QString mangled, QString functionName, QString className)
{
    QString::const_iterator it = mangled.constBegin();

    if (*it == '(')
    {
        ++it;
        QStringList argumentList;
        while (*it != ')')
            argumentList << demangle1(it);
        ++it;
        if (!className.isEmpty())
            functionName = className + "#" + functionName;
        return demangle1(it) + " " + functionName + "(" + argumentList.join(", ") + ")";
    }
    else
    {
        // Single type
        return demangle1(it);
    }
}


JavaName::JavaName()
{
}
