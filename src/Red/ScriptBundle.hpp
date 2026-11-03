#pragma once

#include <RED4ext/CName.hpp>
#include <RED4ext/Containers/DynArray.hpp>
#include <RED4ext/HashMap.hpp>
#include <RED4ext/Memory/Allocators.hpp>
#include <RED4ext/Mutex.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/Scripting/CProperty.hpp>
#include <RED4ext/Scripting/Functions.hpp>
#include <RED4ext/SharedSpinLock.hpp>

namespace Red
{
enum class EScriptDefinition : uint8_t
{
    Type = 0,
    Class,
    Constant, // Values for Enums and Bitfields
    Enum,
    Bitfield,
    Function,
    Parameter,
    LocalVar,
    Property,
    SourceFile,
};

enum class EScriptVisibility : uint8_t
{
    Public = 0,
    Protected,
    Private,
};

// IScriptDataObject
struct ScriptDefinition
{
    struct Flags
    {
        uint8_t isImported : 1; // 00
        uint8_t hasBase : 1;    // 01 - baseType is present
        uint8_t hasUnk30 : 1;   // 02 - unk30 is filled
        uint8_t isResolved : 1; // 03 - Set by the binder after resolving
        uint8_t b04 : 1;        // 04
        uint8_t b05 : 1;        // 05
        uint8_t b06 : 1;        // 06
        uint8_t b07 : 1;        // 07
    };

    virtual Memory::IAllocator* GetAllocator() = 0; // 00
    virtual ~ScriptDefinition() = 0;                // 08
    virtual EScriptDefinition GetType() = 0;        // 10
    virtual EScriptVisibility GetVisibility() = 0;  // 18
    virtual ScriptDefinition* GetBase() = 0;        // 20
    virtual CName GetName() = 0;                    // 28
    virtual bool IsImported() = 0;                  // 30

    CName name;                 // 08
    uint32_t unk10;             // 10
    uint8_t unk14;              // 14
    uint8_t unk15[0x18 - 0x15]; // 15
    uint64_t unk18;             // 18
    Flags flags;                // 20
    uint8_t unk21[0x28 - 0x21]; // 21
    CName baseType;             // 28
    DynArray<CName> unk30;      // 30
};
RED4EXT_ASSERT_SIZE(ScriptDefinition, 0x40);
RED4EXT_ASSERT_OFFSET(ScriptDefinition, baseType, 0x28);
RED4EXT_ASSERT_OFFSET(ScriptDefinition, unk30, 0x30);

struct ScriptFileInfo : ScriptDefinition
{
    uint32_t crc;               // 40
    uint32_t index;             // 44
    uint32_t hash;              // 48 - Murmur3 of path
    uint8_t unk4C[0x50 - 0x4C]; // 4C
    CString path;               // 50
};
RED4EXT_ASSERT_SIZE(ScriptFileInfo, 0x70);
RED4EXT_ASSERT_OFFSET(ScriptFileInfo, path, 0x50);

enum class EScriptType : uint8_t
{
    Primitive = 0,
    Class, // Class/Enum/Bitfield
    StrongHandle,
    WeakHandle,
    DynArray,
    StaticArray,
    ScriptRef,
};

// CScriptedDataTypeRef
struct ScriptType : ScriptDefinition
{
    CBaseRTTIType* rttiType;     // 40
    ScriptDefinition* innerType; // 48
    int32_t arraySize;           // 50
    EScriptType metaType;        // 54
};
RED4EXT_ASSERT_SIZE(ScriptType, 0x58);
RED4EXT_ASSERT_OFFSET(ScriptType, innerType, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptType, metaType, 0x54);

// CScriptedDataProperty
struct ScriptProperty : ScriptDefinition
{
    struct Flags
    {
        uint16_t isImported : 1; // 00
        uint16_t b01 : 1;        // 01
        uint16_t b02 : 1;        // 02
        uint16_t b03 : 1;        // 03
        uint16_t b04 : 1;        // 04
        uint16_t b05 : 1;        // 05
        uint16_t b06 : 1;        // 06
        uint16_t b07 : 1;        // 07
        uint16_t b08 : 1;        // 08
        uint16_t b09 : 1;        // 09
        uint16_t b10 : 1;        // 0A
        uint16_t b11 : 1;        // 0B
        uint16_t b12 : 1;        // 0C
        uint16_t b13 : 1;        // 0D
        uint16_t b14 : 1;        // 0E
        uint16_t b15 : 1;        // 0F
    };

