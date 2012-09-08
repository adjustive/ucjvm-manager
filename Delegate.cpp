#include "Delegate.h"

Delegate<int *()> ctor = ctor.constructor();
Delegate<int *()> ctor2 = ctor2.constructor<int>();
Delegate<int *()> method = method.create<Delegate<int *()>, &Delegate<int *()>::operator()>(&ctor);

Delegate<int *(int)> ctor3 = ctor3.constructor();
Delegate<int *(int)> method2 = method2.create<Delegate<int *(int)>, &Delegate<int *(int)>::operator()>(&ctor3);
