#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyMoveConstructible.hpp"

using Aura::Trait::TriviallyMoveConstructible;

struct foo{};

struct bar
{
    bar(bar&&) = default;
};

struct baz
{
    baz(const baz&) = default;
};

struct qux
{
    qux(volatile qux&&){}
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
    static_assert(TriviallyMoveConstructible<int>);
    static_assert(TriviallyMoveConstructible<int*>);
    static_assert(TriviallyMoveConstructible<int&>);
    static_assert(TriviallyMoveConstructible<int&&>);

    static_assert(not TriviallyMoveConstructible<void>);
    static_assert(not TriviallyMoveConstructible<decltype(meow)>);
    static_assert(TriviallyMoveConstructible<decltype(&Base::foo)>);
    static_assert(TriviallyMoveConstructible<E>);
    static_assert(not TriviallyMoveConstructible<Incomplete>);

    static_assert(TriviallyMoveConstructible<foo>);
    static_assert(TriviallyMoveConstructible<bar>);
    static_assert(not TriviallyMoveConstructible<qux>);
    static_assert(TriviallyMoveConstructible<Derived>);
    static_assert(not TriviallyMoveConstructible<DynamicallyDerived>);

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