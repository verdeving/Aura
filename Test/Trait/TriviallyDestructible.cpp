#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyDestructible.hpp"

using Aura::Trait::TriviallyDestructible;

enum class [[nodiscard]] E
{
    EA,
    EB
};

using F0 = int();

using F1 = int(int);

using FR = int(&)();

union UPlain
{
    int x;

    double y;
};

struct Bitfield
{
    unsigned b : 3, c : 5;
};

struct ImplicitDefault
{
    int x;
};

struct Defaulted
{
    Defaulted() = default;

    ~Defaulted() = default;

    int x;
};

struct UserProvided
{
    ~UserProvided(){} // non-trivial destructor

    int x;
};

struct Deleted
{
    ~Deleted() = delete;

    int x;
};

struct WithConstMember
{
    const int x;
};

struct WithReferenceMember
{
    int& r;
};

struct Abstract
{
    virtual void foo() = 0;
};

struct Base
{
    int b;
};

struct DerivedTrivial : Base
{
    int d;
};

struct DerivedNonTrivial : Base
{
    int d;

    ~DerivedNonTrivial(){} // non-trivial
};

struct VirtualDtor
{
    virtual ~VirtualDtor(){}

    int x;
};

struct Incomplete;

struct M
{
    int m;
};

using PM = int M::*;

struct NonTrivialElem
{
    ~NonTrivialElem(){} // non-trivial

    int x;
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Primitives, pointers, enums
    static_assert(TriviallyDestructible<int>);
    static_assert(TriviallyDestructible<double>);
    static_assert(TriviallyDestructible<E>);
    static_assert(TriviallyDestructible<int*>);
    static_assert(TriviallyDestructible<void*>);
    static_assert(TriviallyDestructible<int(*)()>);

    // Arrays (object types), cv-qualifications
    static_assert(TriviallyDestructible<int[3]>);
    static_assert(TriviallyDestructible<int[2][2]>);

    // References: IMHO, and even if this goes against the standard, references should be trivially
    // destructible, because you're not supposed to explicitly call the destructor anyways, so this
    // is fine, you should never encounter something like:
    //
    // if constexpr(Reference<T> and TriviallyDestructible<T>)
    //     ref.~T();
    static_assert(TriviallyDestructible<int&>);
    static_assert(TriviallyDestructible<int&&>);

    // void, function types (should fail)
    static_assert(not TriviallyDestructible<void>);
    static_assert(not TriviallyDestructible<F0>);
    static_assert(not TriviallyDestructible<F1>);

    // Unions and aggregates
    static_assert(TriviallyDestructible<UPlain>);
    static_assert(TriviallyDestructible<Bitfield>);

    // Classes with various destructors
    static_assert(TriviallyDestructible<ImplicitDefault>);
    static_assert(TriviallyDestructible<Defaulted>);
    static_assert(not TriviallyDestructible<UserProvided>);
    static_assert(not TriviallyDestructible<Deleted>);
    static_assert(TriviallyDestructible<WithConstMember>);
    static_assert(TriviallyDestructible<WithReferenceMember>);

    // cv-qualified class types remain object types; triviality unaffected by top-level cv
    static_assert(TriviallyDestructible<const ImplicitDefault>);
    static_assert(TriviallyDestructible<volatile ImplicitDefault>);
    static_assert(TriviallyDestructible<const volatile ImplicitDefault>);

    // Abstract classes, inheritance
    static_assert(TriviallyDestructible<Abstract>);
    static_assert(TriviallyDestructible<DerivedTrivial>);
    static_assert(not TriviallyDestructible<DerivedNonTrivial>);
    static_assert(not TriviallyDestructible<VirtualDtor>);

    // Incomplete types (not sized => should fail)
    static_assert(not TriviallyDestructible<Incomplete>);

    // Pointers to members
    static_assert(TriviallyDestructible<PM>);

    // Arrays of non-trivially destructible types (should fail)
    static_assert(not TriviallyDestructible<NonTrivialElem>);
    static_assert(not TriviallyDestructible<NonTrivialElem[2]>);

    // Sanity: enums/pointer arrays
    static_assert(TriviallyDestructible<E[4]>);
    static_assert(TriviallyDestructible<int*[2]>);
    static_assert(TriviallyDestructible<void*[2]>);

    // Smoke negative: function references
    static_assert(not TriviallyDestructible<FR>);

    return true;
}

#ifdef aura_windows
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
    return not aura_testing();
}

#endif