#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Core/Safety.hpp"

struct data
{
    int x, y;
};

struct very_simple_pool
{
    data* pointer;

    unsigned capacity;

    constexpr ~very_simple_pool() noexcept
    {
        if(pointer not_eq nullptr)
            delete[] pointer;
    }

    // lets make an additional safe ctor that initializes the data members
    constexpr very_simple_pool(const unsigned initial_capacity) noexcept : pointer(
    new data[initial_capacity]), capacity(initial_capacity){}

    // unsafe subscript context, since we don't check for index < capacity
    constexpr data& operator[] $unreliable(const unsigned index) noexcept
    {
        return pointer[index];
    }
};

consteval int bar() noexcept
{
    return 0;
}

$tunreliable() consteval int bar() noexcept
{
    return 1;
}

consteval int foo() noexcept // normal foo overload
{
    return 2;
}

consteval int foo $unreliable() noexcept // unreliable foo overload
{
    return 4;
}

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    static_assert(foo() == 2 // normal foo call
    and [&]
    {
        $unsafe // explicit unsafe context
        {
            return foo $(); // because it's inside an unsafe context, it calls to the unsafe foo
            // overload
        }
    }() == 4
    and [&]
    {
        $unsafe // explicit unsafe context
        {
            $safe // explicit safe context
            {
                return foo(); // because of safe context re-entrance thanks to the explicit safe,
                // despite the prior unsafe context, it calls to the normal foo overload
            }
        }
    }() == 2
    and [&]
    {
        bool previous_context_was_unsafe;
        $unsafe // explicit unsafe context
            previous_context_was_unsafe = not $safety;

        $safe // explicit safe context
        {
            if(previous_context_was_unsafe)
                return foo() + 2; // Ok
            return foo();
        }
    }() == 4
    and [&]
    {
        $unsafe
            return bar $t()(); // calls the tunreliable bar, it's explicitly in an unsafe context
    }() == 1
    and [&]
    {
        $unsafe
        {
            // very_simple_pool vsp $l(4);   error, vsp only has a constructor callable from a safe
            // context!
            $safe
            {
                very_simple_pool vsp{4}; // Ok
                // vsp $s(0) = data{3, 42};   error, vsp heap elements can only be accessed in an
                // unsafe context!
                $unsafe
                {
                    vsp $s(0) = data{3, 42}; // Ok
                    return vsp $s(0).y == 42; // Ok
                }
            }
        }
    }(),
    "safety contexts rock!");

    return $safety;
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