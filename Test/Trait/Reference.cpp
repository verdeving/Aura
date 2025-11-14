#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Reference.hpp"

using Aura::Trait::Reference;

enum class [[nodiscard]] E
{
    EA,
    EB
};

using F0 = int();

using F1 = int(int);

using FR = int(&)();

struct S
{
    int x;
};

struct Incomplete;

using PM = int S::*;

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Positive: plain references
    static_assert(Reference<int&>);
    static_assert(Reference<int&&>);
    static_assert(Reference<double&>);
    static_assert(Reference<E&>);
    static_assert(Reference<S&>);
    static_assert(Reference<S&&>);

    // Positive: cv-qualified references
    static_assert(Reference<const int&>);
    static_assert(Reference<volatile int&>);
    static_assert(Reference<const volatile int&>);
    static_assert(Reference<const S&&>);
    static_assert(Reference<volatile S&&>);

    // Negative: non-reference types
    static_assert(not Reference<int>);
    static_assert(not Reference<double>);
    static_assert(not Reference<E>);
    static_assert(not Reference<S>);
    static_assert(not Reference<void>);
    static_assert(not Reference<int*>);
    static_assert(not Reference<int(*)()>);
    static_assert(not Reference<int[3]>);
    static_assert(not Reference<int[2][2]>);

    // Negative: incomplete types (not references)
    static_assert(not Reference<Incomplete>);

    // Function types (not references)
    static_assert(not Reference<F0>);
    static_assert(not Reference<F1>);

    // Function references (should succeed, since they are references)
    static_assert(Reference<FR>);

    // Member pointers (not references)
    static_assert(not Reference<PM>);

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

#if defined(aura_gcc) and defined(aura_windows)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR, int show)
{
    return wWinMain(instance, previous, GetCommandLineW(), show);
}
#endif
#endif