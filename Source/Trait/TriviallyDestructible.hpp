#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_trivially_destructible
#define aura_guard_trait_trivially_destructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and all the following are accomplished:
     *
     * - Its destructor is implicitly defined, or explicitly defaulted.
     * - `Self`'s destructor isn't virtual, and all the direct base classes also satisfy this
     * concept.
     * - All the `Self` non-static data members also satisfy this concept.
     */
    template<class Self> concept TriviallyDestructible = Sized<Self> and
    __is_trivially_destructible(Self);
}

#endif
#endif