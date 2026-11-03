#pragma once

#include "TypeInfo/Resolving.hpp"

template<>
struct std::hash<RED4ext::CName>
{
    std::size_t operator()(RED4ext::CName aKey) const
    {
        return aKey.hash;
    }
};

template<>
struct std::hash<RED4ext::TweakDBID>
{
    std::size_t operator()(RED4ext::TweakDBID aKey) const
    {
#if defined(__APPLE__)
        // R28 (the same fix ArchiveXL got in R26). operator== compares the name hash and the length only; the top 24 bits of the value hold the TweakDB
        // offset of a flat. Equal ids must hash equally, or a flat stored with its value offset is not found by its plain id: an override in a batch and
        // the flat inherited from a base record then both end up in the batch and one of them wins by chance. Found by the autotest harness: the
        // yaml flats of Lizzie's BDs (Character.LizziesBDs_Performer_Base.displayName, q50_main_LizziesBDs.fullDisplayName, ...) read back wrong.
        return static_cast<std::size_t>(aKey.value & 0xFFFFFFFFFFull);
#else
        return aKey.value;
#endif
    }
};

template<>
struct std::hash<RED4ext::ResourcePath>
{
    std::size_t operator()(RED4ext::ResourcePath aKey) const
    {
        return aKey.hash;
    }
};

template<>
struct std::hash<RED4ext::NodeRef>
{
    std::size_t operator()(RED4ext::NodeRef aKey) const
    {
        return aKey.hash;
    }
};

template<typename T>
requires std::is_class_v<T> && std::is_convertible_v<T, uint64_t> && Red::Detail::HasGeneratedTypeName<T>
struct std::hash<T>
{
    std::size_t operator()(T aKey) const
    {
        return static_cast<uint64_t>(aKey);
    }
};
