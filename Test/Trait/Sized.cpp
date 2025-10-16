#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Sized.hpp"

using Aura::Trait::Sized;

struct Dummy1{};

struct Dummy2
{
    int x;
};

struct Incomplete;

using Fn = void();

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Primitive types
    static_assert(Sized<int>, "int should be sized");
    static_assert(Sized<double>, "double should be sized");

    // User-defined complete types
    static_assert(Sized<Dummy1>, "Dummy1 should be sized");
    static_assert(Sized<Dummy2>, "Dummy2 should be sized");

    // Incomplete types
    static_assert(not Sized<Incomplete>, "Incomplete should not be sized");

    // Function types
    static_assert(not Sized<Fn>, "Function type should not be sized");

    // Arrays
    static_assert(Sized<int[3]>, "Bounded array should be sized");
    static_assert(not Sized<int[]>, "Unbounded array should not be sized");

    // cv-qualifiers
    static_assert(Sized<const int>, "const int should be sized");
    static_assert(Sized<volatile Dummy1>, "volatile Dummy1 should be sized");

    // References (always incomplete in sizeof context)
    static_assert(Sized<int&>, "int& should be sized");
    static_assert(Sized<const Dummy1&>, "const Dummy1& should be sized");

    // Pointers
    static_assert(Sized<int*>, "int* should be sized");
    static_assert(Sized<void*>, "void* should be sized");

    // void itself
    static_assert(not Sized<void>, "void should not be sized");
    
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