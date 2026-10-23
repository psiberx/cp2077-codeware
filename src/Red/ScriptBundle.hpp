#pragma once

#include <cstdint>
#include <RED4ext/CName.hpp>
#include <RED4ext/Containers/DynArray.hpp>
#include <RED4ext/HashMap.hpp>
#include <RED4ext/Memory/Allocators.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/Scripting/CProperty.hpp>
#include <RED4ext/Scripting/Functions.hpp>

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

struct ScriptDefinition
{
    virtual Memory::IAllocator* GetAllocator() = 0; // 00
    virtual ~ScriptDefinition() = 0;                // 08
    virtual EScriptDefinition GetType() = 0;        // 10
    virtual EScriptVisibility GetVisibility() = 0;  // 18
    virtual ScriptDefinition* GetParent() = 0;      // 20
    virtual CName GetName() = 0;                    // 28
    virtual bool IsNative() = 0;                    // 30

    CName name;        // 08
    uint64_t unk10;    // 10
    uint8_t unk18[0x28]; // 18 - Added in 2.5, shifts every derived field by 0x28
};

struct ScriptFileInfo : ScriptDefinition
{
    uint32_t crc;   // 18
    uint32_t index; // 1C
    uint32_t hash;  // 20 - Murmur3 of path
    CString path;   // 28
};

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

struct ScriptType : ScriptDefinition
{
    CBaseRTTIType* rttiType;     // 18
    ScriptDefinition* innerType; // 20
    int32_t arraySize;           // 28
    EScriptType metaType;        // 2C
};

struct ScriptProperty : ScriptDefinition
{
    struct Flags
    {
        uint16_t isNative : 1;     // 00
        uint16_t b01 : 1;          // 01
        uint16_t b02 : 1;          // 02
        uint16_t isConst : 1;      // 03
        uint16_t b04 : 1;          // 04
        uint16_t b05 : 1;          // 05
        uint16_t isPersistent : 1; // 06
        uint16_t b07 : 1;          // 07
        uint16_t b08 : 1;          // 08
    };

    CProperty* rttiProp;                // 18
    ScriptDefinition* parent;           // 20
    Flags flags;                        // 28
    Map<CString, CString> defaults;     // 30
    EScriptVisibility visibility;       // 58
    HashMap<CName, CString> attributes; // 60
    ScriptType* type;                   // 90
};

struct ScriptClass;
struct ScriptFunction;

struct ScriptParameter : ScriptDefinition
{
    struct Flags
    {
        uint8_t isOptional : 1;     // 00
        uint8_t isOut : 1;          // 01
        uint8_t isShortCircuit : 1; // 02 - Got from redscript
        uint8_t isConst : 1;        // 03
    };

    CProperty* rttiProp;      // 18
    ScriptFunction* function; // 20
    ScriptType* type;         // 28
    Flags flags;              // 30
};

struct ScriptLocalVar : ScriptDefinition
{
    CProperty* rttiProp;      // 18
    ScriptFunction* function; // 20
    ScriptType* type;         // 28
    uint8_t unk30;            // 30
};

struct ScriptFunction : ScriptDefinition
{
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

    CBaseFunction* rttiFunc;             // 18
    ScriptClass* parent;                 // 20
    CName shortName;                     // 28
    DynArray<ScriptParameter*> params;   // 30
    DynArray<ScriptLocalVar*> localVars; // 40
    HashMap<CName, CString> attributes;  // 50
    ScriptType* returnType;              // 80
    uint16_t unk88;                      // 88
    ScriptFunction* overridden;          // 90
    Flags flags;                         // 98
    CName operatorName;                  // A0
    uint8_t castValue;                   // A8
    EScriptVisibility visibility;        // A9
    DynArray<uint8_t> code;              // B0
    ScriptFileInfo* sourceFile;          // C0
    uint32_t sourceLine;                 // C8
};
RED4EXT_ASSERT_SIZE(ScriptFunction, 0xF8);

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
    uint8_t unk70[0x20];                  // 70 - Added in 2.5
    DynArray<ScriptFunction*> functions;  // 90
    HashMap<CName, CString> attributes;   // A0
    EScriptVisibility visibility;         // D0
    Flags flags;                          // D1
};
RED4EXT_ASSERT_OFFSET(ScriptClass, parent, 0x48);
RED4EXT_ASSERT_OFFSET(ScriptClass, functions, 0x90);
RED4EXT_ASSERT_OFFSET(ScriptClass, flags, 0xD1);

struct ScriptConstant : ScriptDefinition
{
    int64_t rttiValue;        // 18 - Used only for natives
    ScriptDefinition* parent; // 20 - Enum or Bitfield
    int64_t value;            // 28
    bool isNative;            // 30
};

struct ScriptEnum : ScriptDefinition
{
    CEnum* rttiEnum;                     // 18
    DynArray<ScriptConstant*> constants; // 20
    uint8_t size;                        // 30
    bool isNative;                       // 31
    EScriptVisibility visibility;        // 32
};

struct ScriptBitfield : ScriptDefinition
{
    CBitfield* rttiBitfield;             // 18
    DynArray<ScriptConstant*> constants; // 20
    uint8_t size;                        // 30
    bool isNative;                       // 31
    EScriptVisibility visibility;        // 32
};

// Patch 2.5 inserted an 8-byte field at the start and added more fields after unk108,
// only the leading part is described here (the bundle is never allocated by Codeware).
struct ScriptBundle
{
    uint64_t unk00;                                      // 00
    HashMap<CName, ScriptDefinition*> definitionsByName; // 08
    HashMap<CName, ScriptFunction*> functionsByName;     // 38
    HashMap<CName, ScriptType*> typesByName;             // 68
    DynArray<ScriptFileInfo*> files;                     // 98
    DynArray<ScriptFunction*> globals;                   // A8
    DynArray<ScriptEnum*> enums;                         // B8
    DynArray<ScriptBitfield*> bitfields;                 // C8
    DynArray<ScriptClass*> classes;                      // D8
    DynArray<ScriptType*> types;                         // E8
    DynArray<CString> strings;                           // F8
    HashMap<CName, void*> unk108;                        // 108
};
RED4EXT_ASSERT_OFFSET(ScriptBundle, definitionsByName, 0x08);
RED4EXT_ASSERT_OFFSET(ScriptBundle, classes, 0xD8);
}
