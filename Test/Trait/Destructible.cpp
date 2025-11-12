#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Destructible.hpp"

using Aura::Trait::Destructible;

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
    static_assert(Destructible<int>);
    static_assert(Destructible<double>);
    static_assert(Destructible<E>);
    static_assert(Destructible<int*>);
    static_assert(Destructible<void*>);
    static_assert(Destructible<int(*)()>);

    // Arrays (object types), cv-qualifications
    static_assert(Destructible<int[3]>);
    static_assert(Destructible<int[2][2]>);

    // References
    static_assert(Destructible<int&>);
    static_assert(Destructible<int&&>);

    // void, function types (should fail)
    static_assert(not Destructible<void>);
    static_assert(not Destructible<F0>);
    static_assert(not Destructible<F1>);

    // Unions and aggregates
    static_assert(Destructible<UPlain>);
    static_assert(Destructible<Bitfield>);

    // Classes with various destructors
    static_assert(Destructible<ImplicitDefault>);
    static_assert(Destructible<Defaulted>);
    static_assert(Destructible<UserProvided>);
    static_assert(not Destructible<Deleted>);
    static_assert(Destructible<WithConstMember>);
    static_assert(Destructible<WithReferenceMember>);

    // cv-qualified class types remain object types; triviality unaffected by top-level cv
    static_assert(Destructible<const ImplicitDefault>);
    static_assert(Destructible<volatile ImplicitDefault>);
    static_assert(Destructible<const volatile ImplicitDefault>);

    // Abstract classes, inheritance
    static_assert(Destructible<Abstract>);
    static_assert(Destructible<DerivedTrivial>);
    static_assert(Destructible<DerivedNonTrivial>);
    static_assert(Destructible<VirtualDtor>);

    // Incomplete types (not sized => should fail)
    static_assert(not Destructible<Incomplete>);

    // Pointers to members
    static_assert(Destructible<PM>);

    // Arrays of non-trivially destructible types
    static_assert(Destructible<NonTrivialElem>);
    static_assert(Destructible<NonTrivialElem[2]>);

    // Sanity: enums/pointer arrays
    static_assert(Destructible<E[4]>);
    static_assert(Destructible<int*[2]>);
    static_assert(Destructible<void*[2]>);

    // Smoke negative: function references
    static_assert(not Destructible<FR>);

    return true;
}

#ifdef aura_windows
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#else
int main()
#endif
{
    return not aura_testing();
}

#endif