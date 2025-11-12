#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/TriviallyCopyConstructible.hpp"

using Aura::Trait::TriviallyCopyConstructible;

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
    qux(volatile qux&){}
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
    static_assert(TriviallyCopyConstructible<int>);
    static_assert(TriviallyCopyConstructible<int*>);
    static_assert(TriviallyCopyConstructible<int&>);
    static_assert(not TriviallyCopyConstructible<int&&>);

    static_assert(not TriviallyCopyConstructible<void>);
    static_assert(not TriviallyCopyConstructible<decltype(meow)>);
    static_assert(TriviallyCopyConstructible<decltype(&Base::foo)>);
    static_assert(TriviallyCopyConstructible<E>);
    static_assert(not TriviallyCopyConstructible<Incomplete>);

    static_assert(TriviallyCopyConstructible<foo>);
    static_assert(TriviallyCopyConstructible<bar>);
    static_assert(not TriviallyCopyConstructible<qux>);
    static_assert(TriviallyCopyConstructible<Derived>);
    static_assert(not TriviallyCopyConstructible<DynamicallyDerived>);

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