#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/BoundedArray.hpp"

using Aura::Trait::BoundedArray;

enum class [[nodiscard]] E
{
    EA,
    EB
};

struct S
{
    int x;
};

struct Incomplete;

using F0 = int();

using F1 = int(int);

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Positive: primitive arrays
    static_assert(BoundedArray<int[1]>);
    static_assert(BoundedArray<int[3]>);
    static_assert(BoundedArray<double[5]>);
    static_assert(BoundedArray<E[2]>);

    // Positive: multi-dimensional arrays
    static_assert(BoundedArray<int[2][2]>);
    static_assert(BoundedArray<S[4][3]>);

    // Positive: cv-qualified arrays
    static_assert(BoundedArray<const int[2]>);
    static_assert(BoundedArray<volatile int[2]>);
    static_assert(BoundedArray<const volatile int[2]>);

    // Positive: arrays of user-defined types
    static_assert(BoundedArray<S[3]>);

    // Negative: not arrays
    static_assert(not BoundedArray<int>);
    static_assert(not BoundedArray<double>);
    static_assert(not BoundedArray<E>);
    static_assert(not BoundedArray<S>);
    static_assert(not BoundedArray<void>);
    static_assert(not BoundedArray<int*>);
    static_assert(not BoundedArray<int(&)[3]>);   // reference to array
    static_assert(not BoundedArray<int(*)[3]>);   // pointer to array
    static_assert(not BoundedArray<F0>);
    static_assert(not BoundedArray<F1>);

    // Negative: incomplete types
    static_assert(not BoundedArray<Incomplete>);
    static_assert(not BoundedArray<Incomplete[1]>); // incomplete element type

    // Negative: unbounded arrays (unsized)
    static_assert(not BoundedArray<int[]>);
    static_assert(not BoundedArray<S[]>);

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