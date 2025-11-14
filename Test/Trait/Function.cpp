#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Function.hpp"

using Aura::Trait::Function;

template<class> struct PM_traits{};

template<class T, class U> struct PM_traits<U T::*>
{
    using member_type = U;
};

struct A
{
    static int foo();
    
    int fun() const&;
};

using T = PM_traits<decltype(&A::fun)>::member_type;

int f();

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    static_assert(Function<decltype(f)>);
    static_assert(Function<int(int)>);
    
    
    static_assert(not Function<int>);
    static_assert(not Function<decltype([]{})>);

    static_assert(not Function<A>);
    static_assert(Function<decltype(A::foo)>);
    static_assert(not Function<decltype(&A::fun)>);

    static_assert(Function<T>);

    return true;
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