#pragma once

#define X_RTTI_STR1(x) #x
#define X_RTTI_STR2(x) X_RTTI_STR1(x)
#define X_RTTI_LOCATION __FILE__ " : " X_RTTI_STR2(__LINE__)

#define X_RTTI_NAMEOF(...) []() constexpr noexcept { \
  constexpr auto _name = ::nameof::detail::pretty_name(#__VA_ARGS__); \
  return ::nameof::cstring<_name.size()>{_name}; }()

#define X_RTTI_EXPAND(X) X
#define X_RTTI_OVERLOAD(_1, _2, _3, N, ...) N

#define RTTI_IMPL_TYPEINFO(_class) \
    Red::CClass* GetNativeType() \
    { \
        return Red::GetClass<_class>(); \
    }

#define RTTI_IMPL_ALLOCATOR(_allocator) \
public: \
    using AllocatorType = _allocator; \
    static_assert(Red::Detail::IsAllocator<_allocator>, #_allocator " is not a valid allocator type"); \
    Red::Memory::IAllocator* GetAllocator() \
    { \
        return AllocatorType::Get(); \
    }

#define RTTI_DECLARE_FRIENDS(_class) \
    friend class Red::RTTIBuilder<Red::Scope::For<_class>()>; \
    friend class Red::ClassDescriptor<_class>;

#define RTTI_DEFINE_CLASS(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_DEF_CLASS_3, X_RTTI_DEF_CLASS_2, X_RTTI_DEF_CLASS_1)(__VA_ARGS__))

#define X_RTTI_DEF_CLASS_1(_class) \
    template<> \
    struct Red::RTTIBuilder<Red::ClassDefinition<_class>{}> \
    { \
        using Type = _class; \
        using Descriptor = Red::ClassDescriptor<_class>; \
        static constexpr auto Name() \
        { \
            return nameof::nameof_short_type<Type>(); \
        } \
    };

#define X_RTTI_DEF_CLASS_2(_class, _desc) \
    template<> \
    struct Red::RTTIBuilder<Red::ClassDefinition<_class>{}> \
    { \
        using Type = _class; \
        using Descriptor = Red::ClassDescriptor<_class>; \
        static constexpr auto Name() \
        { \
            return nameof::nameof_short_type<Type>(); \
        } \
        static void Describe(Descriptor* type) \
        { \
            _desc; \
        } \
    };

#define X_RTTI_DEF_CLASS_3(_class, _name, _desc) \
    template<> \
    struct Red::RTTIBuilder<Red::ClassDefinition<_class>{}> \
    { \
        using Type = _class; \
        using Descriptor = Red::ClassDescriptor<_class>; \
        static constexpr auto Name() \
        { \
            return _name; \
        } \
        static void Describe(Descriptor* type) \
        { \
            _desc; \
        } \
    };

#define RTTI_EXPAND_CLASS(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_EXT_CLASS_3, X_RTTI_EXT_CLASS_2, X_RTTI_EXT_CLASS_1)(__VA_ARGS__))

#define X_RTTI_EXT_CLASS_2(_class, _desc) \
    template<> \
    struct Red::RTTIBuilder<Red::ClassExpansion<_class, X_RTTI_LOCATION>{}> \
    { \
        using Type = _class; \
        using Descriptor = Red::ClassDescriptor<_class>; \
        static void Describe(Descriptor* type) \
        { \
            _desc; \
        } \
    };

#define X_RTTI_EXT_CLASS_3(_class, _expansion, _desc) \
    template<> \
    struct Red::RTTIBuilder<Red::ClassExpansion<_class, X_RTTI_LOCATION>{}> \
    { \
        using Type = _expansion; \
        using Descriptor = Red::ClassDescriptor<_class>; \
        static void Describe(Descriptor* type) \
        { \
            _desc; \
        } \
    };

#define RTTI_ABSTRACT() \
    type->MarkAbstract()

#define RTTI_PARENT(_parent) \
    type->SetParent<_parent>()

#define RTTI_ALIAS(_alias) \
    type->SetAlias(_alias)

#define RTTI_METHOD(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_METHOD_3, X_RTTI_METHOD_2, X_RTTI_METHOD_1)(__VA_ARGS__))

#define X_RTTI_METHOD_1(_method) \
    type->AddFunction<&Type::_method>(#_method)

#define X_RTTI_METHOD_2(_method, _name) \
    type->AddFunction<&Type::_method>(_name)

#define RTTI_METHOD_FQN(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_METHOD_FQN_3, X_RTTI_METHOD_FQN_2, X_RTTI_METHOD_FQN_1)(__VA_ARGS__))

#define X_RTTI_METHOD_FQN_1(_method) \
    type->AddFunction<&_method>(X_RTTI_NAMEOF(_method).data())

#define X_RTTI_METHOD_FQN_2(_method, _name) \
    type->AddFunction<&_method>(_name)

#define RTTI_CALLBACK(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_CALLBACK_3, X_RTTI_CALLBACK_2, X_RTTI_CALLBACK_1)(__VA_ARGS__))

#define X_RTTI_CALLBACK_1(_method) \
    type->AddFunction<&Type::_method>(#_method, {.isEvent = true})

#define X_RTTI_CALLBACK_2(_method, _name) \
    type->AddFunction<&Type::_method>(_name, {.isEvent = true})

#define RTTI_CALLBACK_FQN(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_CALLBACK_FQN_3, X_RTTI_CALLBACK_FQN_2, X_RTTI_CALLBACK_FQN_1)(__VA_ARGS__))

#define X_RTTI_CALLBACK_FQN_1(_method) \
    type->AddFunction<&_method>(X_RTTI_NAMEOF(_method), {.isEvent = true})

#define X_RTTI_CALLBACK_FQN_2(_method, _name) \
    type->AddFunction<&_method>(_name, {.isEvent = true})

#define RTTI_PROPERTY(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_PROPERTY_3, X_RTTI_PROPERTY_2, X_RTTI_PROPERTY_1)(__VA_ARGS__))

#define X_RTTI_PROPERTY_1(_property) \
    type->AddProperty<&Type::_property>(#_property)

#define X_RTTI_PROPERTY_2(_property, _name) \
    type->AddProperty<&Type::_property>(_name)

#define RTTI_PROPERTY_FQN(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_PROPERTY_FQN_3, X_RTTI_PROPERTY_FQN_2, X_RTTI_PROPERTY_FQN_1)(__VA_ARGS__))

#define X_RTTI_PROPERTY_FQN_1(_property) \
    type->AddProperty<&_property>(X_RTTI_NAMEOF(_property))

#define X_RTTI_PROPERTY_FQN_2(_property, _name) \
    type->AddProperty<&_property>(_name)

#define RTTI_PERSISTENT(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_PERSISTENT_3, X_RTTI_PERSISTENT_2, X_RTTI_PERSISTENT_1)(__VA_ARGS__))

#define X_RTTI_PERSISTENT_1(_property) \
    type->AddProperty<&Type::_property>(#_property, {.isPersistent = true})

#define X_RTTI_PERSISTENT_2(_property, _name) \
    type->AddProperty<&Type::_property>(_name, {.isPersistent = true})

#define RTTI_PERSISTENT_FQN(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_PERSISTENT_FQN_3, X_RTTI_PERSISTENT_FQN_2, X_RTTI_PERSISTENT_FQN_1)(__VA_ARGS__))

#define X_RTTI_PERSISTENT_FQN_1(_property) \
    type->AddProperty<&_property>(X_RTTI_NAMEOF(_property), {.isPersistent = true})

#define X_RTTI_PERSISTENT_FQN_2(_property, _name) \
    type->AddProperty<&_property>(_name, {.isPersistent = true})

#define RTTI_DEFINE_ENUM(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_DEF_ENUM_3, X_RTTI_DEF_ENUM_2, X_RTTI_DEF_ENUM_1)(__VA_ARGS__))

#define X_RTTI_DEF_ENUM_1(_enum) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumDefinition<_enum>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static constexpr auto Name() \
        { \
            return nameof::nameof_short_type<Type>(); \
        } \
    };

#define X_RTTI_DEF_ENUM_2(_enum, _name) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumDefinition<_enum>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static constexpr auto Name() \
        { \
            return _name; \
        } \
    };

#define RTTI_DEFINE_FLAGS(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_DEF_FLAGS_3, X_RTTI_DEF_FLAGS_2, X_RTTI_DEF_FLAGS_1)(__VA_ARGS__))

#define X_RTTI_DEF_FLAGS_1(_enum) \
    template<> \
    struct Red::RTTIBuilder<Red::FlagsDefinition<_enum>{}>  \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static constexpr auto Name() \
        { \
            return nameof::nameof_short_type<Type>(); \
        } \
    };

#define X_RTTI_DEF_FLAGS_2(_enum, _name) \
    template<> \
    struct Red::RTTIBuilder<Red::FlagsDefinition<_enum>{}>  \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static constexpr auto Name() \
        { \
            return _name; \
        } \
    };

#define RTTI_EXPAND_ENUM(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_EXP_ENUM_3, X_RTTI_EXP_ENUM_2, X_RTTI_EXP_ENUM_1)(__VA_ARGS__))

#define X_RTTI_EXP_ENUM_1(_enum) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumExpansion<_enum, X_RTTI_LOCATION>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static void Describe(Descriptor* type) \
        { \
            type->template AddOptions<_enum>(); \
        } \
    };

