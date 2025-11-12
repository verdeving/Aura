#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyDefaultConstructible.hpp"

using Aura::Trait::TriviallyDefaultConstructible;

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
    unsigned b : 3;

    unsigned c : 5;
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
    // Test types: primitives, pointers, enums
    static_assert(TriviallyDefaultConstructible<int>);
    static_assert(TriviallyDefaultConstructible<double>);
    static_assert(TriviallyDefaultConstructible<E>);
    static_assert(TriviallyDefaultConstructible<int*>);
    static_assert(TriviallyDefaultConstructible<void*>);
    static_assert(TriviallyDefaultConstructible<int(*)()>);

    // Arrays (object types), cv-qualifications
    static_assert(TriviallyDefaultConstructible<int[3]>);
    static_assert(TriviallyDefaultConstructible<int[2][2]>);

    // References, void, function types (should fail)
    static_assert(not TriviallyDefaultConstructible<int&>);
    static_assert(not TriviallyDefaultConstructible<int&&>);
    static_assert(not TriviallyDefaultConstructible<void>);
    static_assert(not TriviallyDefaultConstructible<F0>);
    static_assert(not TriviallyDefaultConstructible<F1>);

    // Unions and aggregates
    static_assert(TriviallyDefaultConstructible<UPlain>);
    static_assert(TriviallyDefaultConstructible<Bitfield>);

    // Classes with various default constructors
    static_assert(TriviallyDefaultConstructible<ImplicitDefault>);
    static_assert(TriviallyDefaultConstructible<Defaulted>);
    static_assert(not TriviallyDefaultConstructible<UserProvided>);
    static_assert(not TriviallyDefaultConstructible<Deleted>);
    static_assert(not TriviallyDefaultConstructible<WithConstMember>);
    static_assert(not TriviallyDefaultConstructible<WithReferenceMember>);

    // cv-qualified class types remain object types; triviality unaffected by top-level cv
    static_assert(TriviallyDefaultConstructible<const ImplicitDefault>);
    static_assert(TriviallyDefaultConstructible<volatile ImplicitDefault>);
    static_assert(TriviallyDefaultConstructible<const volatile ImplicitDefault>);

    // Abstract classes, inheritance
    static_assert(not TriviallyDefaultConstructible<Abstract>);
    static_assert(TriviallyDefaultConstructible<DerivedTrivial>);
    static_assert(not TriviallyDefaultConstructible<DerivedNonTrivial>);

    // Incomplete types (not sized => should fail)
    static_assert(not TriviallyDefaultConstructible<Incomplete>);

    // Pointers to members (still trivially default constructible)
    static_assert(TriviallyDefaultConstructible<PM>);

    // Arrays of non-trivially default-constructible types (should fail)
    static_assert(not TriviallyDefaultConstructible<NonTrivialElem>);
    static_assert(not TriviallyDefaultConstructible<NonTrivialElem[2]>);

    // Sanity: pointers, enums arrays stay trivial
    static_assert(TriviallyDefaultConstructible<E[4]>);
    static_assert(TriviallyDefaultConstructible<int*[2]>);
    static_assert(TriviallyDefaultConstructible<void*[2]>);

    // Smoke negative: function references (ill-formed as types; guarded by Sized)
    static_assert(not TriviallyDefaultConstructible<FR>);

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

#ifdef aura_gcc
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR, int show)
{
    return wWinMain(instance, previous, GetCommandLineW(), show);
}
#endif
#endif