#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Unicode.hpp"

using Aura::Unicode::UTF8;
using Aura::Unicode::UTF16;
using Aura::Unicode::UTF32;

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    return static_cast<unsigned char>(UTF8) == 0u and static_cast<unsigned char>(UTF16) == 1u and
    static_cast<unsigned char>(UTF32) == 2u;
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