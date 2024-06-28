#pragma once
enum EInternal{EC_InternalUseOnlyConstructor};

enum EObjectFlags
{
    RF_NoFlags = 0x00000000,

    RF_ClassDefaultObject = 0x00000010,

    RF_Class = 0x00000020
};