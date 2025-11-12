#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/MoveConstructible.hpp"

using Aura::Trait::MoveConstructible;

struct foo{};

struct bar
{
    bar(bar&&) = default;
};

struct baz
{
    baz(const baz&&){}
};

struct qux
{
    qux(volatile const qux&&){}
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
    static_assert(MoveConstructible<int>);
    static_assert(MoveConstructible<int*>);
    static_assert(MoveConstructible<int&>);
    static_assert(MoveConstructible<int&&>);

    static_assert(not MoveConstructible<void>);
    static_assert(not MoveConstructible<decltype(meow)>);
    static_assert(MoveConstructible<decltype(&Base::foo)>);
    static_assert(MoveConstructible<E>);
    static_assert(not MoveConstructible<Incomplete>);

    static_assert(MoveConstructible<foo>);
    static_assert(MoveConstructible<bar>);
    static_assert(MoveConstructible<qux>);
    static_assert(MoveConstructible<Derived>);
    static_assert(MoveConstructible<DynamicallyDerived>);

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

#endif