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

    CName name;     // 08
    uint64_t unk10; // 10
    // Game 2.5 (exe 3.0.88.46235): every script definition grew by 0x28 bytes after the name.
    // ScriptValidator::ValidateProperty (0x6BF654) reads ScriptProperty::type at +0xB8 (2.31: +0x90),
    // ScriptValidator::CompareType (0x10E5B7C) reads ScriptType::innerType +0x48 / metaType +0x54
    // (2.31: +0x20 / +0x2C); the name stays at +0x08 (Validate 0x6B9C98 `mov rdx,[r15+8]`).
    uint8_t unk18[0x28]; // 18
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
// Game 2.5: ScriptFunction's layout past the grown base is not re-derived (Codeware does not read it);
// the 2.31 size assert (0xD0) no longer holds.

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

    CClass* rttiClass;                    // 18
    ScriptClass* parent;                  // 20
    DynArray<ScriptProperty*> properties; // 28
    DynArray<ScriptProperty*> overrides;  // 38
    uint8_t unk70[0x20];                  // 2.5: 0x20 new bytes before functions
    DynArray<ScriptFunction*> functions;  // 48
    HashMap<CName, CString> attributes;   // 58
    EScriptVisibility visibility;         // 88
    Flags flags;                          // 89
};
// Game 2.5 offsets (comments above are 2.31). ScriptValidator's class check (0x6BE2DC) reads the
// parent at +0x48, properties +0x50/+0x5C, functions +0x90/+0x9C, flags byte +0xD1 (importonly 0x02,
// abstract 0x04, struct 0x10, new testonly 0x20); the definition collector 0xB2C408 walks a class's
// +0x50, +0x60 and +0x90 arrays.
static_assert(offsetof(ScriptClass, parent) == 0x48);
static_assert(offsetof(ScriptClass, properties) == 0x50);
static_assert(offsetof(ScriptClass, overrides) == 0x60);
static_assert(offsetof(ScriptClass, functions) == 0x90);
static_assert(offsetof(ScriptClass, flags) == 0xD1);
static_assert(offsetof(ScriptProperty, type) == 0xB8);
static_assert(offsetof(ScriptType, innerType) == 0x48);
static_assert(offsetof(ScriptType, metaType) == 0x54);

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

// Game 2.5 (exe 3.0.88.46235): 8 new bytes at the start, so everything up to the strings moved +8, and the
// tail grew (members up to +0x1E0). Evidence: ScriptBundle dtor 0xA7B3A4 / 0xA7B49C frees hash maps at
// +0x08/+0x38/+0x68 and arrays at +0x98..+0xE8; the definition collector 0xB2C408 walks classes at +0xD8
// (with each class's +0x50/+0x60/+0x90 arrays). 2.31 offsets were 0x00..0xF0. The tail past `strings`
// is opaque here (Codeware does not read it).
struct ScriptBundle
{
    void* unk00;                                         // 00 (2.5)
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
};
static_assert(offsetof(ScriptBundle, definitionsByName) == 0x08);
static_assert(offsetof(ScriptBundle, classes) == 0xD8);
}
