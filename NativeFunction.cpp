#include "NativeFunction.h"

NativeFunction::NativeFunction(QString className,
                               QString description,
                               quint16 id,
                               QString name,
                               QString params)
    : className(className)
    , description(description)
    , id(id)
    , name(name)
    , params(params)
{
}
