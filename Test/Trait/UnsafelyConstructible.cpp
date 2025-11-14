#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/UnsafelyConstructible.hpp"

using Aura::Trait::UnsafelyConstructible;

struct SimpleConstructor
{
    SimpleConstructor $unreliable(){}
};

struct ConstructorWithParams
{
    ConstructorWithParams $unreliable(int){}
};

struct VirtualSimpleConstructor : virtual SimpleConstructor
{
    VirtualSimpleConstructor $unreliable() : SimpleConstructor $(){}
};

struct VirtualConstructorWithParams : virtual ConstructorWithParams
{
    VirtualConstructorWithParams $unreliable(int x) : ConstructorWithParams $(x){}
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    static_assert(UnsafelyConstructible<SimpleConstructor>);
    static_assert(UnsafelyConstructible<ConstructorWithParams, int>);
    static_assert(UnsafelyConstructible<VirtualSimpleConstructor>);
    static_assert(UnsafelyConstructible<VirtualConstructorWithParams, int>);

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