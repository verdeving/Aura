#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Constant.hpp"

using Aura::Trait::Constant;

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    static_assert(not Constant<int>);
    static_assert(not Constant<volatile int>);
    static_assert(not Constant<int&>);
    static_assert(not Constant<int&&>);
    static_assert(not Constant<const int*>);
    static_assert(not Constant<const int&>);

    static_assert(Constant<const int>);
    static_assert(Constant<int* const>);
    static_assert(Constant<volatile const int>);

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