    CProperty* rttiProp;                // 40
    ScriptDefinition* parent;           // 48
    Flags flags;                        // 50
    uint8_t unk52[0x58 - 0x52];         // 52
    Map<CString, CString> defaults;     // 58
    EScriptVisibility visibility;       // 80
    uint8_t unk81;                      // 81
    uint8_t unk82[0x88 - 0x82];         // 82
    HashMap<CName, CString> attributes; // 88
    ScriptType* type;                   // B8
    uint8_t unkC0;                      // C0
    uint8_t unkC1[0xC8 - 0xC1];         // C1
};
RED4EXT_ASSERT_SIZE(ScriptProperty, 0xC8);
RED4EXT_ASSERT_OFFSET(ScriptProperty, defaults, 0x58);
RED4EXT_ASSERT_OFFSET(ScriptProperty, visibility, 0x80);
RED4EXT_ASSERT_OFFSET(ScriptProperty, attributes, 0x88);
RED4EXT_ASSERT_OFFSET(ScriptProperty, type, 0xB8);

struct ScriptClass;
struct ScriptFunction;

// CScriptedDataFunctionParam
struct ScriptParameter : ScriptDefinition
{
    struct Flags
    {
        uint8_t isOptional : 1;     // 00
        uint8_t isOut : 1;          // 01
        uint8_t isShortCircuit : 1; // 02 - Got from redscript
        uint8_t isConst : 1;        // 03
    };

    CProperty* rttiProp;        // 40
    ScriptFunction* function;   // 48
    ScriptType* type;           // 50
    Flags flags;                // 58
    uint8_t unk59[0x60 - 0x59]; // 59
};
RED4EXT_ASSERT_SIZE(ScriptParameter, 0x60);

// CScriptedDataFunctionLocal
struct ScriptLocalVar : ScriptDefinition
{
    struct Flags
    {
        uint8_t isConst : 1; // 00
        uint8_t b01 : 1;     // 01
    };

    CProperty* rttiProp;        // 40
    ScriptFunction* function;   // 48
    ScriptType* type;           // 50
    Flags flags;                // 58
    uint8_t unk59[0x60 - 0x59]; // 59
};
RED4EXT_ASSERT_SIZE(ScriptLocalVar, 0x60);

// CScriptedDataFunction
struct ScriptFunction : ScriptDefinition
{
    struct ReturnValue
    {
        ScriptType* type;           // 00
        bool isConst;               // 08
        uint8_t unk09[0x10 - 0x09]; // 09
    };

    struct Flags
    {
        uint32_t isStatic : 1;     // 00
        uint32_t isExec : 1;       // 01
        uint32_t isTimer : 1;      // 02
        uint32_t isFinal : 1;      // 03
        uint32_t isNative : 1;     // 04
        uint32_t b05 : 1;          // 05
        uint32_t b06 : 1;          // 06
        uint32_t isEvent : 1;      // 07
        uint32_t b08 : 1;          // 08
        uint32_t b09 : 1;          // 09
        uint32_t b10 : 1;          // 0A
        uint32_t b11 : 1;          // 0B
        uint32_t b12 : 1;          // 0C
        uint32_t b13 : 1;          // 0D
        uint32_t b14 : 1;          // 0E
        uint32_t isConst : 1;      // 0F
        uint32_t isThreadsafe : 1; // 10
        uint32_t isScripted : 1;   // 11 - Seems pointless, for all functions isScripted != isNative
    };

