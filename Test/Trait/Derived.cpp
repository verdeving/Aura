#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifdef aura_windows
#include <Windows.h>
#endif
#include "Trait/Derived.hpp"

using Aura::Trait::Derived;

// Test types
struct BaseType{};

struct DerivedPublic : BaseType{};

struct DerivedProtected : protected BaseType{};

struct DerivedPrivate : private BaseType{};

struct Unrelated{};

struct DerivedFromDerivedPublic : DerivedPublic{};

struct DerivedFromDerivedProtected : DerivedProtected{};

struct DerivedFromDerivedPrivate : DerivedPrivate{};

struct VirtuallyDerivedFromBase : virtual BaseType{};

[[nodiscard]] auto aura_testing() noexcept -> bool
{
    // Same type
    static_assert(Derived<BaseType, BaseType>, "BaseType, BaseType should be derived");

    // Public inheritance
    static_assert(Derived<DerivedPublic, BaseType>, "DerivedPublic should derive from BaseType");

    // Protected inheritance
    static_assert(Derived<DerivedProtected, BaseType>,
    "DerivedProtected should derive from BaseType");

    // Private inheritance
    static_assert(Derived<DerivedPrivate, BaseType>, "DerivedPrivate should derive from BaseType");

    // Indirect public inheritance
    static_assert(Derived<DerivedFromDerivedPublic, BaseType>,
    "Indirect public inheritance should be derived");

    // Indirect protected inheritance
    static_assert(Derived<DerivedFromDerivedProtected, BaseType>,
    "Indirect protected inheritance should be derived");

    // Indirect private inheritance
    static_assert(Derived<DerivedFromDerivedPrivate, BaseType>,
    "Indirect private inheritance should be derived");

    // Unrelated types
    static_assert(not Derived<Unrelated, BaseType>, "Unrelated should not be derived from BaseType"
    );

    // Reverse relationship should fail
    static_assert(not Derived<BaseType, DerivedPublic>,
    "BaseType should not derive from DerivedPublic");

    // Virtual inheritance
    static_assert(Derived<VirtuallyDerivedFromBase, BaseType>,
    "Virtual inheritance should be derived");

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