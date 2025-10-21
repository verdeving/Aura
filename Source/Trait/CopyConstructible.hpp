#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_copy_constructible
#define aura_guard_trait_copy_constructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and it has a constructor where the first parameter
     * is an l-value reference type, and no other parameters are given, or the rest of parameters
     * have a default argument.
     */
    template<class Self> concept CopyConstructible = Sized<Self> and (__is_constructible(Self, Self
    &) or __is_constructible(Self, volatile Self&) or __is_constructible(Self, const Self&) or
    __is_constructible(Self, volatile const Self&));
}

#endif
#endif