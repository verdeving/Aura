#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/DefaultConstructible.hpp"

using Aura::Trait::DefaultConstructible;

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

    int x;
};

struct UserProvided
{
    UserProvided(){}

    int x;
};

struct Deleted
{
    Deleted() = delete;

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

    int x;
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

    DerivedNonTrivial(){}
};

struct Incomplete;

struct M
{
    int m;
};

using PM = int M::*;

struct NonTrivialElem
{
    NonTrivialElem(){}

    int x;
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Primitives, pointers, enums
    static_assert(DefaultConstructible<int>);
    static_assert(DefaultConstructible<double>);
    static_assert(DefaultConstructible<E>);
    static_assert(DefaultConstructible<int*>);
    static_assert(DefaultConstructible<void*>);
    static_assert(DefaultConstructible<int(*)()>);

    // Arrays (object types), cv-qualifications of class types
    static_assert(DefaultConstructible<int[3]>);
    static_assert(DefaultConstructible<int[2][2]>);

    static_assert(DefaultConstructible<ImplicitDefault>);
    static_assert(DefaultConstructible<const ImplicitDefault>);
    static_assert(DefaultConstructible<volatile ImplicitDefault>);
    static_assert(DefaultConstructible<const volatile ImplicitDefault>);

    // References, void, function types (should fail)
    static_assert(not DefaultConstructible<int&>);
    static_assert(not DefaultConstructible<int&&>);
    static_assert(not DefaultConstructible<void>);
    static_assert(not DefaultConstructible<F0>);
    static_assert(not DefaultConstructible<F1>);

    // Unions and aggregates
    static_assert(DefaultConstructible<UPlain>);
    static_assert(DefaultConstructible<Bitfield>);

    // Classes with various default constructors
    static_assert(DefaultConstructible<ImplicitDefault>);
    static_assert(DefaultConstructible<Defaulted>);
    static_assert(DefaultConstructible<UserProvided>);
    static_assert(not DefaultConstructible<Deleted>);
    static_assert(not DefaultConstructible<WithConstMember>);
    static_assert(not DefaultConstructible<WithReferenceMember>);

    // Abstract classes, inheritance
    static_assert(not DefaultConstructible<Abstract>);
    static_assert(DefaultConstructible<DerivedTrivial>);
    static_assert(DefaultConstructible<DerivedNonTrivial>);

    // Incomplete types (not sized => should fail)
    static_assert(not DefaultConstructible<Incomplete>);

    // Pointers to members
    static_assert(DefaultConstructible<PM>);

    // Arrays of non-trivially default-constructible types (should pass for DefaultConstructible)
    static_assert(DefaultConstructible<NonTrivialElem>);
    static_assert(DefaultConstructible<NonTrivialElem[2]>);

    // Sanity: enums/pointer arrays
    static_assert(DefaultConstructible<E[4]>);
    static_assert(DefaultConstructible<int*[2]>);
    static_assert(DefaultConstructible<void*[2]>);

    // Smoke negative: function references (ill-formed as types; guarded by Sized)
    static_assert(not DefaultConstructible<FR>);

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