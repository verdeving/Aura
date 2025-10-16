#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_trivially_default_constructible
#define aura_guard_trait_trivially_default_constructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and all the following are accomplished:
     *
     * - Its default constructor is implicitly defined, or explicitly defaulted.
     * - `Self` contains no virtual functions, and doesn't have virtual base classes, and all the
     * direct base classes also satisfy this concept.
     * - All the`Self` non-static data members don't have a default member initializer and also
     * satisfy this concept.
     */
    template<class Self> concept TriviallyDefaultConstructible = Sized<Self> and
    __is_trivially_constructible(Self);
}

#endif
#endif