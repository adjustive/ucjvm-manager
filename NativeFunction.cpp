#include "NativeFunction.h"

NativeFunction::NativeFunction(QString className,
                               QString description,
                               QString id,
                               QString name,
                               QString params)
    : className(className)
    , description(description)
    , id(id)
    , name(name)
    , params(params)
{
}
