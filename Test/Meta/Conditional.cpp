#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Meta/Conditional.hpp"

using Aura::Meta::Conditional;

struct A{};

struct B{};

[[nodiscard]] auto type_dispatch(A) noexcept -> bool
{
    return true;
}

[[nodiscard]] auto type_dispatch(B) noexcept -> bool
{
    return false;
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    return type_dispatch(Conditional<true, A, B>{}) and not type_dispatch(Conditional<false, A, B>{
    });
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