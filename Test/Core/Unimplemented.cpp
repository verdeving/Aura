#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Unimplemented.hpp"

[[nodiscard]] auto meow() noexcept -> bool $unimplemented;

[[nodiscard]] auto meow(int) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    return
    meow(42)    // ok
    // and meow(): error -> "not implemented"
    ;
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