#pragma once

RTTI_EXPAND_CLASS(Red::TagList, {
    RTTI_ALIAS("TagList");

    RTTI_METHOD(IsEmpty);
    RTTI_METHOD(Clear);

    RTTI_METHOD(Contains, bool(T::*)(CName) const, "HasTag");
    RTTI_METHOD(Add, void(T::*)(CName), "AddTag");
    RTTI_METHOD(Remove, void(T::*)(CName), "RemoveTag");

    RTTI_METHOD(Contains, bool(T::*)(const DynArray<CName>&) const, "HasTags");
    RTTI_METHOD(Add, void(T::*)(const DynArray<CName>&), "AddTags");
    RTTI_METHOD(Remove, void(T::*)(const DynArray<CName>&), "RemoveTags");
});
