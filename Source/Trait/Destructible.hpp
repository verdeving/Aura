#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_destructible
#define aura_guard_trait_destructible
#include "Sized.hpp"

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and it has a selected destructor.
     */
    template<class Self> concept Destructible = Sized<Self> and __is_destructible(Self);
}

#endif
#endif