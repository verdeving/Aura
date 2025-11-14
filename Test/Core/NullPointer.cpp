#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/NullPointer.hpp"

using Aura::NullPointer;

[[nodiscard]] constexpr bool is_null_pointer(int*) noexcept
{
    return false;
}

[[nodiscard]] constexpr bool is_null_pointer(NullPointer) noexcept
{
    return true;
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    int foo = 42;
    return not is_null_pointer(&foo) and is_null_pointer(nullptr);
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