#define X_RTTI_EXP_ENUM_2(_enum, _expansion) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumExpansion<_enum, X_RTTI_LOCATION>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static void Describe(Descriptor* type) \
        { \
            type->template AddOptions<_expansion>(); \
        } \
    };

#define RTTI_EXPAND_FLAGS(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_EXP_FLAGS_3, X_RTTI_EXP_FLAGS_2, X_RTTI_EXP_FLAGS_1)(__VA_ARGS__))

#define X_RTTI_EXP_FLAGS_1(_enum) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumExpansion<_enum, X_RTTI_LOCATION>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static void Describe(Descriptor* type) \
        { \
            type->template AddFlags<_enum>(); \
        } \
    };

#define X_RTTI_EXP_FLAGS_2(_enum, _expansion) \
    template<> \
    struct Red::RTTIBuilder<Red::EnumExpansion<_enum, X_RTTI_LOCATION>{}> \
    { \
        using Type = _enum; \
        using Descriptor = Red::EnumDescriptor<_enum>; \
        static void Describe(Descriptor* type) \
        { \
            type->template AddFlags<_expansion>(); \
        } \
    };

#define RTTI_OPTION() \
    static_assert(false, "Not Implemented")

#define RTTI_DEFINE_GLOBALS(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_DEF_GLOB_3, X_RTTI_DEF_GLOB_2, X_RTTI_DEF_GLOB_1)(__VA_ARGS__))

