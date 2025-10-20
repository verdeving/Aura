#if aura_major >= 0 and aura_middle >= 0 and aura_minor >= 1
#ifndef aura_guard_trait_destructible
#define aura_guard_trait_destructible
#include "Sized.hpp"
#ifdef aura_gcc
#include "Function.hpp"
#include "Reference.hpp"
#include "BoundedArray.hpp"
#endif

namespace Aura::Trait
{
    /**
     * @brief Satisfied when `Self` is `Sized` and it has a selected destructor.
     */
    template<class Self> concept Destructible = Sized<Self> and
    #ifdef aura_clang
    __is_destructible(Self)
    #else
    (requires(Self self)
    {
        self.compl Self();
    }
    or (Reference<Self> and not Function<Self>) or BoundedArray<Self>)
    #endif
    ;
}

#endif
#endif