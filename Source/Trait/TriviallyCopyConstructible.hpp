#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_trivially_copy_constructible
#define aura_guard_trait_trivially_copy_constructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and all the following are accomplished:
     *
     * - Its copy constructor is implicitly defined, or explicitly defaulted.
     * - All the `Self` non-static data members and direct base classes also satisfy this concept.
     */
    template<class Self> concept TriviallyCopyConstructible = Sized<Self> and (
    __is_trivially_constructible(Self, Self&) or __is_trivially_constructible(Self, const Self&));
}

#endif
#endif