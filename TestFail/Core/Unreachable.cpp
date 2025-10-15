#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Unreachable.hpp"

using Aura::unreachable;

[[nodiscard]] auto failure_test(int x) noexcept -> bool
{
    switch(x)
    {
        default:
            return true;
        // x can't be 4 for whatever reason
        case 4:
            unreachable();
    }
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    return failure_test(4);
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