#pragma once

#include "App/World/DynamicEntityState.hpp"

namespace App
{
class DynamicEntitySystemPS : public Red::PersistentState
{
public:
    void PrepareForSaving()
    {
        Red::SortedUniqueArray<Red::CName> uniqueNames;
        size_t nameArraySize = 0;

        for (const auto& entityState : m_entityStates)
        {
            entityState->entitySpec->PrepareForSaving();

            for (const auto& tag : entityState->entitySpec->tags)
            {
                if (uniqueNames.Insert(tag).second)
                {
                    nameArraySize += strlen(tag.ToString()) + 1;
                }
            }
        }

        m_names.Resize(nameArraySize);

        auto i = 0;
        for (const auto& name : uniqueNames)
        {
            auto str = name.ToString();
            while (*str)
            {
                m_names[i++] = *(str++);
            }
            m_names[i++] = 0;
        }
    }

    void RestoreAfterLoading()
    {
        for (const auto& entityState : m_entityStates)
        {
            entityState->entitySpec->RestoreAfterLoading();
        }

        auto str = m_names.Data();
        while (str != m_names.End())
        {
            Red::CNamePool::Add(str);
            while (*(str++));
        }
    }

    void Clear()
    {
        m_entityStates.Clear();
        m_names.Clear();
    }

    void AddEntityState(const App::DynamicEntityStatePtr& aEntityState)
    {
        m_entityStates.PushBack(aEntityState);
    }

    Red::DynArray<DynamicEntityStatePtr>& GetEntityStates()
    {
        return m_entityStates;
    }

protected:
    Red::DynArray<DynamicEntityStatePtr> m_entityStates;
    Red::DynArray<char> m_names;

    RTTI_IMPL_TYPEINFO(App::DynamicEntitySystemPS);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::DynamicEntitySystemPS, {
    RTTI_PARENT(Red::PersistentState);
    RTTI_PERSISTENT(m_entityStates);
    RTTI_PERSISTENT(m_names);
});
