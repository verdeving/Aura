#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_derived
#define aura_guard_trait_derived

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is derived from `Base`.
     *
     * This concept evaluates to `true` iff `Self` is the same as 'Base', or `Self` inherits from
     * `Base` through `virtual`, `public`, `protected`, or `private` inheritance.
     *
     * @tparam Self The type to test for derivation. This is the potential derived type in the
     * relationship.
     * @tparam Base The type to test as a base. This is the potential base class in the
     * relationship.
     */
    template<class Self, class Base> concept Derived = __is_base_of(Base, Self);
}

#endif
#endif