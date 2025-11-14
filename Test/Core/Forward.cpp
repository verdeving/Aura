#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Forward.hpp"

[[nodiscard]] auto process(int&) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto process(int&&) noexcept -> bool
{
    return true;
}

template<class T> [[nodiscard]] auto wrapper(T&& t) noexcept -> bool
{
    return process($forward(t));
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    int meow = 42;
    return not wrapper(meow) and wrapper(42);
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