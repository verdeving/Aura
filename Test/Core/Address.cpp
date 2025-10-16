#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Same.hpp"
#include "Core/Address.hpp"

using Aura::Trait::Same;
using Aura::address;

struct foo
{
    int x;

    const int* operator bitand() const&
    {
        return &x;
    }
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    constexpr foo f{3};
    return not Same<decltype(address(f)), decltype(bitand f)>;
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