    CBaseFunction* rttiFunc;             // 40
    ScriptClass* parent;                 // 48
    CName shortName;                     // 50
    DynArray<ScriptParameter*> params;   // 58
    DynArray<ScriptLocalVar*> localVars; // 68
    HashMap<CName, CString> attributes;  // 78
    uint64_t unkA8;                      // A8
    uint64_t unkB0;                      // B0
    ReturnValue returnValue;             // B8
    ScriptFunction* baseFunction;        // C8
    ScriptClass* baseClass;              // D0
    ScriptFunction* unkD8;               // D8
    DynArray<CName> overriddenNames;     // E0
    ScriptFunction* overridden;          // F0
    Flags flags;                         // F8
    DynArray<uint64_t> unk100;           // 100 - Runtime only
    DynArray<uint64_t> unk110;           // 110 - Runtime only
    CName operatorName;                  // 120
    uint8_t castValue;                   // 128
    EScriptVisibility visibility;        // 129
    uint8_t unk12A[0x130 - 0x12A];       // 12A
    DynArray<uint8_t> code;              // 130
    ScriptFileInfo* sourceFile;          // 140
    uint32_t sourceLine;                 // 148
    uint8_t isOverride;                  // 14C
    uint8_t unk14D[0x150 - 0x14D];       // 14D
};
RED4EXT_ASSERT_SIZE(ScriptFunction, 0x150);
RED4EXT_ASSERT_OFFSET(ScriptFunction, params, 0x58);
RED4EXT_ASSERT_OFFSET(ScriptFunction, attributes, 0x78);
RED4EXT_ASSERT_OFFSET(ScriptFunction, returnValue, 0xB8);
RED4EXT_ASSERT_OFFSET(ScriptFunction, flags, 0xF8);
RED4EXT_ASSERT_OFFSET(ScriptFunction, code, 0x130);
RED4EXT_ASSERT_OFFSET(ScriptFunction, sourceFile, 0x140);
RED4EXT_ASSERT_OFFSET(ScriptFunction, sourceLine, 0x148);

// CScriptedDataClass
struct ScriptClass : ScriptDefinition
{
    struct Flags
    {
        uint8_t isNative : 1;     // 00
        uint8_t isImportOnly : 1; // 01
        uint8_t isAbstract : 1;   // 02
        uint8_t isFinal : 1;      // 03
        uint8_t isStruct : 1;     // 04
    };

