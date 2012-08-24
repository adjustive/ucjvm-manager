#ifndef CONSTANTPOOLINFO_DUMMY_H
#define CONSTANTPOOLINFO_DUMMY_H

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Dummy : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Dummy();

    void print() const;
};

#endif // CONSTANTPOOLINFO_DUMMY_H