#define X_RTTI_DEF_GLOB_1(_desc) \
    template<> \
    struct Red::RTTIBuilder<Red::GlobalDefinition<X_RTTI_LOCATION>{}> \
    { \
        using Descriptor = Red::GlobalDescriptor; \
        static void Describe(Descriptor* rtti) \
        { \
            _desc; \
        } \
    };

#define X_RTTI_DEF_GLOB_2(_namespace, _desc) \
    template<> \
    struct Red::RTTIBuilder<<Red::GlobalDefinition<X_RTTI_LOCATION>{}> \
    { \
        using Descriptor = Red::GlobalDescriptor; \
        static void Describe(Descriptor* rtti) \
        { \
            using namespace _namespace; \
            _desc; \
        } \
    };

#define RTTI_FUNCTION(...) \
    X_RTTI_EXPAND(X_RTTI_OVERLOAD(__VA_ARGS__, X_RTTI_FUNCTION_3, X_RTTI_FUNCTION_2, X_RTTI_FUNCTION_1)(__VA_ARGS__))

#define X_RTTI_FUNCTION_1(_func) \
    rtti->AddFunction<&_func>(X_RTTI_NAMEOF(_func).data())

#define X_RTTI_FUNCTION_2(_func, _name) \
    rtti->AddFunction<&_func>(_name)

#define RTTI_OP() \
    static_assert(false, "Not Implemented")

#define RTTI_CAST() \
    static_assert(false, "Not Implemented")

#define RTTI_REGISTER(_handler) \
    template<> \
    struct Red::RTTIBuilder<<Red::GlobalDefinition<X_RTTI_LOCATION>{}> \
    { \
        using Descriptor = Red::GlobalDescriptor; \
        static void Register(Descriptor* rtti) \
        { \
            _handler; \
        } \
    };

#define RTTI_DESCRIBE(_handler) \
    template<> \
    struct Red::RTTIBuilder<<Red::GlobalDefinition<X_RTTI_LOCATION>{}> \
    { \
        using Descriptor = Red::GlobalDescriptor; \
        static void Describe(Descriptor* rtti) \
        { \
            _handler; \
        } \
    };
