#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/CopyConstructible.hpp"

using Aura::Trait::CopyConstructible;

struct foo{};

struct bar
{
    bar(bar&) = default;
};

struct baz
{
    baz(const baz&) = default;
};

struct qux
{
    qux(volatile const qux&){}
};

void meow(){}

enum class E{};

struct Incomplete;

struct Base
{
    void foo(){}
};

struct Derived : Base{};

struct AbstractBase
{
    virtual void foo() = 0;
};

struct DynamicallyDerived : AbstractBase
{
    void foo() override{}
};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    static_assert(CopyConstructible<int>);
    static_assert(CopyConstructible<int*>);
    static_assert(CopyConstructible<int&>);
    static_assert(not CopyConstructible<int&&>);

    static_assert(not CopyConstructible<void>);
    static_assert(not CopyConstructible<decltype(meow)>);
    static_assert(CopyConstructible<decltype(&Base::foo)>);
    static_assert(CopyConstructible<E>);
    static_assert(not CopyConstructible<Incomplete>);

    static_assert(CopyConstructible<foo>);
    static_assert(CopyConstructible<bar>);
    static_assert(CopyConstructible<qux>);
    static_assert(CopyConstructible<Derived>);
    static_assert(CopyConstructible<DynamicallyDerived>);

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

#ifdef aura_gcc
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR, int show)
{
    return wWinMain(instance, previous, GetCommandLineW(), show);
}
#endif
#endif