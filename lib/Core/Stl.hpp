#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <TiltedCore/StlAllocator.hpp>
#include <tsl/hopscotch_map.h>
#include <tsl/hopscotch_set.h>
#else
#include <initializer_list>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#endif

namespace Core
{
// Pretty much the same as TiltedCore with StlAllocator,
// but unique ptr allows implicit casting to the base.

namespace Detail
{
template<class T>
struct UniqueDeleter
{
    constexpr UniqueDeleter() noexcept = default;

    template<class U>
    requires std::is_base_of_v<T, U>
    UniqueDeleter(const UniqueDeleter<U>& d) noexcept {}

    void operator()(std::conditional_t<std::is_array_v<T>, T, T*> aData)
    {
#if defined(_WIN32) || defined(_WIN64)
        TiltedPhoques::Delete<T>(aData);
#else
        delete aData;
#endif
    }
};
}

#if defined(_WIN32) || defined(_WIN64)
template<class T>
using Vector = std::vector<T, TiltedPhoques::StlAllocator<T>>;

template<class T>
using Set = tsl::hopscotch_set<T, std::hash<T>, std::equal_to<T>, TiltedPhoques::StlAllocator<T>>;

template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
using SortedSet = std::set<T, Compare, Allocator>;

template<class T, class U>
using Map = tsl::hopscotch_map<T, U, std::hash<T>, std::equal_to<T>, TiltedPhoques::StlAllocator<std::pair<T, U>>>;

template<class T, class U>
using SortedMap = std::map<T, U, std::less<T>, TiltedPhoques::StlAllocator<std::pair<const T, U>>>;

#else
// macOS: standard containers. Map keeps the hopscotch call shape (iterator key() and value()) so the shared sources
// compile unchanged.
template<class T>
using Vector = std::vector<T>;

template<class T>
using Set = std::unordered_set<T>;

template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
using SortedSet = std::set<T, Compare, Allocator>;

template<class T, class U>
using SortedMap = std::map<T, U>;

template<class K, class V>
class Map
{
public:
    using Base = std::unordered_map<K, V>;

    template<class It>
    struct Iter
    {
        It it;

        auto& key() const { return it->first; }
        auto& value() const { return it->second; }
        auto& operator*() const { return *it; }
        auto* operator->() const { return std::addressof(*it); }
        Iter& operator++() { ++it; return *this; }
        bool operator==(const Iter& aOther) const { return it == aOther.it; }
        bool operator!=(const Iter& aOther) const { return it != aOther.it; }
    };

    using iterator = Iter<typename Base::iterator>;
    using const_iterator = Iter<typename Base::const_iterator>;

    Map() = default;
    Map(std::initializer_list<typename Base::value_type> aList) : m(aList) {}

    iterator begin() { return {m.begin()}; }
    iterator end() { return {m.end()}; }
    const_iterator begin() const { return {m.begin()}; }
    const_iterator end() const { return {m.end()}; }

    iterator find(const K& aKey) { return {m.find(aKey)}; }
    const_iterator find(const K& aKey) const { return {m.find(aKey)}; }

    V& operator[](const K& aKey) { return m[aKey]; }

    template<class... A>
    auto emplace(A&&... aArgs) { return m.emplace(std::forward<A>(aArgs)...); }

    std::pair<iterator, bool> insert(const typename Base::value_type& aValue)
    {
        auto result = m.insert(aValue);
        return {{result.first}, result.second};
    }

    auto insert_or_assign(const K& aKey, const V& aValue) { return m.insert_or_assign(aKey, aValue); }
    auto insert_or_assign(const K& aKey, V&& aValue) { return m.insert_or_assign(aKey, std::move(aValue)); }

    bool contains(const K& aKey) const { return m.contains(aKey); }
    bool empty() const { return m.empty(); }
    std::size_t size() const { return m.size(); }
    auto erase(const K& aKey) { return m.erase(aKey); }
    iterator erase(iterator aIt) { return {m.erase(aIt.it)}; }
    iterator erase(const_iterator aIt) { return {m.erase(aIt.it)}; }
    void clear() { m.clear(); }
    void reserve(std::size_t aCount) { m.reserve(aCount); }

private:
    Base m;
};
#endif

// TODO: OrderedMap

template<class T>
using SharedPtr = std::shared_ptr<T>;

template<class T>
using WeakPtr = std::weak_ptr<T>;

template<class T>
using UniquePtr = std::unique_ptr<T, Detail::UniqueDeleter<T>>;

template<typename T>
struct ShareFromThis : public std::enable_shared_from_this<T>
{
    SharedPtr<T> ToShared()
    {
        return std::enable_shared_from_this<T>::shared_from_this();
    }

    WeakPtr<T> ToWeak()
    {
        return std::enable_shared_from_this<T>::weak_from_this();
    }
};

template<typename T, typename... Args>
auto MakeShared(Args&&... aArgs)
{
#if defined(_WIN32) || defined(_WIN64)
    return std::allocate_shared<T>(TiltedPhoques::StlAllocator<T>(), std::forward<Args>(aArgs)...);
#else
    return std::make_shared<T>(std::forward<Args>(aArgs)...);
#endif
}

template<typename T, typename... Args>
auto MakeUnique(Args&&... aArgs)
{
#if defined(_WIN32) || defined(_WIN64)
    return UniquePtr<T>(TiltedPhoques::New<T>(std::forward<Args>(aArgs)...));
#else
    return UniquePtr<T>(new T(std::forward<Args>(aArgs)...));
#endif
}
}