    CClass* rttiClass;                    // 40
    ScriptClass* parent;                  // 48
    DynArray<ScriptProperty*> properties; // 50
    DynArray<ScriptProperty*> overrides;  // 60
    DynArray<CName> unk70;                // 70 - Runtime only
    DynArray<ScriptFunction*> unk80;      // 80 - Runtime only
    DynArray<ScriptFunction*> functions;  // 90
    HashMap<CName, CString> attributes;   // A0
    EScriptVisibility visibility;         // D0
    Flags flags;                          // D1
    uint8_t unkD2[0xD8 - 0xD2];           // D2
};
RED4EXT_ASSERT_SIZE(ScriptClass, 0xD8);
RED4EXT_ASSERT_OFFSET(ScriptClass, parent, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptClass, properties, 0x50);
RED4EXT_ASSERT_OFFSET(ScriptClass, overrides, 0x60);
RED4EXT_ASSERT_OFFSET(ScriptClass, functions, 0x90);
RED4EXT_ASSERT_OFFSET(ScriptClass, attributes, 0xA0);
RED4EXT_ASSERT_OFFSET(ScriptClass, flags, 0xD1);

// CScriptedDataNamedValue
struct ScriptConstant : ScriptDefinition
{
    int64_t rttiValue;          // 40
    ScriptDefinition* parent;   // 48
    int64_t value;              // 50
    bool isNative;              // 58
    uint8_t unk59[0x60 - 0x59]; // 59
};
RED4EXT_ASSERT_SIZE(ScriptConstant, 0x60);

// CScriptedDataEnum
struct ScriptEnum : ScriptDefinition
{
    CEnum* rttiEnum;                     // 40
    DynArray<ScriptConstant*> constants; // 48
    DynArray<uint64_t> unk58;            // 58 - Runtime only
    uint8_t size;                        // 68
    bool isNative;                       // 69
    EScriptVisibility visibility;        // 6A
    uint8_t unk6B[0x70 - 0x6B];          // 6B
};
RED4EXT_ASSERT_SIZE(ScriptEnum, 0x70);
RED4EXT_ASSERT_OFFSET(ScriptEnum, constants, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptEnum, size, 0x68);
RED4EXT_ASSERT_OFFSET(ScriptEnum, isNative, 0x69);
RED4EXT_ASSERT_OFFSET(ScriptEnum, visibility, 0x6A);

// CScriptedDataBitfield
struct ScriptBitfield : ScriptDefinition
{
    CBitfield* rttiBitfield;             // 40
    DynArray<ScriptConstant*> constants; // 48
    uint8_t size;                        // 58
    bool isNative;                       // 59
    EScriptVisibility visibility;        // 5A
    uint8_t unk5B[0x60 - 0x5B];          // 5B
};
RED4EXT_ASSERT_SIZE(ScriptBitfield, 0x60);
RED4EXT_ASSERT_OFFSET(ScriptBitfield, constants, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptBitfield, size, 0x58);
RED4EXT_ASSERT_OFFSET(ScriptBitfield, isNative, 0x59);
RED4EXT_ASSERT_OFFSET(ScriptBitfield, visibility, 0x5A);

struct ScriptBundle;

struct ScriptBundleRef
{
    ScriptBundle* environment;  // 00
    bool isOwned;               // 08 - Owned bundle is freed in dtor
    uint8_t unk09[0x10 - 0x09]; // 09
};
RED4EXT_ASSERT_SIZE(ScriptBundleRef, 0x10);

// CScriptedDataEnvironment
struct ScriptBundle
{
    uint8_t unk00[0x08 - 0x00];                          // 000
    HashMap<CName, ScriptDefinition*> definitionsByName; // 008
    HashMap<CName, ScriptFunction*> functionsByName;     // 038
    HashMap<CName, ScriptType*> typesByName;             // 068
    DynArray<ScriptFileInfo*> files;                     // 098
    DynArray<ScriptFunction*> globals;                   // 0A8
    DynArray<ScriptEnum*> enums;                         // 0B8
    DynArray<ScriptBitfield*> bitfields;                 // 0C8
    DynArray<ScriptClass*> classes;                      // 0D8
    DynArray<ScriptType*> types;                         // 0E8
    DynArray<CString> strings;                           // 0F8
    HashMap<CString, uint32_t> stringIndices;            // 108
    SharedSpinLock typesLock;                            // 138
    uint8_t unk139[0x140 - 0x139];                       // 139
    Mutex stringMutex;                                   // 140
    DynArray<CString> filePaths;                         // 168
    uint32_t unk178;                                     // 178
    uint8_t unk17C[0x180 - 0x17C];                       // 17C
    ScriptBundle* baseBundle;                            // 180 - Set from outside (e.g. CScriptingSystem)
    DynArray<ScriptBundleRef*> dependencies;             // 188 - Set from outside (e.g. CScriptingSystem)
    DynArray<CName> extraTypes;                          // 198
    CString unk1A8;                                      // 1A8
    uint32_t bundleIndex;                                // 1C8 - Set from outside (e.g. CScriptingSystem)
    uint8_t unk1CC[0x1D0 - 0x1CC];                       // 1CC
    DynArray<ScriptProperty*> extraProperties;           // 1D0
    DynArray<uint64_t> unk1E0;                           // 1E0
    uint8_t isScriptMod;                                 // 1F0 - Enables blacklisted functions check
    uint8_t hasBlacklistedFunctions;                     // 1F1 - Set if any blacklisted function found
    uint8_t unk1F2[0x1F8 - 0x1F2];                       // 1F2
};
RED4EXT_ASSERT_SIZE(ScriptBundle, 0x1F8);
RED4EXT_ASSERT_OFFSET(ScriptBundle, definitionsByName, 0x08);
RED4EXT_ASSERT_OFFSET(ScriptBundle, files, 0x98);
RED4EXT_ASSERT_OFFSET(ScriptBundle, strings, 0xF8);
RED4EXT_ASSERT_OFFSET(ScriptBundle, stringIndices, 0x108);
RED4EXT_ASSERT_OFFSET(ScriptBundle, typesLock, 0x138);
RED4EXT_ASSERT_OFFSET(ScriptBundle, stringMutex, 0x140);
RED4EXT_ASSERT_OFFSET(ScriptBundle, baseBundle, 0x180);
RED4EXT_ASSERT_OFFSET(ScriptBundle, dependencies, 0x188);
RED4EXT_ASSERT_OFFSET(ScriptBundle, extraTypes, 0x198);
RED4EXT_ASSERT_OFFSET(ScriptBundle, extraProperties, 0x1D0);
RED4EXT_ASSERT_OFFSET(ScriptBundle, isScriptMod, 0x1F0);
}
