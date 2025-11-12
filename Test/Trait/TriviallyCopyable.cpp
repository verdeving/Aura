#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyCopyable.hpp"

using Aura::Trait::TriviallyCopyable;

// ✅ Trivial, standard layout
struct TrivialType
{
    int a;
    double b;
};

// ✅ Empty class is trivially copyable
struct Empty{};

// ❌ Non-trivial destructor
struct NonTrivialDtor
{
    ~NonTrivialDtor() {} // user-provided, so not trivial
};

// ❌ Non-trivial copy constructor
struct NonTrivialCopy
{
    NonTrivialCopy() = default;
    NonTrivialCopy(const NonTrivialCopy&) {} // user-provided
};

// ❌ Non-trivial move constructor
struct NonTrivialMove
{
    NonTrivialMove() = default;
    NonTrivialMove(NonTrivialMove&&) {} // user-provided
};

// ❌ Non-trivial copy assignment
struct NonTrivialCopyAssign
{
    NonTrivialCopyAssign& operator=(const NonTrivialCopyAssign&) { return *this; }
};

// ❌ Non-trivial move assignment
struct NonTrivialMoveAssign
{
    NonTrivialMoveAssign& operator=(NonTrivialMoveAssign&&) { return *this; }
};

// ✅ Union with only trivial members
union TrivialUnion
{
    int i;
    double d;
};

// ❌ Union with non-trivial member
union NonTrivialUnion
{
    NonTrivialDtor bad;
    int i;
};

// ✅ Array of trivially copyable type
struct ArrayHolder
{
    int arr[10];
};

// ❌ Contains non-trivial member
struct ContainsNonTrivial
{
    NonTrivialDtor bad;
};


// ❌ Has a virtual function
struct WithVirtualFunction
{
    virtual void f(); // introduces vtable → not trivially copyable
};

// ❌ Has a virtual base class
struct Base
{
    int x;
};

struct DerivedWithVirtualBase : virtual Base
{
    int y;
};

struct Incomplete;

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Positive cases
    static_assert(TriviallyCopyable<int>, "int should be trivially copyable");
    static_assert(TriviallyCopyable<double>, "double should be trivially copyable");
    static_assert(TriviallyCopyable<TrivialType>, "TrivialType should be trivially copyable");
    static_assert(TriviallyCopyable<Empty>, "Empty should be trivially copyable");
    static_assert(TriviallyCopyable<TrivialUnion>,
    "Union with only trivial members should be trivially copyable");
    static_assert(TriviallyCopyable<ArrayHolder>,
    "Struct containing only trivially copyable array should be trivially copyable");

    // Negative cases
    static_assert(not TriviallyCopyable<NonTrivialDtor>,
    "NonTrivialDtor has a user-provided destructor, not trivially copyable");
    static_assert(not TriviallyCopyable<NonTrivialCopy>,
    "NonTrivialCopy has a user-provided copy constructor, not trivially copyable");
    static_assert(not TriviallyCopyable<NonTrivialMove>,
    "NonTrivialMove has a user-provided move constructor, not trivially copyable");
    static_assert(not TriviallyCopyable<NonTrivialCopyAssign>,
    "NonTrivialCopyAssign has a user-provided copy assignment, not trivially copyable");
    static_assert(not TriviallyCopyable<NonTrivialMoveAssign>,
    "NonTrivialMoveAssign has a user-provided move assignment, not trivially copyable");
    static_assert(not TriviallyCopyable<NonTrivialUnion>,
    "Union with non-trivial member is not trivially copyable");
    static_assert(not TriviallyCopyable<ContainsNonTrivial>,
    "Struct containing a non-trivial member is not trivially copyable");
    static_assert(not TriviallyCopyable<WithVirtualFunction>,
    "Class with a virtual function is not trivially copyable");
    static_assert(not TriviallyCopyable<DerivedWithVirtualBase>,
    "Class with a virtual base is not trivially copyable");
    static_assert(not TriviallyCopyable<int[]>,
    "Arrays of unknown bound are not trivially copyable");
    static_assert(not TriviallyCopyable<void>, "void is not trivially copyable");
    static_assert(not TriviallyCopyable<Incomplete>,
    "Incomplete classes are not trivially copyable");

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