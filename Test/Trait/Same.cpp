#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"

using Aura::Trait::Same;

// Dummy types for testing
struct Dummy1{};

struct Dummy2{};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Identical primitive types
    static_assert(Same<int, int>, "int, int should be same");
    static_assert(not Same<int, unsigned int>, "int, unsigned int should differ");

    // Identical user-defined types
    static_assert(Same<Dummy1, Dummy1>, "Dummy1, Dummy1 should be same");
    static_assert(not Same<Dummy1, Dummy2>, "Dummy1, Dummy2 should differ");

    // cv-qualifiers matter
    static_assert(not Same<int, const int>, "int, const int should differ");
    static_assert(Same<const Dummy1, const Dummy1>, "const Dummy1, const Dummy1 should be same");

    // Reference qualifiers matter
    static_assert(not Same<int, int&>, "int, int& should differ");
    static_assert(not Same<int&, int&&>, "int&, int&& should differ");
    static_assert(Same<int&, int&>, "int&, int& should be same");

    // Mixed cvref combinations
    static_assert(not Same<const int&, const int>, "const int&, const int should differ");
    static_assert(Same<const int&, const int&>, "const int&, const int& should be same");

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