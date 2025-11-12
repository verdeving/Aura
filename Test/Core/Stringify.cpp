#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Stringify.hpp"

[[nodiscard]] auto same_literal_test(const char* str1, const char* str2) noexcept -> bool
{
    const unsigned max = static_cast<unsigned>(__builtin_strlen(str1));
    if(max not_eq __builtin_strlen(str2))
        return false;
    for(unsigned id = 0u; id < max; ++id)
        if(str1[id] not_eq str2[id])
            return false;
    return true;
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    return not same_literal_test("not the same", $stringify(, n0t the same)) and same_literal_test(
    "the same", $stringify(, the same));
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