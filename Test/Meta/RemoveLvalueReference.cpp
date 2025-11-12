#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Meta/RemoveLvalueReference.hpp"

using Aura::Trait::Same;
using Aura::Meta::RemoveLvalueReference;

// Dummy types for testing
struct Dummy{};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Non-reference types remain unchanged
    static_assert(Same<RemoveLvalueReference<int>, int>, "int failed");
    static_assert(Same<RemoveLvalueReference<Dummy>, Dummy>, "Dummy failed");

    // L-value references are stripped
    static_assert(Same<RemoveLvalueReference<int&>, int>, "int& failed");
    static_assert(Same<RemoveLvalueReference<Dummy&>, Dummy>, "Dummy& failed");

    // R-value references remain unchanged
    static_assert(Same<RemoveLvalueReference<int&&>, int&&>, "int&& failed");
    static_assert(Same<RemoveLvalueReference<Dummy&&>, Dummy&&>, "Dummy&& failed");

    // Const and volatile qualifiers are preserved
    static_assert(Same<RemoveLvalueReference<const int&>, const int>, "const int& failed");
    static_assert(Same<RemoveLvalueReference<volatile Dummy&&>, volatile Dummy&&>,
    "volatile Dummy&& failed");

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