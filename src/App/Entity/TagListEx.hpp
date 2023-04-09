#pragma once

RTTI_EXPAND_CLASS(Red::TagList, {
    RTTI_ALIAS("TagList");
    RTTI_METHOD(IsEmpty);
    RTTI_METHOD(HasTag);
    RTTI_METHOD(AddTag);
    RTTI_METHOD(RemoveTag);
    RTTI_METHOD(Clear);
});
