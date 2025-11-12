#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/BitCast.hpp"

using Aura::bit_cast;

struct S1
{
    unsigned char a, b;
};

struct S2
{
    unsigned short x;
};

struct WithPadding
{
    char c;

    int i;
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Scalar roundtrip
    $unsafe
    {
        int x = 0x12345678;
        auto y = bit_cast<unsigned> $(x);
        auto z = bit_cast<int> $(y);
        if(x not_eq z)
            return false;
    }

    // Struct equivalence (endianness-sensitive)
    $unsafe
    {
        S1 s1{0x12, 0x34};
        auto s2 = bit_cast<S2> $(s1);
        if(s2.x not_eq static_cast<unsigned short>(0x3412))
            return false;
    }

    // Float-int roundtrip
    $unsafe
    {
        float f = 1.0f;
        auto i = bit_cast<unsigned> $(f);
        auto g = bit_cast<float> $(i);
        if(f not_eq g)
            return false;
    }

    // Struct with padding roundtrip
    $unsafe
    {
        WithPadding wp{'A', 42};
        auto raw = bit_cast<unsigned long long> $(wp);
        auto wp2 = bit_cast<WithPadding> $(raw);
        if (not (wp2.c == 'A' and wp2.i == 42))
            return false;
    }

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