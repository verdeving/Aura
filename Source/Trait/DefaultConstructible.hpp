#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_default_constructible
#define aura_guard_trait_default_constructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and has an eligible trivial or non-trivial
     * constructor where no parameters are given or all the parameters have a default argument.
     */
    template<class Self> concept DefaultConstructible = Sized<Self> and __is_constructible(Self);
}

#endif
#endif